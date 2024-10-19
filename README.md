
# SRV03RTM Anika

On 23rd September 2020 a ~2.9GB nt5src.7z file was posted to 4chan's /g/ board, containing leaked partial (~70% complete) source code for Windows XP SP1 & Server 2003.

This code has apparently been going around in private circles for several years, but was mostly unknown to the wider internet until this recent leak.

The archive contains a majority of the code needed for a full Windows XP/Server2003 install, minus any activation/cryptographic or third-party code.

The Windows Server 2003 source code is more complete and it's what I ultimately decided to build on my x64 machine. This repository contains the source code with all the patches needed to compile the source code, even on Windows 11.
Sadly, a few sources (archive.org) are down so the project will NOT be complete for a bit of time.

## Tips
It's recommended to disable any AV before extracting/building, as both of those actions create a lot of new files (your AV will likely try scanning every one, slowing down the extraction/build by quite a bit) - this also counts for any other tools that monitor files such as voidtools' Everything.

Extract source tree to a folder named ```srv03rtm``` on the root of a drive (important, as pre-built DirectUI files will only link properly under this path), any drive letter (besides C:) should be fine, use ```D:\srv03rtm\``` as the path to match RTM binaries. I used G: and it worked just fine.

## Build Environment
Run command-prompt as administrator (can usually be done by typing cmd into start menu, right click Command Prompt -> Run as administrator)

In the command-prompt, change to the drive you extracted source-code to by typing in the drive letter (eg. E:) and changing to the source folder: ```cd srv03rtm``` and then starting razzle: ```tools\razzle64.cmd free offline```

The first time you run razzle inside that copy of the source code it'll need to initialise a few things, give it a few minutes, after a while a Notepad window will appear - make sure to close this for the initialisation to continue.

## Building 
You will need to renew test certificates for this after October 2021 so download and install Git (Bash) and run ```certutils\generate.sh``` in Git Bash then install the PFX inside ```srv03rtm.certs\tools``` by right-clicking and selecting ```Install PFX```. Select ```Local Machine``` and then just hit next for every prompt. Do the same for ```testpca.cer```, ```testroot.cer``` and ```vbl03ca.cer``` too and copy the ```srv03rtm.certs``` folder contents to ```srv03rtm```.

Important: Currently the build doesn't seem to play well when building with more than 4 threads. If your build machine has more than that it's recommended to cap it to 4 threads maximum via the ```-M 4``` switch, added to the build command (eg. ```build /cZP -M 4```, or ```bcz -M 4```)

### Clean build
Performs clean rebuild of all components (recommended for first build!):

```build /cZP``` (```bcz``` is also aliased to this)
### "Dirty" build
Builds only components that have changed since last clean build:

```build /ZP``` (```bz``` is also aliased to this)

### Postbuild
Download the [win2003_x86-missing-binaries_v2.7z](https://mirrorace.org/m/4rv80) pack, which contains missing binaries for both x86fre & x86chk builds.

(unfortunately this is quite a big pack, and it's likely the link will inevitably go down some day, however this pack isn't actually required - instead you can make use of ```missing.cmd``` with an ISO of Windows Server 2003)

From that 7z, extract the contents of the binaries folder for the build type you're building into your build trees binaries folder (eg. ```D:\binaries.x86fre```, should have been created during the build), the 7z should contain files for all SKUs (uses pidgen.dll from Win2003 Enterprise, so your builds should accept Enterprise product keys)

**When asked during extraction to overwrite folders select ```Yes```, but when asked to overwrite files like DUser.pdb/dll make sure to select ```No```!**

Once missing files have been added, you should have files such as ```binaries.x86{fre/chk}\_pop3_00.htm```, ```binaries.x86{fre/chk}\ql10wnt.sys```, etc.

Inside the razzle window run ```tools\postbuild.cmd``` (use ```-sku:{sku}``` if you want to process only specific one (no brackets!), expect ```filechk``` errors if you ignore this and didn't use missing.7z / missing.cmd with every sku)

Once postbuild has finished, assuming you used the ```win2003_x86-missing-binaries.7z``` file above and followed the guide properly, it should have hopefully succeeded without errors, and there shouldn't be any ```binaries.x86fre\build_logs\postbuild.err``` file!

Otherwise take a look inside the ```postbuild.err``` - most messages in here are negligible, but if you see ```filechk``` errors associated with the edition you want to use, you may need to re-run ```missing.cmd```, or extract ```win2003_x86-missing-binaries_v2.7z``` again.

If ```postbuild.err``` contains messages like ```(crypto.cmd) ERROR``` or ```(ntsign.cmd) ERROR``` try re-importing the ```tools\driver.pfx``` key-file (double-click it, press Next through the prompts, password is empty), and make sure your system date is set to the current date (updated test certs are only valid from October 2020 to October 2021)

## Creating an ISO
Execute ```tools\oscdimg.cmd {sku} [destination-file (optional)]``` where ```{sku}``` is one of:

```srv``` - Windows Server 2003 Standard Edition

```sbs``` - Windows Server 2003 Small Business Edition

```ads``` - Windows Server 2003 Enterprise Edition

```dtc``` - Windows Server 2003 Datacenter Edition

```bla``` - Windows Server 2003 Web Edition

The ISO will be saved to ```{build-drive}\{build-tag}_{sku}.iso```, unless ```[destination-file]``` is provided as a parameter.

## Additional Stuff

### Timebomb
Time can be adjusted by editing ```DAYS``` variable inside ```\tools\postbuildscripts\timebomb.cmd``` (line 44)

Setting ```DAYS``` to ```0``` will disable the timebomb.

Only certain ```DAYS``` parameters are valid (0, 5, 15, 30, 60, 90, 120, 150, 180, 240, 360, 444)

### Different Build Options
You can modify your razzle shortcut (or execute it manually inside your source folder) to include (or remove) additional argument(s):

```free``` - build 'free' bits (production, omitting it will generated checked bits)

```chkkernel``` - build 'checked' (testing) kernel/hal/ntdll when building 'free' bits

```no_opts``` - disable binary optimization (useful for debugging, but will most likely fail a full build, some code can't be built without optimization)

```verbose``` - enable verbose output of the build process

```binaries_dir <basepath>``` - specifies custom output directory (default is ```binaries```, the suffix added after ```.``` is non-customizable)

```officialbuild``` - sets razzle to build this as an "official" build, requires updating ```BuildMachines.txt```, see the section below

Other options are not described here, see ```razzle.cmd /?``` for details.

### 'OfficialBuild' parameter / BuildMachines.txt
The ```OfficialBuild``` razzle parameter changes a few things in the build, which will make it match up closer to the retail builds, should be useful if you need to compare against retail for any reason.

For a list of things affected by the OfficialBuild parameter see https://pastebin.com/VgVph3Xv & https://pastebin.com/gYzWGLM5, thanks to the anon that compiled them! (note that these aren't complete lists, and not all things mentioned here are guaranteed to take effect).

However, using this parameter requires a file to be updated with info about your build machine first!

An easy way to update the file required is to run the following command inside a razzle window, at the root of the source tree:

```echo %COMPUTERNAME%,primary,%_BuildBranch%,%_BuildArch%,%_BuildType%,ntblus >> tools\BuildMachines.txt```

After that you can run ```tools\verifybuildmachine.cmd``` to make sure it was setup correctly, if there's any problem an error message will show, otherwise the command will return without any message.

With that in place you should now be able to use the OfficialBuild parameter next time you init razzle, eg. ```tools\razzle.cmd free offline officialbuild```

Some small notes to be aware of:

if you change build arch or build type (eg. to amd64, or to a checked build) you'll need to run the echo command again to add your machine for that build arch/type combination

if you see Clearing OFFICIAL_BUILD_MACHINE variable after initing razzle, rerun the echo command and then close down/reinit razzle again, else the build won't properly count itself as official.

### Pseudo-localization builds
An anon has made some progress with localization, allowing "Pseudo-Localization" (PLOC) builds to be created in 3 different configurations, via certain razzle options & postbuild script changes, these builds should come in useful for people looking into creating non-English builds.

The three configs available are PSU (Pseudo), FE (Far East) and MIR (Mirrored), representing some of the main changes that localization might require (such as right-to-left text, etc)

Their instructions for creating these builds have been archived here: http://archive.rebeccablacktech.com/g/post/78862319/ & http://archive.rebeccablacktech.com/g/post/78862415/

### Creating fresh postbuild
```tools\postbuild.cmd -full```

```tools\missing.cmd```

```tools\postbuild.cmd```

Use ```-sku:{sku}``` if you want to process only specific one (no brackets!)

### Building specific components
Most components can be built seperately. For example, if you wish to rebuild ```ntos``` component, perform these steps:

```cd base\ntos``` (you can also use ntos alias that razzle has set up for you)

```bcz``` (alias for ```build /cPZ```)

Generally ```postbuild.cmd``` is clever enough to include your changes properly without needing fresh build as it uses ```bindiff``` to find differences.


# Credits
archive.org (once it's up ill add the exact link)

```Microsoft leaked source code archive_2020-09-24.torrent``` for nt5src

https://rentry.co/win2k3-extra-patches for everything (didn't use branding)

https://pastebin.com/VgVph3Xv && https://pastebin.com/gYzWGLM5 for OfficialBuild help

https://rentry.co/16bit-msbuild for making compilation possible on Windows 11

https://rentry.co/build-win2k3 for more help when I was lost
