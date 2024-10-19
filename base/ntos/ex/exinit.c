/*++

Copyright (c) 1989  Microsoft Corporation

Module Name:

    exinit.c

Abstract:

    The module contains the the initialization code for the executive
    component. It also contains the display string and shutdown system
    services.

Author:

    Steve Wood (stevewo) 31-Mar-1989

Revision History:

--*/

#include "exp.h"
#include <zwapi.h>
#include <ntregapi.h>
#include <inbv.h>
#include "safeboot.h"

// Disable warning about WORK_QUEUE_ITEM/PIO_APC_ROUTINE casts
// (those are fine, NtNotifyChangeKey is setup to allow taking a WORK_QUEUE_ITEM*)
#pragma warning(disable:4055)

//
// Define forward referenced prototypes.
//

// from cmp.h, but it seems exinit.c isn't meant to include that (based on IA64 exinit.obj)
VOID
CmpLockRegistryExclusive(
    VOID
    );

VOID
CmpUnlockRegistry(
    );

ULONG
static
ExpSingleStringCheck (
    LPWSTR s1
    );

VOID
static
ExpStringCheck (
    LPWSTR s1,
    LPWSTR s2,
    LPWSTR s3,
    LPWSTR s4,
    LPWSTR s5,
    LPWSTR s6,
    LPWSTR s7,
    LPWSTR s8,
    LPWSTR s9,
    LPWSTR s10,
    LPWSTR s11,
    LPWSTR s12,
    LPWSTR s13,
    LPWSTR s14,
    LPWSTR s15,
    LPWSTR s16,
    LPWSTR s17,
    LPWSTR s18,
    LPWSTR s19,
    LPWSTR s20,
    LPWSTR s21,
    LPWSTR s22,
    LPWSTR s23
    );


#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, ExpSingleStringCheck)
#pragma alloc_text(INIT, ExpStringCheck)
#pragma alloc_text(INIT, ExInitPoolLookasidePointers)
#pragma alloc_text(PAGE, ExpWatchLicenseInfoWork)
#pragma alloc_text(PAGE, ExpWatchProductTypeWork)
#pragma alloc_text(PAGE, ExpWatchSystemPrefixWork)
#pragma alloc_text(INIT, ExpWatchProductTypeInitialization)
#pragma alloc_text(INIT, ExInitSystemPhase2)
#pragma alloc_text(INIT, ExComputeTickCountMultiplier)
#pragma alloc_text(PAGE, NtShutdownSystem)
#pragma alloc_text(PAGE, NtDisplayString)
#pragma alloc_text(PAGE, ExSystemExceptionFilter)
#pragma alloc_text(INIT, ExInitializeSystemLookasideList)
#pragma alloc_text(INIT, ExpInitSystemPhase0)
#pragma alloc_text(INIT, ExpInitSystemPhase1)
#pragma alloc_text(INIT, ExInitSystem)
#endif

ERESOURCE ExpKeyManipLock;

//
// Tick count multiplier.
//

ULONG ExpTickCountMultiplier;

extern WCHAR CmSuiteBuffer[128];
extern ULONG CmSuiteBufferLength;
extern ULONG CmSuiteBufferType;

ULONG ExpHydraEnabled;
static ULONG ExpSuiteMask;

// TODO: these three should be somewhere else!
static KEY_VALUE_PARTIAL_INFORMATION *ExpProductSuiteValueInfo;
EXP_LICENSE_INFO *ExpLicenseInfo;
ULONG ExpLicenseInfoCount;
extern BOOLEAN ExpShuttingDown;

#ifdef ALLOC_DATA_PRAGMA
#pragma data_seg("INITDATA")
#endif

ULONG ExpMultiUserTS = TRUE;

#ifdef ALLOC_DATA_PRAGMA
#pragma data_seg()
#endif

#ifdef ALLOC_DATA_PRAGMA
#pragma const_seg("PAGECONST")
#endif

#define EXP_ST_SETUP              0
#define EXP_ST_SETUP_TYPE         1
#define EXP_ST_SYSTEM_PREFIX      2
#define EXP_ST_PRODUCT_OPTIONS    3
#define EXP_ST_PRODUCT_TYPE       4
#define EXP_ST_LANMANNT           5
#define EXP_ST_SERVERNT           6
#define EXP_ST_WINNT              7
#define EXP_ST_PRODUCT_SUITE      8
#define EXP_ST_LICENSE_INFO       9
#define EXP_ST_CONCURRENT_LIMIT  10
#define EXP_ST_SUITE_SBS         11
#define EXP_ST_SUITE_ENTERPRISE  12
#define EXP_ST_SUITE_COMSRV      13
#define EXP_ST_SUITE_BACKOFFICE  14
#define EXP_ST_SUITE_SBSREST     15
#define EXP_ST_SUITE_TRMSRV      16
#define EXP_ST_SUITE_EMBED       17
#define EXP_ST_SUITE_DTC         18
#define EXP_ST_SUITE_PERSONAL    19
#define EXP_ST_SUITE_BLADE       20
#define EXP_ST_SUITE_EMBEDRES    21
#define EXP_ST_SUITE_SECURITY    22
LPWSTR
const
ExpStrings[23] = {
    L"\\Registry\\Machine\\System\\Setup",
    L"SetupType",
    L"SystemPrefix",
    L"\\Registry\\Machine\\System\\CurrentControlSet\\Control\\ProductOptions",
    L"ProductType",
    L"LanmanNT",
    L"ServerNT",
    L"WinNT",
    L"ProductSuite",
    L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\LicenseInfoSuites",
    L"ConcurrentLimit",
    L"Small Business",
    L"Enterprise",
    L"CommunicationServer",
    L"BackOffice",
    L"Small Business(Restricted)",
    L"Terminal Server",
    L"EmbeddedNT",
    L"DataCenter",
    L"Personal",
    L"Blade",
    L"Embedded(Restricted)",
    L"Security Appliance"
};

#ifdef ALLOC_DATA_PRAGMA
#pragma const_seg("INITCONST")
#endif

ULONG
static
ExpSingleStringCheck (
    LPWSTR s1
    )
{

    UNICODE_STRING DestinationString;

    RtlInitUnicodeString(&DestinationString, s1);
    return RtlComputeCrc32(0, DestinationString.Buffer, DestinationString.Length);
}

ULONG KdDumpEnableOffset;

