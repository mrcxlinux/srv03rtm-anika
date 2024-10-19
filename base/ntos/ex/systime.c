/*++

Copyright (c) 1989  Microsoft Corporation

Module Name:

    systime.c

Abstract:

    This module implements the NT system time services.

Author:

    Mark Lucovsky (markl) 08-Aug-1989

Revision History:

--*/

#include "exp.h"
#include "stdio.h"
#include "../config/cmp.h"
#include "ntverp.h"
#pragma hdrstop

// Disable warning about WORK_QUEUE_ITEM/PIO_APC_ROUTINE casts
// (those are fine, NtNotifyChangeKey is setup to allow taking a WORK_QUEUE_ITEM*)
#pragma warning(disable:4055)

#ifndef WPA_CHECK
#define WPA_CHECK 1
#endif

//
// Refresh time every hour (soon to be 24 hours)
//

#define EXP_ONE_SECOND      (10 * (1000*1000))
#define EXP_REFRESH_TIME    -3600
#define EXP_DEFAULT_SEPERATION  60

//
// ALLOC_PRAGMA
//

#ifdef WPA_CHECK

NTSTATUS
IsRegistryKeyLocked(
    IN HANDLE KeyHandle,
    IN PBOOLEAN WasLocked);

#endif

VOID
ExpExpirationThread(
    IN PVOID StartContext
    );

BOOLEAN
ExpRefreshTimeZoneInformation(
    IN PLARGE_INTEGER CurrentUniversalTime);

VOID ExpSetSystemTime(
    IN BOOLEAN UpdateCmos,
    IN BOOLEAN UpdateInterruptTime,
    IN LARGE_INTEGER NewTime,
    OUT PLARGE_INTEGER PreviousTime
    );

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, ExAcquireTimeRefreshLock)
#pragma alloc_text(PAGE, ExReleaseTimeRefreshLock)
#ifdef WPA_CHECK
#pragma alloc_text(PAGE, IsRegistryKeyLocked)
#endif
#pragma alloc_text(PAGE, NtLockProductActivationKeys)
#pragma alloc_text(PAGE, ExpTimeZoneWork)
#pragma alloc_text(PAGE, NtQuerySystemTime)
#pragma alloc_text(PAGE, NtQueryTimerResolution)
#pragma alloc_text(PAGE, NtSetTimerResolution)
#pragma alloc_text(PAGE, ExSetTimerResolution)
#pragma alloc_text(PAGE, ExShutdownSystem)
#pragma alloc_text(PAGE, ExpExpirationThread)
#pragma alloc_text(PAGE, ExpWatchExpirationDataWork)
#pragma alloc_text(PAGELK, ExUpdateSystemTimeFromCmos)
#pragma alloc_text(PAGELK, ExpTimeRefreshWork)
#pragma alloc_text(INIT, ExInitializeTimeRefresh)
#pragma alloc_text(PAGE, ExpRefreshTimeZoneInformation)
#pragma alloc_text(PAGELK, ExpSetSystemTime)
#pragma alloc_text(PAGE, NtSetSystemTime)
#endif

//
// Externs
//

KDPC ExpTimeZoneDpc;
KTIMER ExpTimeZoneTimer;
WORK_QUEUE_ITEM ExpTimeZoneWorkItem;

KDPC ExpCenturyDpc;
KTIMER ExpCenturyTimer;
WORK_QUEUE_ITEM ExpCenturyWorkItem;

KDPC ExpTimeRefreshDpc;
KTIMER ExpTimeRefreshTimer;
WORK_QUEUE_ITEM ExpTimeRefreshWorkItem;

ULONG ExpOkToTimeRefresh;
ULONG ExpOkToTimeZoneRefresh;
WORK_QUEUE_ITEM ExpWatchExpirationDataWorkItem;

ERESOURCE ExpTimeRefreshLock;

// 4chan note: this is already defined in some header
// but removing this will move it inside UNDEF
// preventing it from matching systime.obj..
LARGE_INTEGER ExpTimeZoneBias;

//
// Globals
//

#ifdef ALLOC_DATA_PRAGMA
#pragma data_seg()
#endif

ULONG ExpMaxTimeSeperationBeforeCorrect = EXP_DEFAULT_SEPERATION;
BOOLEAN ExpSystemIsInCmosMode = TRUE;
ULONG ExpRealTimeIsUniversal = 0;

#ifdef ALLOC_DATA_PRAGMA
#pragma data_seg("PAGEDATA")
#endif

ULONG ExpCurrentTimeZoneId = 0xffffffff;
RTL_TIME_ZONE_INFORMATION ExpTimeZoneInformation = {0};
LONG ExpLastTimeZoneBias = -1;
LONG ExpAltTimeZoneBias = 0;
LARGE_INTEGER ExpNextCenturyTime = {0,0};
TIME_FIELDS ExpNextCenturyTimeFields = {0};
LARGE_INTEGER ExpTimeRefreshInterval = {0,0};
ULONG ExpRefreshFailures = 0;
LARGE_INTEGER ExpNextSystemCutover = {0,0};
BOOLEAN ExpShuttingDown = 0;

extern BOOLEAN ExpInTextModeSetup;
extern BOOLEAN ExpTooLateForErrors;

#ifdef WPA_CHECK

//
// This is for frankar's evaluation SKU support
// [0] - Setup Date low
// [2] - Setup Date high
// [1] - Evaluation Period in minutes
//

ULONG ExpNtExpirationDataLength = 12;
LARGE_INTEGER ExpNtExpirationDate = {0};
LARGE_INTEGER ExpNtInstallationDate = {0};
BOOLEAN ExpNextExpirationIsFatal = FALSE;
HANDLE ExpExpirationDataKey = NULL;
ULONG ExpExpirationDataChangeBuffer = 0;
IO_STATUS_BLOCK ExpExpirationDataIoSb = {0};
#endif

//
// Count of the number of processes that have set the timer resolution.
//

ULONG ExpTimerResolutionCount = 0;
ULONG ExpKernelResolutionCount = 0;

LARGE_INTEGER ExpLastShutDown = {0,0};
ULONG ExpRefreshCount = 0;

#ifdef ALLOC_DATA_PRAGMA
#pragma data_seg()
#endif

BOOLEAN ExCmosClockIsSane = TRUE;

BOOLEAN
ExAcquireTimeRefreshLock(
    IN BOOLEAN Wait
    )
{

    KeEnterCriticalRegion();

    if (ExAcquireResourceExclusiveLite(&ExpTimeRefreshLock, Wait) == FALSE) {
        KeLeaveCriticalRegion();
        return FALSE;
    }

    return TRUE;
}

VOID
ExReleaseTimeRefreshLock(
    VOID
    )
{

    ExReleaseResourceLite(&ExpTimeRefreshLock);

    KeLeaveCriticalRegion();
}

