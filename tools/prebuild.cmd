@echo off
setlocal enabledelayedexpansion

rem Set this to "1" if you've already installed tools\driver.pfx yourself
SET SKIPCERTINSTALL="0"

if NOT defined SDXROOT echo Error: Prebuild must be ran from an admin razzle prompt!&goto :eof

pushd %SDXROOT%

echo Administrative permissions required. Detecting permissions...

net session >nul 2>&1
if %errorLevel% == 0 (
    echo Success: Administrative permissions confirmed.
) else (
    echo Error: Prebuild must be ran from an admin razzle prompt!
    pause .
    goto end
)

echo.
echo Removing pre-built exinit/systime...
del base\ntos\ex\mp\obj\i386\exinit.obj
del base\ntos\ex\mp\obj\i386\systime.obj
del base\ntos\ex\mp\obj\ia64\exinit.obj
del base\ntos\ex\mp\obj\ia64\systime.obj
del base\ntos\ex\mp\obj\amd64\exinit.obj
del base\ntos\ex\mp\obj\amd64\systime.obj
del base\ntos\ex\up\obj\i386\exinit.obj
del base\ntos\ex\up\obj\i386\systime.obj
del base\ntos\ex\up\obj\ia64\exinit.obj
del base\ntos\ex\up\obj\ia64\systime.obj
del base\ntos\ex\up\obj\amd64\exinit.obj
del base\ntos\ex\up\obj\amd64\systime.obj

echo.
echo Setting Read-only attribute on required objects/libs...
attrib /S /D +r ds\security\services\ca\tools\certut\obj\*.lib
attrib /S /D +r inetcore\outlookexpress\external\obj\*.*
attrib /S /D +r inetcore\outlookexpress\external\objd\*.*
attrib /S /D +r inetcore\outlookexpress\external\objp\*.*
attrib /S /D +r windows\advcore\duser\directui\engine\parser\obj\i386\parse.obj
attrib /S /D +r windows\advcore\duser\directui\engine\parser\objd\i386\parse.obj
attrib /S /D +r windows\advcore\duser\directui\engine\parser\obj\amd64\parse.obj
attrib /S /D +r windows\advcore\duser\directui\engine\parser\objd\amd64\parse.obj

if not exist %SDXROOT%\windows\advcore\gdiplus_asms\ (
    echo.
    echo Copying over SxS policies for GdiPlus...
    xcopy %SDXROOT%\windows\advcore\gdiplus\engine\policy_1.0 %SDXROOT%\windows\advcore\gdiplus_asms\ /E /H /C /R /Q /Y
)

rem check OS version, delete updated 16-bit tools/code if OS doesn't really need it
rem (only Vista+ requires it, due to NTVDM crap)
rem only 2000/XP/2003 handled here since older OS really shouldn't be building this code...

echo.
for /f "tokens=2 delims=[]" %%i in ('ver') do set VERSION=%%i
for /f "tokens=2-3 delims=. " %%i in ("%VERSION%") do set VERSION=%%i.%%j
echo Detected OS Version: %VERSION%

rem try using system certutil, not available on XP/2003 though
SET CERTUTIL=certutil

if "%VERSION%" == "5.2" goto delprebuilt
if "%VERSION%" == "5.1" goto delprebuilt
if "%VERSION%" == "5.0" goto delprebuilt