VOID
static
ExpStringCheck (
    LPWSTR s1,
    LPWSTR s2,
    LPWSTR s3,
    LPWSTR s4,
    LPWSTR s5,
    LPWSTR s6,
    LPWSTR s7,
    LPWSTR s8,
    LPWSTR s9,
    LPWSTR s10,
    LPWSTR s11,
    LPWSTR s12,
    LPWSTR s13,
    LPWSTR s14,
    LPWSTR s15,
    LPWSTR s16,
    LPWSTR s17,
    LPWSTR s18,
    LPWSTR s19,
    LPWSTR s20,
    LPWSTR s21,
    LPWSTR s22,
    LPWSTR s23
    )
{

    static const ULONG Master[23] = {
        0xf54d3d83,
        0x6d3cbfaf,
        0x1418a31c,
        0xe7535704,
        0x720e8093,
        0x1aec49bf,
        0x4d8f8978,
        0xe00497a3,
        0x9788c875,
        0x6aa44e66,
        0x17d632cf,
        0x21bd473b,
        0x72deed9b,
        0xdb4f8357,
        0xbd7ed200,
        0x064f25ee,
        0x0c37a2ff,
        0xee72022f,
        0x52cc749d,
        0x88742b75,
        0x91e72956,
        0x6b09dc7a,
        0x21d28371
    };

    ULONG StringCheckV[23];
    int i;

    StringCheckV[0] = ExpSingleStringCheck(s1);
    StringCheckV[1] = ExpSingleStringCheck(s2);
    StringCheckV[2] = ExpSingleStringCheck(s3);
    StringCheckV[3] = ExpSingleStringCheck(s4);
    StringCheckV[4] = ExpSingleStringCheck(s5);
    StringCheckV[5] = ExpSingleStringCheck(s6);
    StringCheckV[6] = ExpSingleStringCheck(s7);
    StringCheckV[7] = ExpSingleStringCheck(s8);
    StringCheckV[8] = ExpSingleStringCheck(s9);
    StringCheckV[9] = ExpSingleStringCheck(s10);
    StringCheckV[10] = ExpSingleStringCheck(s11);
    StringCheckV[11] = ExpSingleStringCheck(s12);
    StringCheckV[12] = ExpSingleStringCheck(s13);
    StringCheckV[13] = ExpSingleStringCheck(s14);
    StringCheckV[14] = ExpSingleStringCheck(s15);
    StringCheckV[15] = ExpSingleStringCheck(s16);
    StringCheckV[16] = ExpSingleStringCheck(s17);
    StringCheckV[17] = ExpSingleStringCheck(s18);
    StringCheckV[18] = ExpSingleStringCheck(s19);
    StringCheckV[19] = ExpSingleStringCheck(s20);
    StringCheckV[20] = ExpSingleStringCheck(s21);
    StringCheckV[21] = ExpSingleStringCheck(s22);
    StringCheckV[22] = ExpSingleStringCheck(s23);

    for (i=0; i < 23; i++) {
        if (StringCheckV[i] != Master[i]) {
            KdDumpEnableOffset = 8;
        }
    }

}

VOID
ExInitPoolLookasidePointers (
    VOID
    )

/*++

Routine Description:

    This function initializes the PRCB lookaside pointers to temporary
    values that will be updated during phase 1 initialization.

Arguments:

    None.

Return Value:

    None.

--*/

{

    ULONG Index;
    PGENERAL_LOOKASIDE Lookaside;
    PKPRCB Prcb;

    //
    // Initialize the paged and nonpaged small pool lookaside list
    // pointers in the PRCB to temporarily point to the global pool
    // lookaside lists. During phase 1 initialization per processor
    // lookaside lists are allocated and the pointer to these lists
    // are established in the PRCB of each processor.
    //

    Prcb = KeGetCurrentPrcb();
    for (Index = 0; Index < POOL_SMALL_LISTS; Index += 1) {
        Lookaside = &ExpSmallNPagedPoolLookasideLists[Index];
        ExInitializeSListHead(&Lookaside->ListHead);
        Prcb->PPNPagedLookasideList[Index].P = Lookaside;
        Prcb->PPNPagedLookasideList[Index].L = Lookaside;

        Lookaside = &ExpSmallPagedPoolLookasideLists[Index];
        ExInitializeSListHead(&Lookaside->ListHead);
        Prcb->PPPagedLookasideList[Index].P = Lookaside;
        Prcb->PPPagedLookasideList[Index].L = Lookaside;
    }

    return;
}

BOOLEAN
ExInitSystem (
    VOID
    )

/*++

Routine Description:

    This function initializes the executive component of the NT system.
    It will perform Phase 0 or Phase 1 initialization as appropriate.

Arguments:

    None.

Return Value:

    A value of TRUE is returned if the initialization is successful. Otherwise
    a value of FALSE is returned.

--*/

{

    switch ( InitializationPhase ) {

    case 0:
        ExpStringCheck(
            ExpStrings[EXP_ST_SETUP],
            ExpStrings[EXP_ST_SETUP_TYPE],
            ExpStrings[EXP_ST_SYSTEM_PREFIX],
            ExpStrings[EXP_ST_PRODUCT_OPTIONS],
            ExpStrings[EXP_ST_PRODUCT_TYPE],
            ExpStrings[EXP_ST_LANMANNT],
            ExpStrings[EXP_ST_SERVERNT],
            ExpStrings[EXP_ST_WINNT],
            ExpStrings[EXP_ST_PRODUCT_SUITE],
            ExpStrings[EXP_ST_LICENSE_INFO],
            ExpStrings[EXP_ST_CONCURRENT_LIMIT],
            ExpStrings[EXP_ST_SUITE_SBS],
            ExpStrings[EXP_ST_SUITE_ENTERPRISE],
            ExpStrings[EXP_ST_SUITE_COMSRV],
            ExpStrings[EXP_ST_SUITE_BACKOFFICE],
            ExpStrings[EXP_ST_SUITE_SBSREST],
            ExpStrings[EXP_ST_SUITE_TRMSRV],
            ExpStrings[EXP_ST_SUITE_EMBED],
            ExpStrings[EXP_ST_SUITE_DTC],
            ExpStrings[EXP_ST_SUITE_PERSONAL],
            ExpStrings[EXP_ST_SUITE_BLADE],
            ExpStrings[EXP_ST_SUITE_EMBEDRES],
            ExpStrings[EXP_ST_SUITE_SECURITY]
            );

        return ExpInitSystemPhase0();
    case 1:
        return ExpInitSystemPhase1();
    default:
        KeBugCheckEx(UNEXPECTED_INITIALIZATION_CALL, 3, InitializationPhase, 0, 0);
    }
}

BOOLEAN
ExpInitSystemPhase0 (
    VOID
    )

/*++

Routine Description:

    This function performs Phase 0 initialization of the executive component
    of the NT system.

Arguments:

    None.

Return Value:

    A value of TRUE is returned if the initialization is success. Otherwise
    a value of FALSE is returned.

--*/

{

    ULONG Index;
    BOOLEAN Initialized = TRUE;
    PGENERAL_LOOKASIDE Lookaside;

    WCHAR* CurSuite;

    //
    // Initialize Resource objects, currently required during SE
    // Phase 0 initialization.
    //

    if (ExpResourceInitialization() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Resource initialization failed\n"));
    }

    //
    // Initialize query/set environment variable synchronization fast
    // mutex.
    //

    ExInitializeFastMutex(&ExpEnvironmentLock);

    //
    // Initialize the key manipulation resource.
    //

    ExInitializeResourceLite(&ExpKeyManipLock);

    //
    // Initialize the paged and nonpaged small pool lookaside structures,
    //

    InitializeListHead(&ExPoolLookasideListHead);
    for (Index = 0; Index < POOL_SMALL_LISTS; Index += 1) {
        Lookaside = &ExpSmallNPagedPoolLookasideLists[Index];
        ExInitializeSystemLookasideList(Lookaside,
                                        NonPagedPool,
                                        (Index + 1) * sizeof (POOL_BLOCK),
                                        'looP',
                                        256,
                                        &ExPoolLookasideListHead);

        Lookaside = &ExpSmallPagedPoolLookasideLists[Index];
        ExInitializeSystemLookasideList(Lookaside,
                                        PagedPool,
                                        (Index + 1) * sizeof (POOL_BLOCK),
                                        'looP',
                                        256,
                                        &ExPoolLookasideListHead);
    }

    //
    // Initialize the nonpaged and paged system lookaside lists.
    //

    InitializeListHead(&ExNPagedLookasideListHead);
    KeInitializeSpinLock(&ExNPagedLookasideLock);
    InitializeListHead(&ExPagedLookasideListHead);
    KeInitializeSpinLock(&ExPagedLookasideLock);

    //
    // Initialize the system paged and nonpaged lookaside list.
    //

    InitializeListHead(&ExSystemLookasideListHead);

    if (CmSuiteBufferType == REG_MULTI_SZ && CmSuiteBuffer[0] != 0) {
        CurSuite = CmSuiteBuffer;
        do {

            if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_SBS]) == 0) {
                ExpSuiteMask |= 0x1; // TODO: Use a proper definition
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_SBSREST]) == 0) {
                ExpSuiteMask |= 0x20;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_ENTERPRISE]) == 0) {
                ExpSuiteMask |= 0x2;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_COMSRV]) == 0) {
                ExpSuiteMask |= 0x8;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_BACKOFFICE]) == 0) {
                ExpSuiteMask |= 0x4;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_TRMSRV]) == 0) {
                ExpSuiteMask |= 0x10;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_EMBED]) == 0) {
                ExpSuiteMask |= 0x40;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_DTC]) == 0) {
                ExpSuiteMask |= 0x80;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_PERSONAL]) == 0) {
                ExpSuiteMask |= 0x200;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_BLADE]) == 0) {
                ExpSuiteMask |= 0x400;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_EMBEDRES]) == 0) {
                ExpSuiteMask |= 0x800;
            }
            else if (wcscmp(CurSuite, ExpStrings[EXP_ST_SUITE_SECURITY]) == 0) {
                ExpSuiteMask |= 0x1000;
            }

            // 4chan todo: these aren't checked in SP0 exinit.obj