VOID
ExpTimeRefreshWork(
    IN PVOID Context
    )
{

    ULONG NumberOfProcessors;
    LARGE_INTEGER ShutDownTime;

    LARGE_INTEGER KeTime;
    HANDLE Thread;
    NTSTATUS Status;

    UNREFERENCED_PARAMETER(Context);

    PAGED_CODE(); // 202

    do {
        if ( ExpRefreshCount == 0 ) {

            //
            // first time through time refresh. If we are not in setup mode
            // then make sure shutdowntime is in good shape
            //
            if ( !ExpSetupModeDetected && !ExpInTextModeSetup ) {

                if ( ExpLastShutDown.QuadPart && ExpLastShutDown.HighPart != 0) {

                    NumberOfProcessors = ExpSetupSystemPrefix.LowPart;
                    NumberOfProcessors = NumberOfProcessors >> 5;
                    NumberOfProcessors = NumberOfProcessors & 0x0000001f;

                    ShutDownTime = ExpLastShutDown;

                    ShutDownTime.LowPart &= 0x3f;


                    if ( ExpSetupSystemPrefix.HighPart & 0x04000000 ) {

                        if ( (ShutDownTime.LowPart >> 1 != NumberOfProcessors) ||
                             (ShutDownTime.LowPart & 1) == 0 ) {

                            ShutDownTime.HighPart = 0;

                        }
                        else {
                            if ( ShutDownTime.HighPart == 0 ) {
                                ShutDownTime.HighPart = 1;
                            }
                        }
                    }
                    else {
                        if ( (ShutDownTime.LowPart >> 1 != NumberOfProcessors) ||
                             (ShutDownTime.LowPart & 1) ) {

                            ShutDownTime.HighPart = 0;

                        }
                        else {
                            if ( ShutDownTime.HighPart == 0 ) {
                                ShutDownTime.HighPart = 1;
                            }
                        }
                    }
                    ExpRefreshCount++;
                    ExpLastShutDown = ShutDownTime;
                    ExpLastShutDown.LowPart |= 0x40;
                }
            }
            else {
                ExpLastShutDown.QuadPart = 0;
            }
        }
        else {
            if ( !ExpSetupModeDetected && !ExpInTextModeSetup ) {
                ExpRefreshCount++;
            }
        }

        //
        // If enabled, synchronize the system time to the cmos time. Pay
        // attention to timezone bias.
        //

        //
        // Time zone worker will set just did switchover. This periodic timer
        // will clear this, but will also skip all time adjustment work. This will
        // help keep us out of the danger zone +/- 1 hour around a switchover
        //

        if (KeTimeSynchronization) {
            ExAcquireTimeRefreshLock(TRUE);
            ExUpdateSystemTimeFromCmos(0, 0);
            ExReleaseTimeRefreshLock();
        }

#ifdef WPA_CHECK
        //
        // Enforce evaluation period
        //
        if ( ExpNtExpirationData[1] ) {
            KeQuerySystemTime(&KeTime);
            if ( KeTime.QuadPart >= ExpNtExpirationDate.QuadPart ) {
                if ( ExpNextExpirationIsFatal ) {
                    PoShutdownBugCheck (FALSE,
                                        END_OF_NT_EVALUATION_PERIOD,
                                        (ULONG_PTR)ExpNtInstallationDate.LowPart,
                                        (ULONG_PTR)ExpNtInstallationDate.HighPart,
                                        (ULONG_PTR)ExpNtExpirationData[1],
                                        0);
                }
                else {
                    ExpNextExpirationIsFatal = TRUE;
                    Status = PsCreateSystemThread(&Thread,
                                                  THREAD_ALL_ACCESS,
                                                  NULL,
                                                  0L,
                                                  NULL,
                                                  ExpExpirationThread,
                                                  (PVOID)STATUS_EVALUATION_EXPIRATION
                                                  );

                    if (NT_SUCCESS(Status)) {
                        ZwClose(Thread);
                    }
                }
            }
#endif
        }
    } while (InterlockedDecrement((PLONG)&ExpOkToTimeRefresh));

    KeSetTimer(
        &ExpTimeRefreshTimer,
        ExpTimeRefreshInterval,
        &ExpTimeRefreshDpc
        );
}

VOID
ExpTimeRefreshDpcRoutine(
    IN PKDPC Dpc,
    IN PVOID DeferredContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2
    )
{

    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(DeferredContext);
    UNREFERENCED_PARAMETER(SystemArgument1);
    UNREFERENCED_PARAMETER(SystemArgument2);

    if (InterlockedIncrement((PLONG)&ExpOkToTimeRefresh) == 1) {
        ExQueueWorkItem(&ExpTimeRefreshWorkItem, DelayedWorkQueue);
    }
}

#ifdef WPA_CHECK

// 4chan todo: in the src this probably doesn't abuse the WasLocked param like this
// but the optimized systime.obj seems to move things so WasLocked gets overwritten
NTSTATUS
IsRegistryKeyLocked(
    IN HANDLE KeyHandle,
    IN PBOOLEAN WasLocked)
{

    NTSTATUS Status = STATUS_SUCCESS;
    PCM_KEY_BODY KeyBody;

    BEGIN_LOCK_CHECKPOINT;

    *WasLocked = FALSE;
    
    Status = ObReferenceObjectByHandle(
                                KeyHandle,
                                KEY_READ,
                                CmpKeyObjectType,
                                KernelMode,
                                (PVOID *)&KeyBody,
                                NULL
                                );

    if(NT_SUCCESS(Status)) {
        *WasLocked = (BOOLEAN)(KeyBody->KeyControlBlock->ExtFlags & 0x80);
        ObfDereferenceObject(KeyBody);
    }
    
    END_LOCK_CHECKPOINT;
    
    return Status;
}

FORCEINLINE
VOID
WPADecipher64 (
    const PULONG v,
    PULONG w,
    const PULONG k)
{

    ULONG   y = v [0],
            z = v [1],
            n = 32,
            sum = 0xC6EF3720,
            delta = 0x9E3779B9;

    /* sum = delta<<5, in general sum = delta * n */

    while (n-- > 0) {
        z -= ((y >> 5 ^ y << 4) + y ^ k[(sum >> 0xB) & 3] + sum);
        sum -= delta;
        y -= ((z >> 5 ^ z << 4) + z ^ k[sum & 3] + sum);
    }

    w[0] = y;
    w[1] = z;
}

FORCEINLINE
VOID
WPADecrypt128 (
    PUCHAR pBytes,
    ULONG cbBytes,
    ULONG dkey[4]
    )
{

    int Size = cbBytes - 8;
    PUCHAR Ptr;

    if (Size >= 0) {
        Ptr = pBytes;

        do {
            WPADecipher64((PULONG)&Ptr[Size], (PULONG)&Ptr[Size--], dkey);
        }
        while(Size >= 0);
    }
}

FORCEINLINE
USHORT
WPAStringChecksum(
    PUSHORT pStart,
    ULONG cchLen)
{

    ULONG i;
    USHORT Result;

    Result = 43889;
    for(i = 0; i < cchLen; i++) {
        Result = pStart[i] ^ (pStart[i] + Result);
    }

    return Result;
}

const ULONG abWPAStringKey[4] = { 0xFF8BC3CC, 0xFF8BC3CC, 0x424448B, 0x4C2CC };

UCHAR szWPAKeyNameData[] = {
    0x4D, 0x74, 0x86, 0x97, 0xF8, 0x98, 0x59, 0xAD,
    0x3E, 0x7C, 0xE7, 0x2F, 0x31, 0xF1, 0xA4, 0xDD,
    0x58, 0x39, 0x78, 0x7D, 0x2E, 0x41, 0xED, 0xB6,
    0x9B, 0x8D, 0x5D, 0x1E, 0xDA, 0x8E, 0xCD, 0x4D,
    0x91, 0xCB, 0x71, 0xF4, 0xAF, 0x24, 0xBD, 0xA1,
    0x3C, 0x36, 0x34, 0x63, 0x98, 0xFD, 0xC2, 0xCF,
    0xDA, 0x34, 0x87, 0x82, 0x57, 0xFB, 0x7E, 0x2C,
    0x12, 0x18, 0x5F, 0x23,
};
#endif