echo.
echo Using updated 16-bit compilers and code
echo (as your OS won't work properly with the originals)
echo.

if exist com\ole32\olethunk\ole16\coll\map_kv.cxx_new (
    echo Updating map_kv.cxx...
    del /F /Q com\ole32\olethunk\ole16\coll\map_kv.cxx
    move com\ole32\olethunk\ole16\coll\map_kv.cxx_new com\ole32\olethunk\ole16\coll\map_kv.cxx
)
if exist com\ole32\olethunk\ole16\compobj\comlocal.cxx_new (
    echo Updating comlocal.cxx...
    del /F /Q com\ole32\olethunk\ole16\compobj\comlocal.cxx
    move com\ole32\olethunk\ole16\compobj\comlocal.cxx_new com\ole32\olethunk\ole16\compobj\comlocal.cxx
)
if exist com\ole32\olethunk\ole16\compobj\stdalloc.cxx_new (
    echo Updating stdalloc.cxx...
    del /F /Q com\ole32\olethunk\ole16\compobj\stdalloc.cxx
    move com\ole32\olethunk\ole16\compobj\stdalloc.cxx_new com\ole32\olethunk\ole16\compobj\stdalloc.cxx
)
if exist com\ole32\olethunk\ole16\inc\map_kv.h_new (
    echo Updating map_kv.h...
    del /F /Q com\ole32\olethunk\ole16\inc\map_kv.h
    move com\ole32\olethunk\ole16\inc\map_kv.h_new com\ole32\olethunk\ole16\inc\map_kv.h
)
if exist com\ole32\olethunk\ole16\ole2\memstm.cxx_new (
    echo Updating memstm.cxx...
    del /F /Q com\ole32\olethunk\ole16\ole2\memstm.cxx
    move com\ole32\olethunk\ole16\ole2\memstm.cxx_new com\ole32\olethunk\ole16\ole2\memstm.cxx
)
if exist com\ole32\olethunk\ole16\tools_new\ (
    if exist com\ole32\olethunk\ole16\tools_old rmdir /q /s com\ole32\olethunk\ole16\tools_old
    
    echo Updating ole16 tools...
    move com\ole32\olethunk\ole16\tools com\ole32\olethunk\ole16\tools_old
    move com\ole32\olethunk\ole16\tools_new com\ole32\olethunk\ole16\tools
)

if exist tools\postbuildscripts\setupw95.cmd_new (
    echo Updating setupw95.cmd post-build script...
    echo (as your OS may have problems running hwdatgen simultaneously^)
    
    del /F /Q tools\postbuildscripts\setupw95.cmd
    move tools\postbuildscripts\setupw95.cmd_new tools\postbuildscripts\setupw95.cmd
)

if exist tools\postbuildscripts\drivercab.cmd_new (
    echo Updating drivercab.cmd post-build script...
    echo (as your OS may have problems running cabwrapper simultaneously^)
    
    del /F /Q tools\postbuildscripts\drivercab.cmd
    move tools\postbuildscripts\drivercab.cmd_new tools\postbuildscripts\drivercab.cmd
)

echo.
echo Updates complete.

goto importkey

:delprebuilt
rem use our own included certutil on XP/2003 as they don't seem to have it included with the OS...
set CERTUTIL=tools\x86\certutil

echo.
echo Deleting unneeded updated 16-bit compilers/code
echo (as your OS can build the originals fine)

rmdir /Q /S com\ole32\olethunk\ole16\tools_new
del /F /Q com\ole32\olethunk\ole16\coll\map_kv.cxx_new
del /F /Q com\ole32\olethunk\ole16\compobj\comlocal.cxx_new
del /F /Q com\ole32\olethunk\ole16\compobj\stdalloc.cxx_new
del /F /Q com\ole32\olethunk\ole16\inc\map_kv.h_new
del /F /Q com\ole32\olethunk\ole16\ole2\memstm.cxx_new
del /F /Q tools\postbuildscripts\setupw95.cmd_new
del /F /Q tools\postbuildscripts\drivercab.cmd_new

:importkey

if %SKIPCERTINSTALL% == "1" goto done
if %SKIPCERTINSTALL% == 1 goto done

echo.
echo Importing test-signing keys from driver.pfx...
echo (if prompted for anything, just hit enter or press OK)

tools\x86\importpfx -f "tools\driver.pfx" -p "" -t USER -s "MY"

rem if no error we're finished, otherwise try using certutil instead (XP has problems with ImportPFX...)
if %errorLevel% == 0 goto done

echo.
echo ImportPFX.exe failed, trying import via certutil...

rem try certutil as last resort, since it can hang in certain configs (eg. Win7 SP1 unpatched)
rem hopefully ImportPFX worked for those configs though
echo. 
echo If this script hangs:
echo - Press CTRL+C and Y to exit this script
echo - Navigate to tools folder and import driver.pfx yourself by opening the file (double-click it)
echo (if prompted for anything, just hit enter or press OK)
echo. 

!CERTUTIL! /p "" /f /importpfx tools\driver.pfx

:done

echo.
echo Prebuild complete!

:end
popd
endlocal