#if 0
            else if (wcscmp(CurSuite, L"Storage Server") == 0) {
                ExpSuiteMask |= 0x2000;
            }
            else if (wcscmp(CurSuite, L"Compute Server") == 0) {
                ExpSuiteMask |= 0x4000;
            }
#endif

            CurSuite += wcslen(CurSuite) + 1;
        }
        while (*CurSuite != 0);
    }

    return Initialized;
}

VOID
static
ExpWatchLicenseInfoWork(
    PEXP_LICENSE_INFO LicenseInfo
    )
{

    NTSTATUS Status;

    KEY_FULL_INFORMATION KeyInfo;
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING LimitValueName;
    UNICODE_STRING SubKeyName;
    HANDLE Thread;
    ULONG ResultLength;
    HANDLE hSubKey;
    ULONG Index;
    SIZE_T Size;

    PKEY_BASIC_INFORMATION KeyBuffer;

    if (!ExpSetupModeDetected) {

        RtlInitUnicodeString(&SubKeyName, LicenseInfo->SubKeyName);

        InitializeObjectAttributes( &ObjectAttributes,
                                    &SubKeyName,
                                    OBJ_CASE_INSENSITIVE,
                                    NULL,
                                    NULL
                                  );

        NtClose(LicenseInfo->RegKey);

        Status = NtOpenKey(&LicenseInfo->RegKey, KEY_READ | KEY_WRITE, &ObjectAttributes);
        if (!NT_SUCCESS(Status)) {
            KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x12, Status, 0, 0);
        }

        Status = NtQueryKey(LicenseInfo->RegKey, KeyFullInformation, &KeyInfo, sizeof(KeyInfo), &ResultLength);
        if (!NT_SUCCESS(Status)) {
            KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x13, Status, 0, 0);
        }

        Size = sizeof(WCHAR) * KeyInfo.MaxNameLen + 56; // todo: what is 56?

        KeyBuffer = (PKEY_BASIC_INFORMATION)ExAllocatePoolWithTag(0, Size, ' yeK');
        if (!KeyBuffer) {
            KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x14, Size, 0, 0);
        }

        SubKeyName.MaximumLength =
            SubKeyName.Length =
                (USHORT)(sizeof(WCHAR) * (KeyInfo.MaxNameLen + wcslen(&LicenseInfo->SubKeyName[0x10])));

        SubKeyName.Buffer = (PWSTR)ExAllocatePoolWithTag(0, SubKeyName.Length, ' yeK');
        if (!SubKeyName.Buffer) {
            KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x14, SubKeyName.Length, 1, 0);
        }

        RtlInitUnicodeString(&LimitValueName, ExpStrings[EXP_ST_CONCURRENT_LIMIT]);

        Status = NtSetValueKey(
            LicenseInfo->RegKey,
            &LimitValueName,
            0,
            REG_DWORD,
            &LicenseInfo->Count,
            sizeof(LicenseInfo->Count)
            );

        if (!NT_SUCCESS(Status)) {
            KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x15, Status, 0, 0);
        }

        Index = 0;

        while ((Status = NtEnumerateKey(LicenseInfo->RegKey, Index, 0, KeyBuffer, (ULONG)Size, &ResultLength))
            != STATUS_NO_MORE_ENTRIES) {

            if (NT_SUCCESS(Status)) {
                KeyBuffer->Name[KeyBuffer->NameLength / sizeof(WCHAR)] = 0;

                wcscpy(SubKeyName.Buffer, LicenseInfo->SubKeyName);
                wcscat(SubKeyName.Buffer, L"\\");
                wcscat(SubKeyName.Buffer, KeyBuffer->Name);

                SubKeyName.Length = (USHORT)(sizeof(WCHAR) * wcslen(SubKeyName.Buffer));

                InitializeObjectAttributes( &ObjectAttributes,
                                            &SubKeyName,
                                            OBJ_CASE_INSENSITIVE,
                                            NULL,
                                            NULL
                                          );

                Status = NtOpenKey(&hSubKey, KEY_READ | KEY_WRITE, &ObjectAttributes);
                if (!NT_SUCCESS(Status)) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x16, Status, 0, 0);
                }

                Status = NtSetValueKey(
                    hSubKey,
                    &LimitValueName,
                    0,
                    REG_DWORD,
                    &LicenseInfo->Count,
                    sizeof(LicenseInfo->Count)
                    );

                if (!NT_SUCCESS(Status)) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x17, Status, 0, 0);
                }

                NtClose(hSubKey);
            }
            ++Index;
        }

        ExFreePoolWithTag(KeyBuffer, 0);
        ExFreePoolWithTag(SubKeyName.Buffer, 0);
    }

    Status = NtNotifyChangeKey(
        LicenseInfo->RegKey,
        NULL,
        (PIO_APC_ROUTINE)(void*)&LicenseInfo->ExpWatchLicenseInfoWorkItem,
        (PVOID)DelayedWorkQueue,
        &LicenseInfo->ExpLicenseInfoIoSb,
        (REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET),
        TRUE,
        &LicenseInfo->ExpLicenseInfoChangeBuffer,
        sizeof(LicenseInfo->ExpLicenseInfoChangeBuffer),
        TRUE);

    if (!NT_SUCCESS(Status)) {
        KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x18, Status, 0, 0);
    }

    if (ExpSetupModeDetected) {
        return;
    }

    Status = PsCreateSystemThread(&Thread,
        THREAD_ALL_ACCESS,
        NULL,
        0L,
        NULL,
        ExpExpirationThread,
        (PVOID)STATUS_LICENSE_VIOLATION
        );

    if (NT_SUCCESS(Status)) {
        ZwClose(Thread);
    }
}

#define MAX_PRODUCT_TYPE_BYTES  18       // lanmannt, servernt, winnt are only options

HANDLE ExpProductTypeKey;
PKEY_VALUE_PARTIAL_INFORMATION ExpProductTypeValueInfo;
ULONG ExpProductTypeChangeBuffer;
ULONG ExpSystemPrefixChangeBuffer;
IO_STATUS_BLOCK ExpProductTypeIoSb;
IO_STATUS_BLOCK ExpSystemPrefixIoSb;
WORK_QUEUE_ITEM ExpWatchProductTypeWorkItem;
WORK_QUEUE_ITEM ExpWatchSystemPrefixWorkItem;
BOOLEAN ExpInTextModeSetup;