NTSTATUS
NtLockProductActivationKeys(
    IN OUT OPTIONAL ULONG   *pPrivateVer,
    OUT OPTIONAL ULONG   *pSafeMode
    )
{

#ifdef WPA_CHECK

    // 4chan todo: this func is 99% match to systime.obj
    // except order of these variables in stack is different
    // can't seem to change it though, eg instanceKeyIndex always gets put at 1C...
    ULONG instanceKeyIndex;

    NTSTATUS Status;
    NTSTATUS returnstatus;

    USHORT SubKeyName[512];

    UCHAR Buffer[1024];
    PKEY_BASIC_INFORMATION KeyBuffer;

    USHORT WPAKeyNameBuf[30];
    UNICODE_STRING WPAKeyName;
    UNICODE_STRING subkeyString;

    OBJECT_ATTRIBUTES subkeyObjectAttributes;
    OBJECT_ATTRIBUTES ObjectAttributes;

    ULONG resultSize;

    HANDLE WPAKey = 0;
    HANDLE handleSubkey;

    BOOLEAN IsLocked;

    RtlCopyMemory(WPAKeyNameBuf, szWPAKeyNameData, sizeof(WPAKeyNameBuf));

    if(WPAStringChecksum(WPAKeyNameBuf, sizeof(WPAKeyNameBuf) / sizeof(USHORT)) != 47439) {
        return STATUS_UNSUCCESSFUL;
    }

    WPADecrypt128((PUCHAR)&WPAKeyNameBuf, sizeof(WPAKeyNameBuf), (PULONG)abWPAStringKey);

    RtlInitUnicodeString(&WPAKeyName, WPAKeyNameBuf);

    if (KeGetPreviousMode() != KernelMode) {
        try {
            if (pPrivateVer) {
                ProbeForWriteUlong(pPrivateVer);
                *pPrivateVer = *pPrivateVer < 3782 ? 0 : VER_PRODUCTBUILD;
            }

            if (pSafeMode) {
                ProbeForWriteUlong(pSafeMode);
                *pSafeMode = InitSafeBootMode;
            }
        } except (EXCEPTION_EXECUTE_HANDLER) {

            return GetExceptionCode();
        }
    }
    else {
        if (pPrivateVer) {
            *pPrivateVer = *pPrivateVer < 3782 ? 0 : VER_PRODUCTBUILD;
        }

        if (pSafeMode) {
            *pSafeMode = InitSafeBootMode;
        }
    }

    InitializeObjectAttributes( &ObjectAttributes,
                                &WPAKeyName,
                                OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );

    Status = ZwOpenKey(&WPAKey, KEY_READ, &ObjectAttributes);
    returnstatus = Status;

    if (NT_SUCCESS(Status)) {
        instanceKeyIndex = 0;

        while ((Status = ZwEnumerateKey(WPAKey, instanceKeyIndex, 0, Buffer, sizeof(Buffer), &resultSize))
            != STATUS_NO_MORE_ENTRIES) {

            if (!NT_SUCCESS(Status)) {
                returnstatus = Status;
                break;
            }

            KeyBuffer = ((PKEY_BASIC_INFORMATION)&Buffer);

            if (KeyBuffer->NameLength + 0x40 > sizeof(Buffer)) {
                returnstatus = STATUS_NO_MEMORY;
                continue;
            }

            wcscpy(SubKeyName, WPAKeyNameBuf);
            wcsncat(SubKeyName, KeyBuffer->Name, KeyBuffer->NameLength / sizeof(USHORT));
            wcscat(SubKeyName, L"\\");

            RtlInitUnicodeString(&subkeyString, SubKeyName);

            InitializeObjectAttributes( &subkeyObjectAttributes,
                                        &subkeyString,
                                        OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
                                        NULL,
                                        NULL
                                      );

            Status = ZwOpenKey(&handleSubkey, KEY_READ, &subkeyObjectAttributes);
            if (NT_SUCCESS(Status)) {
                Status = IsRegistryKeyLocked(handleSubkey, &IsLocked);

                if (NT_SUCCESS(Status)) {
                    if (!IsLocked) {
                        Status = ZwLockRegistryKey(handleSubkey);
                        if (NT_SUCCESS(Status)) {
                            handleSubkey = 0;
                            ++instanceKeyIndex;
                            continue;
                        }
                    }
                    else {
                        ZwClose(handleSubkey);
                        ++instanceKeyIndex;
                        continue;
                    }
                }
                returnstatus = Status;
                ZwClose(handleSubkey);
            }
            else {
                returnstatus = Status;
            }

            ++instanceKeyIndex;
        }

        ZwClose(WPAKey);
        if (Status == STATUS_NO_MORE_ENTRIES) {
            returnstatus = 0;
        }

        return returnstatus;
    }

    return Status;

#else

    UNREFERENCED_PARAMETER(pPrivateVer);
    UNREFERENCED_PARAMETER(pSafeMode);

    return STATUS_SUCCESS;
#endif
}

VOID
ExInitializeTimeRefresh(
    VOID
    )
{

#ifdef WPA_CHECK
    LARGE_INTEGER ExpirationPeriod;
    NTSTATUS Status;
    UNICODE_STRING KeyName;
    OBJECT_ATTRIBUTES ObjectAttributes;
    ULONG ulBuild;

    ulBuild = VER_PRODUCTBUILD;
    ZwLockProductActivationKeys(&ulBuild, 0);

    if ( ExpSetupModeDetected ) {
        ExpNtExpirationData[1] = 0;
    }
    if ( ExpNtExpirationData[1] ) {

        if ( ExpNtExpirationData[0] == 0 && ExpNtExpirationData[2] == 0 ) {
            KeQuerySystemTime(&ExpNtInstallationDate);
        }
        else {
            ExpNtInstallationDate.LowPart = ExpNtExpirationData[0];
            ExpNtInstallationDate.HighPart = ExpNtExpirationData[2];
        }

        ExpirationPeriod.QuadPart = Int32x32To64(EXP_ONE_SECOND,
                                                 ExpNtExpirationData[1] * 60
                                                );
        SharedUserData->SystemExpirationDate.QuadPart =
            ExpNtExpirationDate.QuadPart = ExpNtInstallationDate.QuadPart + ExpirationPeriod.QuadPart;

        ExpShuttingDown = FALSE;

        ExInitializeWorkItem(&ExpWatchExpirationDataWorkItem, ExpWatchExpirationDataWork, NULL);


        RtlInitUnicodeString(&KeyName,L"\\Registry\\Machine\\System\\CurrentControlSet\\Control\\Session Manager\\Executive");

        InitializeObjectAttributes( &ObjectAttributes,
                                    &KeyName,
                                    OBJ_CASE_INSENSITIVE,
                                    NULL,
                                    NULL
                                  );

        Status = ZwOpenKey( &ExpExpirationDataKey,
                            KEY_READ | KEY_NOTIFY | KEY_WRITE,
                            &ObjectAttributes
                          );

        if ( NT_SUCCESS(Status) ) {

            ZwNotifyChangeKey(
                               ExpExpirationDataKey,
                               NULL,
                               (PIO_APC_ROUTINE)&ExpWatchExpirationDataWorkItem,
                               (PVOID)DelayedWorkQueue,
                               &ExpExpirationDataIoSb,
                               REG_LEGAL_CHANGE_FILTER,
                               FALSE,
                               &ExpExpirationDataChangeBuffer,
                               sizeof(ExpExpirationDataChangeBuffer),
                               TRUE
                              );
        }
    }


#endif

    KeInitializeDpc(
        &ExpTimeRefreshDpc,
        ExpTimeRefreshDpcRoutine,
        NULL
        );
    ExInitializeWorkItem(&ExpTimeRefreshWorkItem, ExpTimeRefreshWork, NULL);
    KeInitializeTimer(&ExpTimeRefreshTimer);

    ExpTimeRefreshInterval.QuadPart = Int32x32To64(EXP_ONE_SECOND,
                                                   EXP_REFRESH_TIME);

    KeSetTimer(
        &ExpTimeRefreshTimer,
        ExpTimeRefreshInterval,
        &ExpTimeRefreshDpc
        );

    ExInitializeResourceLite(&ExpTimeRefreshLock);
}

VOID
ExpTimeZoneWork(
    IN PVOID Context
    )
{

    UNREFERENCED_PARAMETER(Context);

    PAGED_CODE(); // 812

    do {
        ZwSetSystemTime(NULL, NULL);
    } while (InterlockedDecrement((PLONG)&ExpOkToTimeZoneRefresh));
}

VOID
ExpTimeZoneDpcRoutine(
    IN PKDPC Dpc,
    IN PVOID DeferredContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2
    )
{

    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(DeferredContext);
    UNREFERENCED_PARAMETER(SystemArgument1);
    UNREFERENCED_PARAMETER(SystemArgument2);

    if (InterlockedIncrement((PLONG)&ExpOkToTimeZoneRefresh) == 1) {
        ExQueueWorkItem(&ExpTimeZoneWorkItem, DelayedWorkQueue);
    }
}

VOID
ExpCenturyDpcRoutine(
    IN PKDPC Dpc,
    IN PVOID DeferredContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2
    )
{

    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(DeferredContext);
    UNREFERENCED_PARAMETER(SystemArgument1);
    UNREFERENCED_PARAMETER(SystemArgument2);

    if (InterlockedIncrement((PLONG)&ExpOkToTimeZoneRefresh) == 1) {
        ExQueueWorkItem(&ExpCenturyWorkItem, DelayedWorkQueue);
    }
}

