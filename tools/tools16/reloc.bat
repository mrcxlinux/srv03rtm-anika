@echo off
setlocal

rem note: if batch is called with params that contain ; or =, it seems cmd splits the param into seperate params when we call msdos32 below
rem eg. a call "reloc.bat -i..\inc;..\rinc test.rc" becomes "msdos32 reloc.16 -i..\inc ..\rinc test.rc" below, making reloc treat ..\rinc as the input filename...
rem in the (rare?) instances of things using reloc with ; or =, changing it to call msdos32 directly seems to fix it
rem (tho that way doesn't allow the timeout/temp folder fixes below...)

rem msdos32 seems to cause race-condition issues in temp files, probably not setting correct mode when opening files or something
rem try fixing this by adding a random 1-10 second timeout before calling it, hopefully might prevent instances from overlapping
SET /A timeout=%RANDOM% * 10 / 32768 + 1
rem sleep %timeout%

rem despite the timeout it seems instances can still overwrite each others temp files
rem setting %TEMP% to a random dir name inside current directory works pretty well though
rem (setlocal will prevent the change going outside this batch file)
rem todo: can we remove timeout now we have this?
for %%I in (.) do set DirName=%%~nxI

set TEMPNEW=c%TIME:~-2%%RANDOM%%DirName%
set TEMPNEW=%TEMPNEW:~0,8%

if not exist %TEMPNEW% mkdir %TEMPNEW%

set TEMP=%TEMPNEW%
msdos32 reloc.16 %*

rmdir /q /s %TEMPNEW%

endlocal