VOID
ExpWatchProductTypeWork(
    PVOID Context
    )
{

    NTSTATUS Status;

    UCHAR ValueBuffer[34];
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING KeyName;
    UNICODE_STRING KeyValueName;
    ULONG ValueSize;
    HANDLE Thread;
    BOOLEAN IllegalChange = TRUE;
    BOOLEAN RegistryLocked = FALSE;

    PKEY_VALUE_PARTIAL_INFORMATION ValueInfo = (PKEY_VALUE_PARTIAL_INFORMATION)ValueBuffer;

    UNREFERENCED_PARAMETER(Context);

    ExAcquireResourceSharedLite(&ExpKeyManipLock, 1);

    if (!ExpProductTypeKey) {
        goto Cleanup;
    }

    NtClose(ExpProductTypeKey);
    ExpProductTypeKey = 0;

    RtlInitUnicodeString(&KeyName, ExpStrings[EXP_ST_PRODUCT_OPTIONS]);

    InitializeObjectAttributes( &ObjectAttributes,
                                &KeyName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );

    Status = NtOpenKey(&ExpProductTypeKey, KEY_READ | KEY_WRITE, &ObjectAttributes);
    if (!NT_SUCCESS(Status)) {
        KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 13, Status, 0, 0);
    }

    if (!ExpSetupModeDetected) {
        RtlInitUnicodeString(&KeyValueName, ExpStrings[EXP_ST_PRODUCT_TYPE]);
        if ( NtQueryValueKey(
                 ExpProductTypeKey,
                 &KeyValueName,
                 KeyValuePartialInformation,
                 ValueBuffer,
                 sizeof(ValueBuffer),
                 &ValueSize) >= 0
                 ) {

            RegistryLocked = (BOOLEAN) (
                !wcscmp(ExpStrings[EXP_ST_LANMANNT], (wchar_t*)ValueInfo->Data) ||
                !wcscmp(ExpStrings[EXP_ST_SERVERNT], (wchar_t*)ValueInfo->Data)
            );

            if (wcscmp(ExpStrings[EXP_ST_WINNT], (wchar_t *)ExpProductTypeValueInfo->Data) && RegistryLocked) {
                ASSERT(ExpProductTypeValueInfo->DataLength == ValueInfo->DataLength); // 980
                ASSERT(ExpProductTypeValueInfo->Type == ValueInfo->Type); // 981                
                
                memcpy(ExpProductTypeValueInfo, ValueBuffer, sizeof(ValueBuffer));

                IllegalChange = FALSE;
            }
        }

        CmpLockRegistryExclusive();
        RegistryLocked = TRUE;

        Status = NtSetValueKey(
            ExpProductTypeKey,
            &KeyValueName,
            0,
            ExpProductTypeValueInfo->Type,
            ExpProductTypeValueInfo->Data,
            ExpProductTypeValueInfo->DataLength
            );

        if (!NT_SUCCESS(Status)) {
            KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 17, Status, 1, 0);
        }

        if (ExpProductSuiteValueInfo) {
            RtlInitUnicodeString(&KeyValueName, ExpStrings[EXP_ST_PRODUCT_SUITE]);

            Status = NtSetValueKey(
                     ExpProductTypeKey,
                     &KeyValueName,
                     0,
                     ExpProductSuiteValueInfo->Type,
                     ExpProductSuiteValueInfo->Data,
                     ExpProductSuiteValueInfo->DataLength);

            if ( !NT_SUCCESS(Status) ) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 17, Status, 2, 0);
            }
        }
        else {
            RtlInitUnicodeString(&KeyValueName, ExpStrings[EXP_ST_PRODUCT_SUITE]);

            NtDeleteValueKey(ExpProductTypeKey, &KeyValueName);
            NtFlushKey(ExpProductTypeKey);
        }
        NtFlushKey(ExpProductTypeKey);
    }

    Status = NtNotifyChangeKey(
        ExpProductTypeKey,
        NULL,
        (PIO_APC_ROUTINE)(void*)&ExpWatchProductTypeWorkItem,
        (PVOID)DelayedWorkQueue,
        &ExpProductTypeIoSb,
        (REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET),
        FALSE,
        &ExpProductTypeChangeBuffer,
        sizeof(ExpProductTypeChangeBuffer),
        TRUE);

    if (RegistryLocked) {
        CmpUnlockRegistry();
    }

    if (!NT_SUCCESS(Status)) {
        KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 17, Status, 4, 0);
    }

    if (ExpSetupModeDetected || !IllegalChange) {
        goto Cleanup;
    }

    Status = PsCreateSystemThread(&Thread,
        THREAD_ALL_ACCESS,
        NULL,
        0L,
        NULL,
        ExpExpirationThread,
        (PVOID)STATUS_LICENSE_VIOLATION
        );

    if (NT_SUCCESS(Status)) {
        ZwClose(Thread);
    }

Cleanup:
    ExReleaseResourceLite(&ExpKeyManipLock);
}

VOID
static
ExpWatchSystemPrefixWork(
    PVOID Context
    )
{

    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING KeyValueName;
    UNICODE_STRING KeyName;
    BOOLEAN RegistryLocked = FALSE;

    UNREFERENCED_PARAMETER(Context);

    ExAcquireResourceSharedLite(&ExpKeyManipLock, 1);
    if (!ExpSetupKey || ExpShuttingDown) {
        goto Cleanup;
    }

    NtClose(ExpSetupKey);
    ExpSetupKey = 0;

    RtlInitUnicodeString(&KeyName, ExpStrings[EXP_ST_SETUP]);

    InitializeObjectAttributes( &ObjectAttributes,
                                &KeyName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );

    Status = NtOpenKey(&ExpSetupKey, KEY_READ | KEY_WRITE, &ObjectAttributes);
    if (!NT_SUCCESS(Status)) {
        KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0xF, Status, 0, 0);
    }

    if (!ExpSetupModeDetected) {
        RtlInitUnicodeString(&KeyValueName, ExpStrings[EXP_ST_SYSTEM_PREFIX]);

        CmpLockRegistryExclusive();
        RegistryLocked = TRUE;

        Status = NtSetValueKey(
            ExpSetupKey,
            &KeyValueName,
            0,
            REG_BINARY,
            &ExpSetupSystemPrefix,
            sizeof(ExpSetupSystemPrefix)
            );

        if (!NT_SUCCESS(Status)) {
            KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x10, Status, 0, 0);
        }
        ZwFlushKey(ExpSetupKey);
    }

    Status = NtNotifyChangeKey(
        ExpSetupKey,
        NULL,
        (PIO_APC_ROUTINE)&ExpWatchSystemPrefixWorkItem,
        (PVOID)DelayedWorkQueue,
        &ExpSystemPrefixIoSb,
        (REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET),
        FALSE,
        &ExpSystemPrefixChangeBuffer,
        sizeof(ExpSystemPrefixChangeBuffer),
        TRUE);

    if (RegistryLocked) {
        CmpUnlockRegistry();
    }

    if (!NT_SUCCESS(Status)) {
        KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x10, Status, 1, 0);
    }

Cleanup:
    ExReleaseResourceLite(&ExpKeyManipLock);
}

BOOLEAN
ExVerifySuite (
    SUITE_TYPE SuiteType
    )

/*++

Routine Description:

    This function verifies the given suite type with the system's
    assigned suite type.

Arguments:

    SuiteType - Suite type to check.

Return Value:

    A value of TRUE is returned if the suite matches the system. Otherwise
    a value of FALSE is returned.

--*/

{

    if (SuiteType > MaxSuiteType) {
        return FALSE;
    }

    if (SuiteType == TerminalServer && !ExpHydraEnabled) {
        return FALSE;
    }

    //
    // Shift the suite type to match the suite mask.
    //

    return (BOOLEAN)(((1 << SuiteType) & ExpSuiteMask) != 0);
}

//
// Setup to watch changes on the product type. Main part of this effort is to get
// the boot time value of product type and do not allow it to change
//
extern POBJECT_TYPE CmpKeyObjectType;
PVOID ExpControlKey[2];