BOOLEAN
ExpRefreshTimeZoneInformation(
    IN PLARGE_INTEGER CurrentUniversalTime
    )
{

    NTSTATUS Status;
    RTL_TIME_ZONE_INFORMATION tzi;
    LARGE_INTEGER NewTimeZoneBias;
    LARGE_INTEGER LocalCustomBias;
    LARGE_INTEGER StandardTime;
    LARGE_INTEGER DaylightTime;
    LARGE_INTEGER NextCutover;
    LONG ActiveBias;

    LARGE_INTEGER CurrentTime;
    TIME_FIELDS TimeFields;

    PAGED_CODE(); // 876

    if (ExpTimeZoneWorkItem.WorkerRoutine == NULL) {
        ExInitializeTimeRefresh();
        KeInitializeDpc(&ExpTimeZoneDpc, ExpTimeZoneDpcRoutine, NULL);
        ExInitializeWorkItem(&ExpTimeZoneWorkItem, ExpTimeZoneWork, NULL);
        KeInitializeTimer(&ExpTimeZoneTimer);
        KeInitializeDpc(&ExpCenturyDpc, ExpCenturyDpcRoutine, NULL);
        ExInitializeWorkItem(&ExpCenturyWorkItem, ExpTimeZoneWork, NULL);
        KeInitializeTimer(&ExpCenturyTimer);

        //
        // TODO: Add a macro for initialising TIME_FIELDS later if deemed necessary.
        //

        ExpNextCenturyTimeFields.Year = 0;
        ExpNextCenturyTimeFields.Month = 1;
        ExpNextCenturyTimeFields.Day = 1;
        ExpNextCenturyTimeFields.Hour = 0;
        ExpNextCenturyTimeFields.Minute = 0;
        ExpNextCenturyTimeFields.Second = 0;
        ExpNextCenturyTimeFields.Milliseconds = 1;
    }

    //
    // Timezone Bias is initially 0
    //

    Status = RtlQueryTimeZoneInformation( &tzi );
    if (!NT_SUCCESS( Status )) {
        ExpSystemIsInCmosMode = TRUE;
        ExpRefreshFailures++;
        return FALSE;
    }

    //
    // Get the new timezone bias
    //

    NewTimeZoneBias.QuadPart = Int32x32To64(tzi.Bias*60,    // Bias in seconds
                                            10000000
                                           );

    ActiveBias = tzi.Bias;

    //
    // Now see if we have stored cutover times
    //

    if ( tzi.StandardStart.Month && tzi.DaylightStart.Month ) {

        //
        // We have timezone cutover information. Compute the
        // cutover dates and compute what our current bias
        // is
        //

        if ( !RtlCutoverTimeToSystemTime(
                &tzi.StandardStart,
                &StandardTime,
                CurrentUniversalTime,
                TRUE
                ) ) {
            ExpSystemIsInCmosMode = TRUE;
            ExpRefreshFailures++;
            return FALSE;
        }

        if ( !RtlCutoverTimeToSystemTime(
                &tzi.DaylightStart,
                &DaylightTime,
                CurrentUniversalTime,
                TRUE
                ) ) {
            ExpSystemIsInCmosMode = TRUE;
            ExpRefreshFailures++;
            return FALSE;
        }

        //
        // If daylight < standard, then time >= daylight and
        // less than standard is daylight
        //

        if ( DaylightTime.QuadPart < StandardTime.QuadPart ) {

            //
            // If today is >= DaylightTime and < StandardTime, then
            // We are in daylight savings time
            //

            if ( (CurrentUniversalTime->QuadPart >= DaylightTime.QuadPart) &&
                 (CurrentUniversalTime->QuadPart < StandardTime.QuadPart) ) {

                if ( !RtlCutoverTimeToSystemTime(
                        &tzi.StandardStart,
                        &NextCutover,
                        CurrentUniversalTime,
                        FALSE
                        ) ) {
                    ExpSystemIsInCmosMode = TRUE;
                    ExpRefreshFailures++;
                    return FALSE;
                }
                ExpCurrentTimeZoneId = TIME_ZONE_ID_DAYLIGHT;
                SharedUserData->TimeZoneId = ExpCurrentTimeZoneId;
            }
            else {
                if ( !RtlCutoverTimeToSystemTime(
                        &tzi.DaylightStart,
                        &NextCutover,
                        CurrentUniversalTime,
                        FALSE
                        ) ) {
                    ExpSystemIsInCmosMode = TRUE;
                    ExpRefreshFailures++;
                    return FALSE;
                }
                ExpCurrentTimeZoneId = TIME_ZONE_ID_STANDARD;
                SharedUserData->TimeZoneId = ExpCurrentTimeZoneId;
            }
        }
        else {

            //
            // If today is >= StandardTime and < DaylightTime, then
            // We are in standard time
            //

            if ( (CurrentUniversalTime->QuadPart >= StandardTime.QuadPart) &&
                 (CurrentUniversalTime->QuadPart < DaylightTime.QuadPart) ) {

                if ( !RtlCutoverTimeToSystemTime(
                        &tzi.DaylightStart,
                        &NextCutover,
                        CurrentUniversalTime,
                        FALSE
                        ) ) {
                    ExpSystemIsInCmosMode = TRUE;
                    ExpRefreshFailures++;
                    return FALSE;
                }
                ExpCurrentTimeZoneId = TIME_ZONE_ID_STANDARD;
                SharedUserData->TimeZoneId = ExpCurrentTimeZoneId;
            }
            else {
                if ( !RtlCutoverTimeToSystemTime(
                        &tzi.StandardStart,
                        &NextCutover,
                        CurrentUniversalTime,
                        FALSE
                        ) ) {
                    ExpSystemIsInCmosMode = TRUE;
                    ExpRefreshFailures++;
                    return FALSE;
                }
                ExpCurrentTimeZoneId = TIME_ZONE_ID_DAYLIGHT;
                SharedUserData->TimeZoneId = ExpCurrentTimeZoneId;
            }
        }

        //
        // At this point, we know our current timezone and the
        // Universal time of the next cutover.
        //

        LocalCustomBias.QuadPart = Int32x32To64(
                            ExpCurrentTimeZoneId == TIME_ZONE_ID_DAYLIGHT ?
                                tzi.DaylightBias*60 :
                                tzi.StandardBias*60,                // Bias in seconds
                            10000000
                            );

        ActiveBias += ExpCurrentTimeZoneId == TIME_ZONE_ID_DAYLIGHT ?
                                tzi.DaylightBias :
                                tzi.StandardBias;
        ExpTimeZoneBias.QuadPart =
                            NewTimeZoneBias.QuadPart + LocalCustomBias.QuadPart;
#ifdef _ALPHA_
        SharedUserData->TimeZoneBias = ExpTimeZoneBias.QuadPart;
#else
        SharedUserData->TimeZoneBias.High2Time = ExpTimeZoneBias.HighPart;
        SharedUserData->TimeZoneBias.LowPart = ExpTimeZoneBias.LowPart;
        SharedUserData->TimeZoneBias.High1Time = ExpTimeZoneBias.HighPart;
#endif
        ExpTimeZoneInformation = tzi;
        ExpLastTimeZoneBias = ActiveBias;
        ExpSystemIsInCmosMode = FALSE;

        //
        // NextCutover contains date on next transition
        //

        //
        // Convert to universal time and create a DPC to fire at the
        // appropriate time
        //
        ExLocalTimeToSystemTime(&NextCutover,&ExpNextSystemCutover);
#if 0
PrintTime(&NextSystemCutover,&NextCutover,CurrentUniversalTime);
#endif // 0

        KeSetTimer(
            &ExpTimeZoneTimer,
            ExpNextSystemCutover,
            &ExpTimeZoneDpc
            );
    }
    else {
        KeCancelTimer(&ExpTimeZoneTimer);
        ExpTimeZoneBias = NewTimeZoneBias;
#ifdef _ALPHA_
        SharedUserData->TimeZoneBias = ExpTimeZoneBias.QuadPart;
#else
        SharedUserData->TimeZoneBias.High2Time = ExpTimeZoneBias.HighPart;
        SharedUserData->TimeZoneBias.LowPart = ExpTimeZoneBias.LowPart;
        SharedUserData->TimeZoneBias.High1Time = ExpTimeZoneBias.HighPart;
#endif
        ExpCurrentTimeZoneId = TIME_ZONE_ID_UNKNOWN;
        SharedUserData->TimeZoneId = ExpCurrentTimeZoneId;
        ExpTimeZoneInformation = tzi;
        ExpLastTimeZoneBias = ActiveBias;
        ExpSystemIsInCmosMode = FALSE;
    }

    RtlCopyMemory(&CurrentTime, CurrentUniversalTime, sizeof(LARGE_INTEGER));
    RtlTimeToTimeFields(&CurrentTime, &TimeFields);
    ExpNextCenturyTimeFields.Year = 100 * (TimeFields.Year / 100 + 1);
    RtlTimeFieldsToTime(&ExpNextCenturyTimeFields, &CurrentTime);
    ExLocalTimeToSystemTime(&CurrentTime, &ExpNextCenturyTime);
    KeSetTimer(&ExpCenturyTimer, ExpNextCenturyTime, &ExpCenturyDpc);

    //
    // If time is stored as local time, update the registry with
    // our best guess at the local time bias
    //

    if (!ExpRealTimeIsUniversal) {
        RtlSetActiveTimeBias(ExpLastTimeZoneBias);
    }

    return TRUE;
}

