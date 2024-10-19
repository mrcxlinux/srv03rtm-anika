@echo off
setlocal ENABLEDELAYEDEXPANSION
if NOT defined SDXROOT echo Run from a razzle prompt.&goto :eof

cd /d %SDXROOT%

set _NTVARIANT=%1

if NOT defined _NTVARIANT echo Usage: oscdimg.cmd <variant> [destination-file].&goto :eof

set _NTISO=%2

set _BUILDNAME=%_NTVARIANT%
if exist "%_NTPOSTBLD%\build_logs\buildname.txt" (
    set _BUILDNAME=""
    for /f "delims=" %%a in (%_NTPOSTBLD%\build_logs\buildname.txt) DO ( set _BUILDNAME=%%a )
    
    rem remove trailing whitespace..
    set _BUILDNAME=!_BUILDNAME:~0,-1!_%_NTVARIANT%
)

if NOT defined _NTISO set _NTISO=%_NTDRIVE%\%_BUILDNAME%.iso

%SDXROOT%\base\ntsetup\opktools\wpebins\x86\oscdimg.exe -n -b"%SDXROOT%\base\ntsetup\opktools\wpebins\x86\etfsboot.com" %_NTPOSTBLD%\%_NTVARIANT% "%_NTISO%"