BOOLEAN
static
ExpWatchProductTypeInitialization (
    VOID
    )
{

    // 4chan todo: stack vars don't match original exinit.obj...
    // no idea how to reorder them neither, oh well
    NTSTATUS Status;
    PVOID KeyBody;
    PKEY_VALUE_PARTIAL_INFORMATION ValueInfo;
    PULONG SetupType;
    ULONG ProductTypeValue;
    PKEY_BASIC_INFORMATION KeyBasic;

    KEY_VALUE_PARTIAL_INFORMATION KeyPartial;
    ULONG ValueInfoBuffer[sizeof(KEY_VALUE_PARTIAL_INFORMATION) + 2];
    KEY_FULL_INFORMATION KeyInfo;
    UNICODE_STRING LimitValueName;
    LARGE_INTEGER EvaluationTime;
    UNICODE_STRING KeyName;
    ULONG SizeBasic;
    ULONG Index;
    ULONG ResultLength;
    UNICODE_STRING KeyValueName;
    UNICODE_STRING RegistryProductTypeName;
    OBJECT_ATTRIBUTES ObjectAttributes;
    HANDLE LicenseInfoKey;
    UNICODE_STRING ProductTypeName;
    UNICODE_STRING SubKeyName;
    ULONG SizeValue;
#if !defined(NT_UP)
    ULONG NumberOfProcessors;
#endif
    PKEY_VALUE_PARTIAL_INFORMATION KeyValue;
    ULONG DataLength;

    //
    // Load the setup information
    //

    ExpSystemPrefixValid = FALSE;
    ExpSetupModeDetected = FALSE;
    SharedUserData->ProductTypeIsValid = TRUE;

    RtlInitUnicodeString(&KeyName, ExpStrings[EXP_ST_SETUP]);

    InitializeObjectAttributes( &ObjectAttributes,
                                &KeyName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );

    Status = NtOpenKey(
                &ExpSetupKey,
                KEY_READ | KEY_WRITE | KEY_NOTIFY,
                &ObjectAttributes
                );

    if (NT_SUCCESS(Status)) {
        Status = ObReferenceObjectByHandle(
                            ExpSetupKey,
                            0,
                            CmpKeyObjectType,
                            KernelMode,
                            (PVOID *)&KeyBody,
                            NULL
                            );

        if (NT_SUCCESS(Status)) {
            ExpControlKey[0] = KeyBody;

            //
            // Query SetupType in the registry and update ExpSetupModeDetected accordingly
            //

            RtlInitUnicodeString(&KeyValueName, ExpStrings[EXP_ST_SETUP_TYPE]);

            ValueInfo = (PKEY_VALUE_PARTIAL_INFORMATION)ValueInfoBuffer;

            Status = NtQueryValueKey(
                            ExpSetupKey,
                            &KeyValueName,
                            KeyValuePartialInformation,
                            ValueInfo,
                            sizeof(ValueInfoBuffer),
                            &DataLength
                            );

            if (NT_SUCCESS(Status)) {
                SetupType = (PULONG)ValueInfo->Data;

                // check for SETUPTYPE_FULL || SETUPTYPE_UPGRADE
                if (*SetupType == 1 || *SetupType == 4) {
                    SharedUserData->ProductTypeIsValid = FALSE;
                    ExpSetupModeDetected = TRUE;
                    ObDereferenceObject(ExpControlKey[0]);
                    ExpControlKey[0] = NULL;
                }
            }
            else {
                if (ExpInTextModeSetup == FALSE) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 3, Status, 0, 0);
                }
            }

            //
            // Query the system prefix data in the registry and update ExpSystemPrefixValid accordingly
            //

            RtlInitUnicodeString(&KeyValueName, ExpStrings[EXP_ST_SYSTEM_PREFIX]);

            ValueInfo = (PKEY_VALUE_PARTIAL_INFORMATION)ValueInfoBuffer;

            Status = NtQueryValueKey(
                            ExpSetupKey,
                            &KeyValueName,
                            KeyValuePartialInformation,
                            ValueInfo,
                            sizeof(ValueInfoBuffer),
                            &DataLength
                            );

            if (NT_SUCCESS(Status)) {
                RtlCopyMemory(&ExpSetupSystemPrefix, &ValueInfo->Data, sizeof(LARGE_INTEGER));

                if (!ExpSetupModeDetected) {
                    ExpSystemPrefixValid = TRUE;

                    ExInitializeWorkItem(&ExpWatchSystemPrefixWorkItem, ExpWatchSystemPrefixWork, NULL);

                    Status = NtNotifyChangeKey(
                        ExpSetupKey,
                        NULL,
                        (PIO_APC_ROUTINE)&ExpWatchSystemPrefixWorkItem,
                        (PVOID)DelayedWorkQueue,
                        &ExpSystemPrefixIoSb,
                        (REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET),
                        FALSE,
                        &ExpSystemPrefixChangeBuffer,
                        sizeof(ExpSystemPrefixChangeBuffer),
                        TRUE);

                    if(!NT_SUCCESS(Status)) {
                        KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 9, Status, 0, 0);
                    }
                }
            } else {
                if (!ExpInTextModeSetup) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 4, Status, 0, 0);
                }
            }
        } else {
            KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 11, Status, 0, 0);
        }
    } else {
        if (!ExpInTextModeSetup) {
            KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 2, Status, 0, 0);
        }
    }

    //
    // Load the product options information
    //

    if (!InitIsWinPEMode || !ExpInTextModeSetup) {
        ExInitializeWorkItem(&ExpWatchProductTypeWorkItem, ExpWatchProductTypeWork, NULL);

        RtlInitUnicodeString(&KeyName, ExpStrings[EXP_ST_PRODUCT_OPTIONS]);

        InitializeObjectAttributes( &ObjectAttributes,
                                    &KeyName,
                                    OBJ_CASE_INSENSITIVE,
                                    NULL,
                                    NULL
                                  );

        Status = NtOpenKey(
                    &ExpProductTypeKey,
                    KEY_READ | KEY_NOTIFY | KEY_WRITE,
                    &ObjectAttributes
                    );

        if (!NT_SUCCESS(Status)) {
            if (!ExpSetupModeDetected && !ExpInTextModeSetup) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 6, Status, 0, 0);
            }
            return FALSE;
        }

        if (!ExpSetupModeDetected && !ExpInTextModeSetup) {
            ASSERT(NT_SUCCESS(Status));

            Status = ObReferenceObjectByHandle(
                                ExpProductTypeKey,
                                0,
                                CmpKeyObjectType,
                                KernelMode,
                                (PVOID *)&KeyBody,
                                NULL
                                );

            if (NT_SUCCESS(Status)) {
                ExpControlKey[1] = KeyBody;
            } else {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 12, Status, 0, 0);
            }
        }

        //
        // Query the product type in the registry
        //

        RtlInitUnicodeString(&KeyValueName, ExpStrings[EXP_ST_PRODUCT_TYPE]);

        ExpProductTypeValueInfo = ExAllocatePoolWithTag(
                                        PagedPool,
                                        sizeof(*ExpProductTypeValueInfo) + MAX_PRODUCT_TYPE_BYTES,
                                        ' yeK'
                                        );

        ASSERT(ExpProductTypeValueInfo != NULL);

        if (!ExpProductTypeValueInfo) {
            return FALSE;
        }

        Status = NtQueryValueKey(
                        ExpProductTypeKey,
                        &KeyValueName,
                        KeyValuePartialInformation,
                        ExpProductTypeValueInfo,
                        sizeof(*ExpProductTypeValueInfo) + MAX_PRODUCT_TYPE_BYTES,
                        &DataLength
                        );

        ASSERT(NT_SUCCESS(Status));

        if (!NT_SUCCESS(Status)) {
            if (!ExpSetupModeDetected && !ExpInTextModeSetup) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 7, Status, 0, 0);
            }
            return FALSE;
        }

        //
        // Modify the suite mask for terminal services
        //

        if (ExpHydraEnabled) {
            ExpSuiteMask |= 0x10;
            SharedUserData->SuiteMask = ExpSuiteMask;

            if (!ExpMultiUserTS) {
                SharedUserData->SuiteMask |= 0x100;
            }
        }
        else {
            SharedUserData->SuiteMask = ExpSuiteMask;
        }

        RtlInitUnicodeString(&KeyValueName, ExpStrings[EXP_ST_PRODUCT_SUITE]);

        if (NtQueryValueKey(
                        ExpProductTypeKey,
                        &KeyValueName,
                        KeyValuePartialInformation,
                        &KeyPartial,
                        sizeof(KeyPartial),
                        &DataLength
                        ) == STATUS_BUFFER_OVERFLOW
            ) {
            DataLength += 16;

            ExpProductSuiteValueInfo = ExAllocatePoolWithTag(
                                            PagedPool,
                                            DataLength,
                                            ' yeK'
                                            );

            ASSERT(ExpProductSuiteValueInfo != NULL);

            if (!ExpProductSuiteValueInfo) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x14, DataLength, 2, 0);
            }

            Status = NtQueryValueKey(
                        ExpProductTypeKey,
                        &KeyValueName,
                        KeyValuePartialInformation,
                        ExpProductSuiteValueInfo,
                        DataLength,
                        &DataLength
                        );

            ASSERT(NT_SUCCESS(Status));

            if (!NT_SUCCESS(Status)) {
                ExFreePoolWithTag(ExpProductSuiteValueInfo, 0);
                ExpProductSuiteValueInfo = NULL;
                if (ExpSetupModeDetected || ExpInTextModeSetup) {
                    return FALSE;
                }
            }
        }

        if (!wcsncmp(ExpStrings[EXP_ST_LANMANNT], (wchar_t*)ExpProductTypeValueInfo->Data, wcslen(ExpStrings[EXP_ST_LANMANNT])) &&
            InitSafeBootMode == SAFEBOOT_DSREPAIR &&
            !ExpSetupModeDetected &&
            !ExpInTextModeSetup) {

            SharedUserData->ProductTypeIsValid = TRUE;
            SharedUserData->NtProductType = NtProductServer;
        }

        if (ExpSystemPrefixValid) {
            RegistryProductTypeName.Buffer = (USHORT*)ExpProductTypeValueInfo->Data;
            ProductTypeValue = *(ULONG*)ExpProductTypeValueInfo->Data;

#if !defined(NT_UP)
            NumberOfProcessors = 1 << ((ExpSetupSystemPrefix.LowPart >> 5) & 0x1F);
#endif

            if ((ExpSetupSystemPrefix.HighPart & 0x4000000) != 0) {
                RtlInitUnicodeString(&ProductTypeName, ExpStrings[EXP_ST_LANMANNT]);
                RegistryProductTypeName.MaximumLength = RegistryProductTypeName.Length = ProductTypeName.Length;

                if(!RtlEqualUnicodeString(&ProductTypeName, &RegistryProductTypeName, 0)) {
                    RtlInitUnicodeString(&ProductTypeName, ExpStrings[EXP_ST_SERVERNT]);

                    if(!RtlEqualUnicodeString(&ProductTypeName, &RegistryProductTypeName, 0)) {
                        KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0, 1, 8 * (ExpSetupSystemPrefix.HighPart & 0x4000000), ProductTypeValue);
                    }
                }

                if (ExpSetupSystemPrefix.HighPart & 0x800) {
                    RtlInitUnicodeString(&ProductTypeName, ExpStrings[EXP_ST_LANMANNT]);

                    if(!RtlEqualUnicodeString(&ProductTypeName, &RegistryProductTypeName, 0)) {
                        KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x19, 0, 0, 0);
                    }
                }
            } else {
                RtlInitUnicodeString(&ProductTypeName, ExpStrings[EXP_ST_WINNT]);
                RegistryProductTypeName.MaximumLength = RegistryProductTypeName.Length = ProductTypeName.Length;

                if(!RtlEqualUnicodeString(&ProductTypeName, &RegistryProductTypeName, 0)) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0, 0, 8 * (ExpSetupSystemPrefix.HighPart & 0x4000000), ProductTypeValue);
                }

                if (ExpSetupSystemPrefix.HighPart & 0x800) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x19, 0, 1, 0);
                }
            }

            EvaluationTime.QuadPart = (ExpSetupSystemPrefix.QuadPart >> 13);
            if ((EvaluationTime.LowPart & 0xFFFFFFF) != ExpNtExpirationData[1]) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 1, EvaluationTime.LowPart, 8 * (ExpSetupSystemPrefix.HighPart & 0x4000000), ExpNtExpirationData[1]);
            }