NTSTATUS
NtQuerySystemTime(
    OUT PLARGE_INTEGER SystemTime
    )

/*++

Routine Description:

    This function returns the absolute system time. The time is in units of
    100nsec ticks since the base time which is midnight January 1, 1601.

Arguments:

    SystemTime - Supplies the address of a variable that will receive the
        current system time.

Return Value:

    STATUS_SUCCESS is returned if the service is successfully executed.

    STATUS_ACCESS_VIOLATION is returned if the output parameter for the
        system time cannot be written.

--*/

{

    LARGE_INTEGER CurrentTime;
    KPROCESSOR_MODE PreviousMode;

    PAGED_CODE(); // 1132 / 1176?

    //
    // Get previous processor mode and probe argument if necessary.
    //

    PreviousMode = KeGetPreviousMode();

    if (PreviousMode != KernelMode) {

        //
        // Establish an exception handler and attempt to write the system time
        // to the specified variable. If the write attempt fails, then return
        // the exception code as the service status. Otherwise return success
        // as the service status.
        //

        try {
            ProbeForWriteSmallStructure((PVOID)SystemTime, sizeof(LARGE_INTEGER), sizeof(ULONG));

            //
            // Query the current system time and store the result in a local
            // variable, then store the local variable in the current time
            // variable. This is required so that faults can be prevented from
            // happening in the query time routine.
            //

            KeQuerySystemTime(&CurrentTime);
            *SystemTime = CurrentTime;

        } except (EXCEPTION_EXECUTE_HANDLER) {
            //
            // If an exception occurs during the write of the current system time,
            // then always handle the exception and return the exception code as the
            // status value.
            //

            return GetExceptionCode();
        }
    } else {
        KeQuerySystemTime(SystemTime);
    }

    return STATUS_SUCCESS;
}

NTSTATUS
NtSetSystemTime(
    IN PLARGE_INTEGER SystemTime,
    OUT PLARGE_INTEGER PreviousTime OPTIONAL
    )

/*++

Routine Description:

    This function sets the current system time and optionally returns the
    previous system time.

Arguments:

    SystemTime - Supplies a pointer to the new value for the system time.

    PreviousTime - Supplies an optional pointer to a variable that receives
        the previous system time.

Return Value:

    STATUS_SUCCESS is returned if the service is successfully executed.

    STATUS_PRIVILEGE_NOT_HELD is returned if the caller does not have the
        privilege to set the system time.

    STATUS_ACCESS_VIOLATION is returned if the input parameter for the
        system time cannot be read or the output parameter for the system
        time cannot be written.

    STATUS_INVALID_PARAMETER is returned if the input system time is negative.

--*/

{

    LARGE_INTEGER CurrentTime;
    LARGE_INTEGER NewTime;
    LARGE_INTEGER CmosTime;
    KPROCESSOR_MODE PreviousMode;
    BOOLEAN HasPrivilege = FALSE;
    TIME_FIELDS TimeFields;
    BOOLEAN CmosMode;

    NTSTATUS Status;

    PAGED_CODE(); // 1267

    //
    // If the caller is really trying to set the time, then do it.
    // If no time is passed, the caller is simply trying to update
    // the system time zone information
    //

    if (ARGUMENT_PRESENT(SystemTime)) {
        //
        // Get previous processor mode and probe arguments if necessary.
        //

        PreviousMode = KeGetPreviousMode();

        //
        // Check if the current thread has the privilege to set the current
        // system time. If the thread does not have the privilege, then return
        // access denied.
        //

        HasPrivilege = SeSinglePrivilegeCheck(
                           SeSystemtimePrivilege,
                           PreviousMode
                           );

        if (!HasPrivilege) {
            return STATUS_PRIVILEGE_NOT_HELD;
        }

        if (PreviousMode != KernelMode) {

            //
            // Establish an exception handler and attempt to set the new system time.
            // If the read attempt for the new system time fails or the write attempt
            // for the previous system time fails, then return the exception code as
            // the service status. Otherwise return either success or access denied
            // as the service status.
            //

            try {
                ProbeForReadSmallStructure((PVOID)SystemTime, sizeof(LARGE_INTEGER), sizeof(ULONG));

                if (ARGUMENT_PRESENT(PreviousTime)) {
                    ProbeForWriteSmallStructure((PVOID)PreviousTime, sizeof(LARGE_INTEGER), sizeof(ULONG));
                }

                NewTime = *SystemTime;
            } except (EXCEPTION_EXECUTE_HANDLER) {
                //
                // If an exception occurs during the read of the new system time or during
                // the write of the previous sytem time, then always handle the exception
                // and return the exception code as the status value.
                //

                return GetExceptionCode();
            }

        } else {
            NewTime = *SystemTime;
        }

        //
        // Get the new system time and check to ensure that the value is
        // positive and reasonable. If the new system time is negative, then
        // return an invalid parameter status.
        //

        if ((NewTime.HighPart < 0) || (NewTime.HighPart > 0x20000000)) {
            return STATUS_INVALID_PARAMETER;
        }

        ExAcquireTimeRefreshLock(TRUE);
        ExpSetSystemTime(TRUE, FALSE, NewTime, &CurrentTime);
        SeAuditSystemTimeChange(CurrentTime, NewTime);
        ExReleaseTimeRefreshLock();

        //
        // Anytime we set the system time, x86 systems will also have to set the registry
        // to reflect the timezone bias.
        //

        if (PreviousTime) {
            if (PreviousMode != KernelMode) {
                try {
                    *PreviousTime = CurrentTime;
                } except (EXCEPTION_EXECUTE_HANDLER) {
                    //
                    // If an exception occurs during the read of the new system time or during
                    // the write of the previous sytem time, then always handle the exception
                    // and return the exception code as the status value.
                    //

                    return GetExceptionCode();
                }
            } else {
                *PreviousTime = CurrentTime;
            }
        }

        Status = STATUS_SUCCESS;
    } else {

        Status = STATUS_INVALID_PARAMETER;
        ExAcquireTimeRefreshLock(TRUE);

        CmosMode = ExpSystemIsInCmosMode;

        if (ExCmosClockIsSane) {
            if (HalQueryRealTimeClock(&TimeFields) != FALSE) {
                RtlTimeFieldsToTime(&TimeFields, &CmosTime);
                if ( ExpRefreshTimeZoneInformation(&CmosTime) ) {

                    //
                    // reset the Cmos time if it is stored in local
                    // time and we are switching away from CMOS time.
                    //

                    if ( !ExpRealTimeIsUniversal ) {
                        KeQuerySystemTime(&CurrentTime);
                        if ( !CmosMode ) {
                            ExSystemTimeToLocalTime(&CurrentTime, &CmosTime);
                            RtlTimeToTimeFields(&CmosTime, &TimeFields);
                            ExCmosClockIsSane = HalSetRealTimeClock(&TimeFields);

                        } else {

                            //
                            // Now we need to recompute our time base
                            // because we thought we had UTC but we really
                            // had local time
                            //

                            ExLocalTimeToSystemTime(&CmosTime, &NewTime);
                            KeSetSystemTime(&NewTime, &CurrentTime, FALSE, NULL);
                        }
                    }

                    PoNotifySystemTimeSet();
                    Status = STATUS_SUCCESS;
                }
            }
        }

        ExReleaseTimeRefreshLock();
    }
    return Status;
}

