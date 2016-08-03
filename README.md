EmulationStation RPiE
================

This version of EmulationStation is targeted mostly for ease of access from the couch.  List of added features are:
-OSK (On Screen Keyboard)
-Gamelist GridView.  (puts games in a grid view)
-Wifi connecting a scanning from ES.  (needs wificonnect put in ~/.emulationstation/app/wifi)
-Storage view
-Several other smaller UI changes.


Original Project website: http://emulationstation.org

**Raspberry Pi users:**
This build is targeted almost specifically for you!  You can just copy in this compiled version over the current emulationstation.
Get the pre-compiled version below.

Download
========

Download a pre-compiled version at https://drive.google.com/file/d/0ByWG5kDXyr5NeEtWQ2J2eGVrdk0/view?usp=sharing
Wifi Connecting needs its own file put into ~/.emulationstation/app/wifi (you'll probably have to create the directory) Get it here
https://drive.google.com/file/d/0ByWG5kDXyr5NQWZKYmVScGpaQk0/view?usp=sharing
I will be making that easier to where ES will get it automatically.


Building
========

** from the original project **

EmulationStation uses some C++11 code, which means you'll need to use at least g++-4.7 on Linux, or VS2010 on Windows, to compile.

EmulationStation has a few dependencies. For building, you'll need CMake, SDL2, Boost (System, Filesystem, DateTime, Locale), FreeImage, FreeType, Eigen3, and cURL.  You also should probably install the `fonts-droid` package which contains fallback fonts for Chinese/Japanese/Korean characters, but ES will still work fine without it (this package is only used at run-time).

**On Debian/Ubuntu:**
All of this be easily installed with apt-get:
```bash
sudo apt-get install libsdl2-dev libboost-system-dev libboost-filesystem-dev libboost-date-time-dev libboost-locale-dev libfreeimage-dev libfreetype6-dev libeigen3-dev libcurl4-openssl-dev libasound2-dev libgl1-mesa-dev build-essential cmake fonts-droid
```

Then, generate and build the Makefile with CMake:
```bash
cd YourEmulationStationDirectory
cmake .
make
```

**On the Raspberry Pi:**

Complete Raspberry Pi build instructions at [emulationstation.org](http://emulationstation.org/gettingstarted.html#install_rpi_standalone).

**Windows is not supported in this project**



Project's original Creator:

-Alec "Aloshi" Lofquist
http://www.aloshi.com
http://www.emulationstation.org