#if !defined(NT_UP)
            if(KeLicensedProcessors != NumberOfProcessors) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 5, ExpSetupSystemPrefix.LowPart, KeLicensedProcessors, NumberOfProcessors);
            }
#endif

        }

        Status = NtNotifyChangeKey(
            ExpProductTypeKey,
            NULL,
            (PIO_APC_ROUTINE)&ExpWatchProductTypeWorkItem,
            (PVOID)DelayedWorkQueue,
            &ExpProductTypeIoSb,
            (REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET),
            FALSE,
            &ExpProductTypeChangeBuffer,
            sizeof(ExpProductTypeChangeBuffer),
            TRUE);

        if (!NT_SUCCESS(Status)) {
            if (ExpSetupModeDetected == FALSE && ExpInTextModeSetup == FALSE) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 8, Status, 0, 0);
            }
            return FALSE;
        }

        RtlInitUnicodeString(&KeyName, ExpStrings[EXP_ST_LICENSE_INFO]);
        InitializeObjectAttributes( &ObjectAttributes,
                                    &KeyName,
                                    OBJ_CASE_INSENSITIVE,
                                    NULL,
                                    NULL
                                  );

        if (NT_SUCCESS(NtOpenKey(&LicenseInfoKey, KEY_READ, &ObjectAttributes))) {
            SubKeyName.MaximumLength = SubKeyName.Length = (USHORT)(sizeof(WCHAR) * wcslen(ExpStrings[EXP_ST_LICENSE_INFO]) + 128);
            SubKeyName.Buffer = (PWSTR)ExAllocatePoolWithTag(0, SubKeyName.Length, ' yeK');

            if (!SubKeyName.Buffer) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x14, SubKeyName.Length, 3, 0);
            }

            Status = NtQueryKey(LicenseInfoKey, KeyFullInformation, &KeyInfo, sizeof(KeyInfo), &ResultLength);
            if (!NT_SUCCESS(Status)) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x13, Status, 1, 0);
            }

            SizeBasic = sizeof(WCHAR) * KeyInfo.MaxNameLen + 56; // TODO: why 56

            KeyBasic = (PKEY_BASIC_INFORMATION)ExAllocatePoolWithTag(0, SizeBasic, ' yeK');
            if (!KeyBasic) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x14, SizeBasic, 4, 0);
            }

            SizeValue = KeyInfo.MaxValueDataLen + 32;

            KeyValue = ExAllocatePoolWithTag(0, SizeValue, ' yeK');
            if (!KeyValue) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x14, SizeValue, 5, 0);
            }

            ExpLicenseInfoCount = KeyInfo.SubKeys;
            ExpLicenseInfo = (EXP_LICENSE_INFO*)ExAllocatePoolWithTag(0, sizeof(EXP_LICENSE_INFO) * KeyInfo.SubKeys, ' yeK');

            if (!ExpLicenseInfo) {
                KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x14, sizeof(EXP_LICENSE_INFO) * ExpLicenseInfoCount, 6, 0);
            }

            RtlInitUnicodeString(&LimitValueName, ExpStrings[EXP_ST_CONCURRENT_LIMIT]);

            Index = 0;

            while ((Status = NtEnumerateKey(LicenseInfoKey, Index, 0, KeyBasic, SizeBasic, &ResultLength))
                != STATUS_NO_MORE_ENTRIES) {

                if (!NT_SUCCESS(Status)) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x1A, Status, 0, 0);
                }

                KeyBasic->Name[KeyBasic->NameLength / sizeof(WCHAR)] = 0;

                wcscpy(SubKeyName.Buffer, ExpStrings[EXP_ST_LICENSE_INFO]);
                wcscat(SubKeyName.Buffer, L"\\");
                wcscat(SubKeyName.Buffer, KeyBasic->Name);

                SubKeyName.Length = (USHORT)(sizeof(USHORT) * wcslen(SubKeyName.Buffer));

                InitializeObjectAttributes( &ObjectAttributes,
                                            &SubKeyName,
                                            OBJ_CASE_INSENSITIVE,
                                            NULL,
                                            NULL
                                          );

                Status = NtOpenKey(&ExpLicenseInfo[Index].RegKey, KEY_READ | KEY_WRITE, &ObjectAttributes);
                if (!NT_SUCCESS(Status)) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x16, Status, 1, 0);
                }

                Status = NtQueryValueKey(ExpLicenseInfo[Index].RegKey, &LimitValueName, KeyValuePartialInformation, KeyValue, SizeValue, &ResultLength);
                if (!NT_SUCCESS(Status)) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x13, Status, 2, 0);
                }

                ExpLicenseInfo[Index].SubKeyName = (USHORT*)ExAllocatePoolWithTag(0, SubKeyName.Length, ' yeK');

                if (!ExpLicenseInfo[Index].SubKeyName) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x14, SubKeyName.Length, 7, 0);
                }

                wcscpy(ExpLicenseInfo[Index].SubKeyName, SubKeyName.Buffer);

                ExpLicenseInfo[Index].Count = *(ULONG*)KeyValue->Data;

                ExInitializeWorkItem(&ExpLicenseInfo[Index].ExpWatchLicenseInfoWorkItem, ExpWatchLicenseInfoWork, &ExpLicenseInfo[Index]);

                Status = NtNotifyChangeKey(
                    ExpLicenseInfo[Index].RegKey,
                    NULL,
                    (PIO_APC_ROUTINE)&ExpLicenseInfo[Index].ExpWatchLicenseInfoWorkItem,
                    (PVOID)DelayedWorkQueue,
                    &ExpLicenseInfo[Index].ExpLicenseInfoIoSb,
                    (REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET),
                    TRUE,
                    &ExpLicenseInfo[Index].ExpLicenseInfoChangeBuffer,
                    sizeof(ExpLicenseInfo[Index].ExpLicenseInfoChangeBuffer),
                    TRUE);

                if (!NT_SUCCESS(Status)) {
                    KeBugCheckEx(SYSTEM_LICENSE_VIOLATION, 0x18, Status, 1, 0);
                }

                ++Index;
            }

            ExFreePoolWithTag(KeyBasic, 0);
            ExFreePoolWithTag(KeyValue, 0);
            ExFreePoolWithTag(SubKeyName.Buffer, 0);
            NtClose(LicenseInfoKey);
        }
    }

    return TRUE;
}