VOID
ExUpdateSystemTimeFromCmos(
    IN BOOLEAN UpdateInterruptTime,
    IN ULONG MaxSepInSeconds
    )
{

    LARGE_INTEGER SystemTime;
    LARGE_INTEGER CmosTime;
    LARGE_INTEGER CurrentTime;
    LARGE_INTEGER TimeDiff;
    TIME_FIELDS TimeFields;
    LARGE_INTEGER MaxSeparation;

    MaxSeparation.LowPart = MaxSepInSeconds;

    if (MaxSepInSeconds == 0) {
        MaxSeparation.LowPart = ExpMaxTimeSeperationBeforeCorrect;
    }

    MaxSeparation.QuadPart = MaxSeparation.LowPart * 10000000i64;

    if (ExCmosClockIsSane) {

        if (HalQueryRealTimeClock(&TimeFields) != FALSE) {

            if (RtlTimeFieldsToTime(&TimeFields, &CmosTime) != FALSE) {

                ExLocalTimeToSystemTime(&CmosTime, &SystemTime);
                KeQuerySystemTime(&CurrentTime);

                //
                // Only set the SystemTime if the times differ by 1 minute
                //

                if (SystemTime.QuadPart > CurrentTime.QuadPart) {
                    TimeDiff.QuadPart = SystemTime.QuadPart - CurrentTime.QuadPart;
                }
                else {
                    TimeDiff.QuadPart = CurrentTime.QuadPart - SystemTime.QuadPart;
                }

                if ((ULONGLONG)TimeDiff.QuadPart > (ULONGLONG)MaxSeparation.QuadPart) {
                    ExpSetSystemTime(FALSE, UpdateInterruptTime, SystemTime, &CurrentTime);
                }
            }
        }
    }
}

VOID
ExpSetSystemTime(
    IN BOOLEAN UpdateCmos,
    IN BOOLEAN UpdateInterruptTime,
    IN LARGE_INTEGER NewTime,
    OUT PLARGE_INTEGER PreviousTime
    )
{

    LARGE_INTEGER CmosTime;
    TIME_FIELDS TimeFields;

    //
    // If RTC is supposed to be set to UTC, use the NewTime value supplied; otherwise, convert the
    // supplied NewTime value into the local time value since the RTC is required to be set to the
    // local time.
    //

    if (ExpRealTimeIsUniversal) {
        CmosTime = NewTime;
    }
    else {
        ExSystemTimeToLocalTime(&NewTime, &CmosTime);
    }

    //
    // Set the system time
    //

    KeSetSystemTime(&NewTime, PreviousTime, UpdateInterruptTime, NULL);

    //
    // If Both flag is set and the system is not in CMOS mode, update the real time clock
    //

    if (UpdateCmos) {
        ExpRefreshTimeZoneInformation(&CmosTime);

        if (ExpRealTimeIsUniversal == FALSE &&
            ExpSystemIsInCmosMode == FALSE) {

            ExSystemTimeToLocalTime(&NewTime, &CmosTime);
            RtlTimeToTimeFields(&CmosTime, &TimeFields);
            ExCmosClockIsSane = HalSetRealTimeClock(&TimeFields);
        }
    }

    //
    // Notify other components that the system time has been set
    //

    PoNotifySystemTimeSet();
}

NTSTATUS
NtQueryTimerResolution(
    OUT PULONG MaximumTime,
    OUT PULONG MinimumTime,
    OUT PULONG CurrentTime
    )

/*++

Routine Description:

    This function returns the maximum, minimum, and current time between
    timer interrupts in 100ns units.

Arguments:

    MaximumTime - Supplies the address of a variable that receives the
        maximum time between interrupts.

    MinimumTime - Supplies the address of a variable that receives the
        minimum time between interrupts.

    CurrentTime - Supplies the address of a variable that receives the
        current time between interrupts.

Return Value:

    STATUS_SUCCESS is returned if the service is successfully executed.

    STATUS_ACCESS_VIOLATION is returned if an output parameter for one
        of the times cannot be written.

--*/

{

    KPROCESSOR_MODE PreviousMode;

    PAGED_CODE(); // 1580

    //
    // Establish an exception handler and attempt to write the time increment
    // values to the specified variables. If the write fails, then return the
    // exception code as the service status. Otherwise, return success as the
    // service status.
    //

    PreviousMode = KeGetPreviousMode();

    if (PreviousMode != KernelMode) {
        try {
            //
            // Get previous processor mode and probe argument if necessary.
            //
            ProbeForWriteUlong(MaximumTime);
            ProbeForWriteUlong(MinimumTime);
            ProbeForWriteUlong(CurrentTime);

            //
            // Store the maximum, minimum, and current times in the specified
            // variables.
            //

            *MaximumTime = KeMaximumIncrement;
            *MinimumTime = KeMinimumIncrement;
            *CurrentTime = KeTimeIncrement;
        } except (ExSystemExceptionFilter()) {
            //
            // If an exception occurs during the write of the time increment values,
            // then handle the exception if the previous mode was user, and return
            // the exception code as the status value.
            //

            return GetExceptionCode();
        }
    } else {
        //
        // Store the maximum, minimum, and current times in the specified
        // variables.
        //

        *MaximumTime = KeMaximumIncrement;
        *MinimumTime = KeMinimumIncrement;
        *CurrentTime = KeTimeIncrement;
    }

    return STATUS_SUCCESS;
}

NTSTATUS
NtSetTimerResolution(
    IN ULONG DesiredTime,
    IN BOOLEAN SetResolution,
    OUT PULONG ActualTime
    )

/*++

Routine Description:

    This function sets the current time between timer interrupts and
    returns the new value.

    N.B. The closest value that the host hardware can support is returned
        as the actual time.

Arguments:

    DesiredTime - Supplies the desired time between timer interrupts in
        100ns units.

    SetResoluion - Supplies a boolean value that determines whether the timer
        resolution is set (TRUE) or reset (FALSE).

    ActualTime - Supplies a pointer to a variable that receives the actual
        time between timer interrupts.

Return Value:

    STATUS_SUCCESS is returned if the service is successfully executed.

    STATUS_ACCESS_VIOLATION is returned if the output parameter for the
        actual time cannot be written.

--*/

