@echo off

SETLOCAL
set DESTDIR=%_NTTREE%

echo Make destination directories

rem 4chan: skip creating unused DUser dir
rem mkdir %DESTDIR%\DUser

mkdir Debug
mkdir Release
mkdir IceCAP

echo Copying Resources
mkdir %DESTDIR%\Resources
copy Resources\*.* %DESTDIR%\Resources

ENDLOCAL