BOOLEAN
ExpInitSystemPhase1 (
    VOID
    )

/*++

Routine Description:

    This function performs Phase 1 initialization of the executive component
    of the NT system.

Arguments:

    None.

Return Value:

    A value of TRUE is returned if the initialization succeeded.  Otherwise
    a value of FALSE is returned.

--*/

{

    ULONG Index;
    BOOLEAN Initialized = TRUE;
    ULONG List;
    PGENERAL_LOOKASIDE Lookaside;
    PKPRCB Prcb;

    //
    // Initialize the ATOM package
    //

    RtlInitializeAtomPackage( 'motA' );

    // this is inside WRK exinit.c, maybe 2003SP1 ?
#if 0
    //
    // Initialize pushlocks.
    //

    ExpInitializePushLocks ();
#endif

    //
    // Initialize the worker threads.
    //

    if (!NT_SUCCESS (ExpWorkerInitialization())) {
        Initialized = FALSE;
        KdPrint(("Executive: Worker thread initialization failed\n"));
    }

    //
    // Initialize the executive objects.
    //

    if (ExpEventInitialization() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Event initialization failed\n"));
    }

    if (ExpEventPairInitialization() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Event Pair initialization failed\n"));
    }

    if (ExpMutantInitialization() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Mutant initialization failed\n"));
    }
    if (ExpInitializeCallbacks() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Callback initialization failed\n"));
    }

    if (ExpSemaphoreInitialization() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Semaphore initialization failed\n"));
    }

    if (ExpTimerInitialization() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Timer initialization failed\n"));
    }

    if (ExpProfileInitialization() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Profile initialization failed\n"));
    }

    if (ExpUuidInitialization() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Uuid initialization failed\n"));
    }

    if (!NT_SUCCESS (ExpKeyedEventInitialization ())) {
        Initialized = FALSE;
        KdPrint(("Executive: Keyed event initialization failed\n"));
    }

    if (ExpWin32Initialization() == FALSE) {
        Initialized = FALSE;
        KdPrint(("Executive: Win32 initialization failed\n"));
    }

    //
    // Initialize per processor paged and nonpaged pool lookaside lists.
    //

    for (Index = 0; Index < (ULONG)KeNumberProcessors; Index += 1) {
        Prcb = KiProcessorBlock[Index];

        //
        // Allocate all of the lookaside list structures at once so they will
        // be dense and aligned properly.
        //

        Lookaside =  ExAllocatePoolWithTag(NonPagedPool,
                                           sizeof(GENERAL_LOOKASIDE) * POOL_SMALL_LISTS * 2,
                                           'LooP');

        //
        // If the allocation succeeded, then initialize and fill in the new
        // per processor lookaside structures. Otherwise, use the default
        // structures initialized during phase zero.
        //

        if (Lookaside != NULL) {
            for (List = 0; List < POOL_SMALL_LISTS; List += 1) {
                ExInitializeSystemLookasideList(Lookaside,
                                                NonPagedPool,
                                                (List + 1) * sizeof (POOL_BLOCK),
                                                'LooP',
                                                256,
                                                &ExPoolLookasideListHead);

                Prcb->PPNPagedLookasideList[List].P = Lookaside;
                Lookaside += 1;

                ExInitializeSystemLookasideList(Lookaside,
                                                PagedPool,
                                                (List + 1) * sizeof (POOL_BLOCK),
                                                'LooP',
                                                256,
                                                &ExPoolLookasideListHead);

                Prcb->PPPagedLookasideList[List].P = Lookaside;
                Lookaside += 1;
            }
        }
    }

    return Initialized;
}

VOID
ExInitSystemPhase2 (
    VOID
    )

/*++

Routine Description:

    This function performs Phase 2 initialisation of the executive component
    of the NT system.

Arguments:

    None.

Return Value:

    None.

--*/

{

    ExpWatchProductTypeInitialization();

    SharedUserData->ComPlusPackage = COMPLUS_PACKAGE_INVALID;
}

ULONG
ExComputeTickCountMultiplier (
    IN ULONG TimeIncrement
    )

/*++

Routine Description:

    This routine computes the tick count multiplier that is used to
    compute a tick count value.

Arguments:

    TimeIncrement - Supplies the clock increment value in 100ns units.

Return Value:

    A scaled integer/fraction value is returned as the function result.

--*/

{

    ULONG FractionPart;
    ULONG IntegerPart;
    ULONG Index;
    ULONG Remainder;

    //
    // Compute the integer part of the tick count multiplier.
    //
    // The integer part is the whole number of milliseconds between
    // clock interrupts. It is assumed that this value is always less
    // than 128.
    //

    IntegerPart = TimeIncrement / (10 * 1000);

    //
    // Compute the fraction part of the tick count multiplier.
    //
    // The fraction part is the fraction milliseconds between clock
    // interrupts and is computed to an accuracy of 24 bits.
    //

    Remainder = TimeIncrement - (IntegerPart * (10 * 1000));
    FractionPart = 0;
    for (Index = 0; Index < 24; Index += 1) {
        FractionPart <<= 1;
        Remainder <<= 1;
        if (Remainder >= (10 * 1000)) {
            Remainder -= (10 * 1000);
            FractionPart |= 1;
        }
    }

    //
    // The tick count multiplier is equal to the integer part shifted
    // left by 24 bits and added to the 24 bit fraction.
    //

    return (IntegerPart << 24) | FractionPart;
}