{

    ULONG NewResolution;
    PEPROCESS Process;
    NTSTATUS Status;

    PAGED_CODE(); // 1663

    //
    // Get previous processor mode and probe argument if necessary.
    //

    if (KeGetPreviousMode() != KernelMode) {
        //
        // Establish an exception handler and attempt to set the timer resolution
        // to the specified value.
        //

        try {
            ProbeForWriteUlong(ActualTime);
        } except (ExSystemExceptionFilter()) {
            //
            // If an exception occurs during the write of the actual time increment,
            // then handle the exception if the previous mode was user, and return
            // the exception code as the status value.
            //

            return GetExceptionCode();
        }
    }

    Process = PsGetCurrentProcess();
    Status = STATUS_SUCCESS;


    //
    // Acquire the time refresh lock
    //

    ExAcquireTimeRefreshLock(TRUE);

    //
    // Set (SetResolution is TRUE) or reset (SetResolution is FALSE) the
    // timer resolution.
    //

    NewResolution = KeTimeIncrement;

    if (SetResolution == FALSE) {
        //
        // If the current process previously set the timer resolution,
        // then clear the set timer resolution flag and decrement the
        // timer resolution count. Otherwise, return an error.
        //

        if (!(PS_TEST_CLEAR_BITS(&Process->Flags, PS_PROCESS_FLAGS_SET_TIMER_RESOLUTION) & PS_PROCESS_FLAGS_SET_TIMER_RESOLUTION)) {
            Status = STATUS_TIMER_RESOLUTION_NOT_SET;
        } else {
            ExpTimerResolutionCount -= 1;

            //
            // If the timer resolution count is zero, the set the timer
            // resolution to the maximum increment value.
            //

            if (ExpTimerResolutionCount == 0) {
                KeSetSystemAffinityThread(1);
                NewResolution = HalSetTimeIncrement(KeMaximumIncrement);
                KeRevertToUserAffinityThread();
                KeTimeIncrement = NewResolution;
            }
        }
    } else {

        //
        // If the current process has not previously set the timer
        // resolution value, then set the set timer resolution flag
        // and increment the timer resolution count.
        //

        if (!(PS_TEST_SET_BITS(&Process->Flags, PS_PROCESS_FLAGS_SET_TIMER_RESOLUTION) & PS_PROCESS_FLAGS_SET_TIMER_RESOLUTION)) {
            ExpTimerResolutionCount += 1;
        }

        //
        // Compute the desired value as the maximum of the specified
        // value and the minimum increment value. If the desired value
        // is less than the current timer resolution value, then set
        // the timer resolution.
        //

        if (DesiredTime < KeMinimumIncrement) {
            DesiredTime = KeMinimumIncrement;
        }

        if (DesiredTime < KeTimeIncrement) {
            KeSetSystemAffinityThread(1);
            NewResolution = HalSetTimeIncrement(DesiredTime);
            KeRevertToUserAffinityThread();
            KeTimeIncrement = NewResolution;
        }
    }

    //
    // Release the time refresh lock
    //

    ExReleaseTimeRefreshLock();

    //
    // Attempt to write the new timer resolution. If the write attempt
    // fails, then do not report an error. When the caller attempts to
    // access the resolution value, and access violation will occur.
    //

    if (KeGetPreviousMode() != KernelMode) {
        try {
            *ActualTime = NewResolution;

        } except(ExSystemExceptionFilter()) {
            NOTHING;
        }
    } else {
        *ActualTime = NewResolution;
    }

    return Status;
}

ULONG
ExSetTimerResolution(
    IN ULONG DesiredTime,
    IN BOOLEAN SetResolution)
{

    ULONG NewIncrement;
    ULONG NewTime;

    PAGED_CODE(); // 1821

    ExAcquireTimeRefreshLock(TRUE);
    NewIncrement = KeTimeIncrement;

    if (!SetResolution) {

        ASSERT(ExpKernelResolutionCount != 0); // 1842

        if (ExpKernelResolutionCount != 0 &&
            !--ExpKernelResolutionCount &&
            !--ExpTimerResolutionCount) {

            KeSetSystemAffinityThread(1);
            NewIncrement = HalSetTimeIncrement(KeMaximumIncrement);
            KeRevertToUserAffinityThread();
            KeTimeIncrement = NewIncrement;
        }
    }
    else {

        if (ExpKernelResolutionCount == 0) {
            ++ExpTimerResolutionCount;
        }

        ++ExpKernelResolutionCount;

        NewTime = DesiredTime;

        if (NewTime < KeMinimumIncrement) {
            NewTime = KeMinimumIncrement;
        }

        if (NewTime < KeTimeIncrement) {
            KeSetSystemAffinityThread(1);
            NewIncrement = HalSetTimeIncrement(NewTime);
            KeRevertToUserAffinityThread();
            KeTimeIncrement = NewIncrement;
        }
    }

    ExReleaseTimeRefreshLock();
    return NewIncrement;
}

VOID
ExSystemTimeToLocalTime(
    IN PLARGE_INTEGER SystemTime,
    OUT PLARGE_INTEGER LocalTime
    )
{

    //
    // LocalTime = SystemTime - TimeZoneBias
    //

    LocalTime->QuadPart = SystemTime->QuadPart - ExpTimeZoneBias.QuadPart;
}

VOID
NTAPI
ExLocalTimeToSystemTime(
    IN PLARGE_INTEGER LocalTime,
    OUT PLARGE_INTEGER SystemTime
    )
{

    //
    // SystemTime = LocalTime + TimeZoneBias
    //

    SystemTime->QuadPart = LocalTime->QuadPart + ExpTimeZoneBias.QuadPart;
}

