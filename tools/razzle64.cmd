@echo off

rem razzle needs PROCESSOR_ARCHITECTURE set to x86 before running it, so it'll use working build tools (x86 only), along with PATHEXT for some 16bit fixes
rem since it needs those we can use a batch file to set them before running it
rem and since we can put whatever we like in the batch, we'll use it to set stuff up in the tree if needed too

rem change to folder above batch file's dir (batch is in SDXROOT\tools\, so this changes to SDXROOT)
pushd "%~dp0\..\"

rem check some tree stuff is in order

pushd tools\tools16

if not exist buildmsg.16.exe (
  move buildmsg.exe buildmsg.16.exe
  ..\x86\msdos32.exe -v7.10 -cbuildmsg.exe buildmsg.16.exe
)
if not exist exe2bin.16.exe (
  move exe2bin.exe exe2bin.16.exe
  ..\x86\msdos32.exe -v7.10 -cexe2bin.exe exe2bin.16.exe
)
if not exist nosrvbld.16.exe (
  move nosrvbld.exe nosrvbld.16.exe
  ..\x86\msdos32.exe -v7.10 -cnosrvbld.exe nosrvbld.16.exe
)

rem rc16 doesn't work well when msdos32-wrapped, use bat redirect instead
if exist rc16.exe (
  move rc16.exe rc16.16.exe
)
if exist rclater.exe (
  move rclater.exe rclater.16.exe
)

rem these seem to sometimes get 0xc0000417 error when msdos32 wrapper is attached
if not exist fixexe.16.exe (
  move fixexe.exe fixexe.16.exe
)
if not exist reloc.16.exe (
  move reloc.exe reloc.16.exe
)

rem cleanup pre-v9e files
if exist stripdd.16.exe (
  del stripdd.16.exe
  del stripdd.bat
  move stripdd.exe stripdd.16.exe
)
if exist h2inc.16.exe (
  del h2inc.16.exe
)
if exist stripz.16.exe (
  del stripz.16.exe
)

popd

if not exist printscan\faxsrv\print\faxprint\faxdrv\win9x\sdk\binw16\rc.16.exe (
  move printscan\faxsrv\print\faxprint\faxdrv\win9x\sdk\binw16\rc.exe printscan\faxsrv\print\faxprint\faxdrv\win9x\sdk\binw16\rc.16.exe
)

rem below dirs get a 16-bit buildmsg.exe built inside them, which gets ran to build the rest of the dir
rem wrap these buildmsg.exe calls with a batch file
if not exist base\mvdm\dos\v86\cmd\command\chs\buildmsg.bat (
  copy tools\tools16\buildmsg_thunk.bat base\mvdm\dos\v86\cmd\command\chs\buildmsg.bat
)
if not exist base\mvdm\dos\v86\cmd\command\cht\buildmsg.bat (
  copy tools\tools16\buildmsg_thunk.bat base\mvdm\dos\v86\cmd\command\cht\buildmsg.bat
)
if not exist base\mvdm\dos\v86\cmd\command\jpn\buildmsg.bat (
  copy tools\tools16\buildmsg_thunk.bat base\mvdm\dos\v86\cmd\command\jpn\buildmsg.bat
)
if not exist base\mvdm\dos\v86\cmd\command\kor\buildmsg.bat (
  copy tools\tools16\buildmsg_thunk.bat base\mvdm\dos\v86\cmd\command\kor\buildmsg.bat
)
if not exist base\mvdm\dos\v86\cmd\command\usa\buildmsg.bat (
  copy tools\tools16\buildmsg_thunk.bat base\mvdm\dos\v86\cmd\command\usa\buildmsg.bat
)
popd

rem make razzle think this is x86 box, so it'll use x86 build tools instead of broken amd64 ones
set PROCESSOR_ARCHITECTURE=x86

rem prefer .bat files over .exe, so our batch wrapper files will be preferred (todo: is this still needed?)
set PATHEXT=.BAT;.COM;.EXE;.CMD;.VBS;.VBE;.JS;.JSE;.WSF;.WSH;.RB;.RBW

tools\razzle %*

popd