NTSTATUS
NtShutdownSystem (
    IN SHUTDOWN_ACTION Action
    )

/*++

Routine Description:

    This service is used to safely shutdown the system.

    N.B. The caller must have SeShutdownPrivilege to shut down the
        system.

Arguments:

    Action - Supplies an action that is to be taken after having shutdown.

Return Value:

    !NT_SUCCESS - The operation failed or the caller did not have appropriate
        privileges.

--*/

{

    POWER_ACTION        SystemAction;
    NTSTATUS            Status;

    //
    // Convert shutdown action to system action
    //

    switch (Action) {
        case ShutdownNoReboot:  SystemAction = PowerActionShutdown;         break;
        case ShutdownReboot:    SystemAction = PowerActionShutdownReset;    break;
        case ShutdownPowerOff:  SystemAction = PowerActionShutdownOff;      break;
        default:
            return STATUS_INVALID_PARAMETER;
    }

    //
    // Bypass policy manager and pass directly to SetSystemPowerState
    //

    Status = NtSetSystemPowerState (
                SystemAction,
                PowerSystemSleeping3,
                POWER_ACTION_OVERRIDE_APPS | POWER_ACTION_DISABLE_WAKES | POWER_ACTION_CRITICAL
                );

    return Status;
}

NTSTATUS
NtDisplayString (
    IN PUNICODE_STRING String
    )

/*++

Routine Description:

    This service calls the HAL to display a string on the console.

    The caller must have SeTcbPrivilege to display a message.

Arguments:

    RebootAfterShutdown - A pointer to the string that is to be displayed.

Return Value:

    !NT_SUCCESS - The operation failed or the caller did not have appropriate
        privileges.

--*/

{

    KPROCESSOR_MODE PreviousMode;
    UNICODE_STRING CapturedString;
    PCHAR StringBuffer = NULL;
    PCHAR AnsiStringBuffer = NULL;
    STRING AnsiString;

    NTSTATUS Status;
    PUNICODE_STRING CurString;

    //
    // Check to determine if the caller has the privilege to make this
    // call.
    //

    PreviousMode = KeGetPreviousMode();
    if (!SeSinglePrivilegeCheck(SeTcbPrivilege, PreviousMode)) {
        return STATUS_PRIVILEGE_NOT_HELD;
    }

    CurString = String;

    //
    // If the previous mode was user, then check the input parameters.
    //

    if (PreviousMode != KernelMode) {
        try {

            //
            // Probe and capture the input unicode string descriptor.
            //

            CapturedString = ProbeAndReadUnicodeString(String);

            //
            // If the captured string descriptor has a length of zero, then
            // return success.
            //

            if ((CapturedString.Buffer == 0) ||
                (CapturedString.MaximumLength == 0)) {
                return STATUS_SUCCESS;
            }

            //
            // Probe and capture the input string.
            //
            // N.B. Note the length is in bytes.
            //

            ProbeForRead(
                CapturedString.Buffer,
                CapturedString.MaximumLength,
                sizeof(UCHAR)
                );

        } except (EXCEPTION_EXECUTE_HANDLER) {
            return GetExceptionCode();
        }

        //
        // Allocate a non-paged string buffer because the buffer passed to
        // HalDisplay string must be non-paged.
        //

        StringBuffer = ExAllocatePoolWithTag(NonPagedPool,
                                              CapturedString.MaximumLength,
                                              'grtS');

        if (!StringBuffer) {
            return STATUS_NO_MEMORY;
        }

        try {
            RtlCopyMemory(StringBuffer,
                          CapturedString.Buffer,
                          CapturedString.MaximumLength);

        } except (EXCEPTION_EXECUTE_HANDLER) {

            if (StringBuffer != NULL) {
                ExFreePoolWithTag(StringBuffer, 0);
            }

            return GetExceptionCode();
        }

        CapturedString.Buffer = (PWSTR)StringBuffer;

        CurString = &CapturedString;
    }

    //
    // Allocate a string buffer for the ansi string.
    //

    AnsiStringBuffer = ExAllocatePoolWithTag(NonPagedPool,
                                             CurString->MaximumLength,
                                             'grtS');


    if (AnsiStringBuffer != NULL) {
        AnsiString.MaximumLength = CurString->MaximumLength;
        AnsiString.Length = 0;
        AnsiString.Buffer = AnsiStringBuffer;

        //
        // We were in kernel mode; just transform the original string.
        //

        RtlUnicodeStringToOemString(
            &AnsiString,
            CurString,
            FALSE
            );

        InbvDisplayString((PUCHAR)AnsiString.Buffer);

        Status = STATUS_SUCCESS;

        ExFreePoolWithTag(AnsiStringBuffer, 0);
    } else {
        Status = STATUS_NO_MEMORY;
    }

    //
    // Free up the memory we used to store the strings.
    //

    if (PreviousMode != KernelMode) {
        ExFreePoolWithTag(StringBuffer, 0);
    }

    return Status;
}

int
ExSystemExceptionFilter( VOID )
{
    return( KeGetPreviousMode() != KernelMode ? EXCEPTION_EXECUTE_HANDLER
                                            : EXCEPTION_CONTINUE_SEARCH
          );
}

NTKERNELAPI
KPROCESSOR_MODE
ExGetPreviousMode (
    VOID
    )

/*++

Routine Description:

    Returns previous mode.  This routine is exported from the kernel so
    that drivers can call it, as they may have to do probing of
    embedded pointers to user structures on IOCTL calls that the I/O
    system can't probe for them on the FastIo path, which does not pass
    previous mode via the FastIo parameters.

Arguments:

    None.

Return Value:

    return-value - Either KernelMode or UserMode

--*/

{
    return KeGetPreviousMode();
}

VOID
ExInitializeSystemLookasideList (
    IN PGENERAL_LOOKASIDE Lookaside,
    IN POOL_TYPE Type,
    IN ULONG Size,
    IN ULONG Tag,
    IN USHORT Depth,
    IN PLIST_ENTRY ListHead
    )

/*++

Routine Description:

    This function initializes a system lookaside list structure and inserts
    the structure in the specified lookaside list.

Arguments:

    Lookaside - Supplies a pointer to a nonpaged lookaside list structure.

    Type - Supplies the pool type of the lookaside list.

    Size - Supplies the size of the lookaside list entries.

    Tag - Supplies the pool tag for the lookaside list entries.

    Depth - Supplies the maximum depth of the lookaside list.

    ListHead - Supplies a pointer to the lookaside list into which the
        lookaside list structure is to be inserted.

Return Value:

    None.

--*/

{

    //
    // Initialize pool lookaside list structure and insert the structure
    // in the pool lookaside list.
    //

    ExInitializeSListHead(&Lookaside->ListHead);
    Lookaside->Allocate = &ExAllocatePoolWithTag;
    Lookaside->Free = &ExFreePool;
    Lookaside->Depth = 2;
    Lookaside->MaximumDepth = Depth;
    Lookaside->TotalAllocates = 0;
    Lookaside->AllocateHits = 0;
    Lookaside->TotalFrees = 0;
    Lookaside->FreeHits = 0;
    Lookaside->Type = Type;
    Lookaside->Tag = Tag;
    Lookaside->Size = Size;
    Lookaside->LastTotalAllocates = 0;
    Lookaside->LastAllocateHits = 0;
    InsertTailList(ListHead, &Lookaside->ListEntry);
    return;
}

#ifdef ALLOC_DATA_PRAGMA
#pragma const_seg()
#endif