VOID
ExShutdownSystem(
    IN ULONG Phase
    )
{

    UNICODE_STRING KeyName;
    UNICODE_STRING KeyValueName;
    OBJECT_ATTRIBUTES ObjectAttributes;
    NTSTATUS Status;
    HANDLE Key;

    ULONG ValueInfoBuffer[sizeof(KEY_VALUE_PARTIAL_INFORMATION) + 2];
    PKEY_VALUE_PARTIAL_INFORMATION ValueInfo;
    LARGE_INTEGER SystemPrefix;
    LARGE_INTEGER ShutDownTime;
    ULONG NumberOfProcessors;
    ULONG DataLength;

    if (!Phase) {
        ExpTooLateForErrors = TRUE;

        //
        // If the system booted with an expiration time, rewrite the expiration data.
        // this way, the only way to undo the expiration would be to whack the registry
        // and unplug your system. Any sort of clean shutdown would undo your registry whack
        //

        if ( ExpNtExpirationData[1] ) {

            ExpShuttingDown = TRUE;

            RtlInitUnicodeString(&KeyName,L"\\Registry\\Machine\\System\\CurrentControlSet\\Control\\Session Manager\\Executive");

            InitializeObjectAttributes( &ObjectAttributes,
                                        &KeyName,
                                        OBJ_CASE_INSENSITIVE,
                                        NULL,
                                        NULL
                                      );
            Status = NtOpenKey( &Key,
                                GENERIC_WRITE,
                                &ObjectAttributes
                              );

            if ( !NT_SUCCESS(Status) ) {
                return;
            }

            //
            // we have the key open so write our data out
            //

            RtlInitUnicodeString( &KeyValueName, L"PriorityQuantumMatrix" );

            NtSetValueKey( Key,
                           &KeyValueName,
                           0,
                           REG_BINARY,
                           &ExpNtExpirationData[0],
                           sizeof(ExpNtExpirationData)
                         );

            NtFlushKey(Key);
            NtClose(Key);

        }

        if ( !ExpInTextModeSetup ) {

            ExpShuttingDown = TRUE;

            if ( ExpSetupModeDetected ) {

                //
                // If we are not in text mode setup, open SetupKey so we
                // can store shutdown time
                //

                RtlInitUnicodeString(&KeyName,L"\\Registry\\Machine\\System\\Setup");

                InitializeObjectAttributes( &ObjectAttributes,
                                            &KeyName,
                                            OBJ_CASE_INSENSITIVE,
                                            NULL,
                                            NULL
                                          );

                Status = NtOpenKey( &Key,
                                    KEY_READ | KEY_WRITE | KEY_NOTIFY,
                                    &ObjectAttributes
                                  );

                if ( !NT_SUCCESS(Status) ) {
                    return;
                    }


                //
                // Pick up the system prefix data
                //

                RtlInitUnicodeString( &KeyValueName, L"SystemPrefix" );

                ValueInfo = (PKEY_VALUE_PARTIAL_INFORMATION)ValueInfoBuffer;

                Status = NtQueryValueKey( Key,
                                          &KeyValueName,
                                          KeyValuePartialInformation,
                                          ValueInfo,
                                          sizeof(ValueInfoBuffer),
                                          &DataLength
                                        );

                NtClose(Key);

                if ( NT_SUCCESS(Status) ) {

                    RtlCopyMemory(&SystemPrefix, &ValueInfo->Data, sizeof(LARGE_INTEGER));

                }
                else {
                    return;
                }
            }
            else {
                SystemPrefix = ExpSetupSystemPrefix;
            }


            KeQuerySystemTime(&ShutDownTime);

            //
            // Clear low 6 bits of time
            //

            ShutDownTime.LowPart &= ~0x0000003F;

            //
            // If we have never gone through the refresh count logic,
            // Do it now
            //

            if (ExpRefreshCount == 0) {
                ExpRefreshCount++;

                //
                // first time through time refresh. If we are not in setup mode
                // then make sure shutdowntime is in good shape
                //
                if ( !ExpSetupModeDetected && !ExpInTextModeSetup ) {
                    if ( ExpLastShutDown.QuadPart ) {
                        NumberOfProcessors = SystemPrefix.LowPart;
                        NumberOfProcessors = NumberOfProcessors >> 5;
                        NumberOfProcessors = NumberOfProcessors & 0x0000001f;

                        ExpLastShutDown.LowPart &= 0x3f;


                        if ( SystemPrefix.HighPart & 0x04000000 ) {

                            if ( (ExpLastShutDown.LowPart >> 1 != NumberOfProcessors) ||
                                 (ExpLastShutDown.LowPart & 1) == 0 ) {

                                ExpLastShutDown.HighPart = 0;

                            }
                            else {
                                if ( ExpLastShutDown.HighPart == 0 ) {
                                    ExpLastShutDown.HighPart = 1;
                                    }
                            }
                        }
                        else {
                            if ( (ExpLastShutDown.LowPart >> 1 != NumberOfProcessors) ||
                                 (ExpLastShutDown.LowPart & 1) ) {

                                ExpLastShutDown.HighPart = 0;

                            }
                            else {
                                if ( ExpLastShutDown.HighPart == 0 ) {
                                    ExpLastShutDown.HighPart = 1;
                                    }
                            }
                        }
                        ExpLastShutDown.LowPart |= 0x40;
                    }
                }
                else {
                    ExpLastShutDown.QuadPart = 0;
                }
            }


            if ( ExpLastShutDown.QuadPart && ExpLastShutDown.HighPart == 0 ) {
                ShutDownTime.LowPart |= ExpLastShutDown.LowPart;
            }
            else {
                NumberOfProcessors = SystemPrefix.LowPart;
                NumberOfProcessors = NumberOfProcessors >> 4;
                NumberOfProcessors = NumberOfProcessors & 0x0000003E;

                ShutDownTime.LowPart |= NumberOfProcessors;

                if ( SystemPrefix.HighPart & 0x04000000 ) {
                    ShutDownTime.LowPart |= 1;
                }
            }

            RtlInitUnicodeString(&KeyName,L"\\Registry\\Machine\\System\\CurrentControlSet\\Control\\Windows");

            InitializeObjectAttributes( &ObjectAttributes,
                                        &KeyName,
                                        OBJ_CASE_INSENSITIVE,
                                        NULL,
                                        NULL
                                      );

            Status = NtOpenKey( &Key,
                                KEY_READ | KEY_WRITE | KEY_NOTIFY,
                                &ObjectAttributes
                              );

            if ( !NT_SUCCESS(Status) ) {
                return;
                }

            RtlInitUnicodeString( &KeyValueName, L"ShutdownTime" );

            NtSetValueKey( Key,
                    &KeyValueName,
                    0,
                    REG_BINARY,
                    &ShutDownTime,
                    sizeof(ShutDownTime)
                    );

            NtFlushKey(Key);
            NtClose(Key);
        }

        //
        // If the kernel is running the text mode setup, dereference the kernel objects
        // dynamically allocated by the executive.
        //

        if (ExpDefaultErrorPort != NULL) {
            ObfDereferenceObject(ExpDefaultErrorPort);
            ExpDefaultErrorPort = NULL;
        }

        if (ExpDefaultErrorPortProcess != NULL) {
            ObfDereferenceObject(ExpDefaultErrorPortProcess);
            ExpDefaultErrorPortProcess = NULL;
        }

        ExAcquireResourceExclusiveLite(&ExpKeyManipLock, TRUE);

        if (ExpControlKey[0] != NULL) {
            ObfDereferenceObject(ExpControlKey[0]);
            ExpControlKey[0] = NULL;
        }

        if (ExpControlKey[1] != NULL) {
            ObfDereferenceObject(ExpControlKey[1]);
            ExpControlKey[1] = NULL;
        }

        if (ExpExpirationDataKey != NULL) {
            ObCloseHandle(ExpExpirationDataKey, FALSE);
            ExpExpirationDataKey = NULL;
        }

        if (ExpProductTypeKey != NULL) {
            ObCloseHandle(ExpProductTypeKey, FALSE);
            ExpProductTypeKey = NULL;
        }

        if (ExpSetupKey != NULL) {
            ObCloseHandle(ExpSetupKey, FALSE);
            ExpSetupKey = NULL;
        }

        ExReleaseResourceLite(&ExpKeyManipLock);

        return;
    }

    if (Phase == 1) {
        if ((PoCleanShutdownEnabled() & PO_CLEAN_SHUTDOWN_PAGING) != 0) {
            ExSwapinWorkerThreads(FALSE);
        }
    }
    else {
        ASSERT(Phase == 2); // 2190 / 2239

        if ((PoCleanShutdownEnabled() & PO_CLEAN_SHUTDOWN_WORKERS) != 0) {
            ExpShutdownWorkerThreads();
        }

        ExDeleteResourceLite(&ExpKeyManipLock);
    }
}

VOID
ExpExpirationThread(
    IN PVOID StartContext
    )
{

    NTSTATUS Status;
    ULONG Response;

    if ( StartContext ) {

        //
        // raise the hard error warning of impending license expiration
        //

        Status = ExRaiseHardError(
                    (NTSTATUS)((ULONG_PTR)StartContext & 0xFFFFFFFF),
                    0,
                    0,
                    NULL,
                    OptionOk,
                    &Response
                    );
        PsTerminateSystemThread(Status);

    }

}

#ifdef WPA_CHECK

VOID
ExpWatchExpirationDataWork(
    IN PVOID Context
    )
{

    UNICODE_STRING KeyName;
    UNICODE_STRING KeyValueName;
    OBJECT_ATTRIBUTES ObjectAttributes;
    NTSTATUS Status;
    BOOLEAN RegistryLocked = FALSE;

    UNREFERENCED_PARAMETER(Context);

    //
    // our change notify triggered. Simply rewrite the boot time product type
    // back out to the registry
    //

    ExAcquireResourceSharedLite(&ExpKeyManipLock, 1);

    if (!ExpExpirationDataKey) {
        goto Cleanup;
    }

    ZwClose(ExpExpirationDataKey);
    ExpExpirationDataKey = NULL;

    if (!ExpShuttingDown) {
        RtlInitUnicodeString(&KeyName,L"\\Registry\\Machine\\System\\CurrentControlSet\\Control\\Session Manager\\Executive");

        InitializeObjectAttributes( &ObjectAttributes,
                                    &KeyName,
                                    OBJ_CASE_INSENSITIVE,
                                    NULL,
                                    NULL
                                  );
        Status = ZwOpenKey( &ExpExpirationDataKey,
                            KEY_READ | KEY_NOTIFY | KEY_WRITE,
                            &ObjectAttributes
                          );

        if (NT_SUCCESS(Status)) {

            if (!ExpSetupModeDetected) {

                RtlInitUnicodeString(&KeyValueName, L"PriorityQuantumMatrix");

                CmpLockRegistryExclusive();
                RegistryLocked = TRUE;

                ZwSetValueKey( ExpExpirationDataKey,
                               &KeyValueName,
                               0,
                               REG_BINARY,
                               &ExpNtExpirationData[0],
                               sizeof(ExpNtExpirationData)
                             );

                ZwFlushKey(ExpExpirationDataKey);
            }

            ZwNotifyChangeKey(
                  ExpExpirationDataKey,
                  NULL,
                  (PIO_APC_ROUTINE)&ExpWatchExpirationDataWorkItem,
                  (PVOID)DelayedWorkQueue,
                  &ExpExpirationDataIoSb,
                  REG_LEGAL_CHANGE_FILTER,
                  FALSE,
                  &ExpExpirationDataChangeBuffer,
                  sizeof(ExpExpirationDataChangeBuffer),
                  TRUE
                );

            if (RegistryLocked) {
                CmpUnlockRegistry();
            }
        }
    }

Cleanup:
    ExReleaseResourceLite(&ExpKeyManipLock);
}

#endif
