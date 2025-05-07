How to use:
__________________________
1. Download source code
2. Unpack tar file (tar xzvf FilePath)
3. Make sure you have downloaded relevant packages (sudo apt install package1 package2 package3 ...)
   - cmake
   - cmake-curses-gui (not necessary, but nice to have. allows use of ccmake command)
   - gcc
   - g++
   - libexpatl-dev
   - qt5-default
   - libxmu-dev
   - libmotif-dev
4. Create build directory (keep things organized)
5. cd build
6. run either cmake .. or ccmake .. (I use ccmake to use the gui)
   - IN CCMAKE run
       a. c (configure command)
       b. Change CMAKE_INSTALL_PREFIX to path where you want program installed (recommended to path to empty directory)
       c. turn on packages (Most important are GEANT4_INSTALL_DATA, GEANT4_USE_QT, GEANT4_USE_SYSTEM_EXPAT. GEANT4_USE_X11_RAYTRACER is nice, turn on GEANT4_BUILD_MULTITHREADED if you want to do multi-threaded coding)
       d. c (configure, if any packages are missing you can install them if needed or continue on to see if GEANT will build anyway)
       e. g (generate command)
7. make (-j# will allow you to build the project across # number of cores. Just speeds things up)
8. make install
9. Go to install directory. Path all the way in until you find geant4make.sh file (share/Geant4-version/geant4make)
10. run command . geant4make.sh

You should now be able to use GEANT4. Test your build with one of the basic examples.

1. Go to examples folder (should be in the unpacked tar file)
2. pick an example (B1 B2 B3 or B4)
3. Create and path to build folder
4. cmake ..
5. make
6. run executable (./File)

Once everything is working and tested, you can use this project.

Some things to note. The terminal that you run the .geant4make.sh command is also the one where you will have to run executables. Otherwise you will get some error about not being able to find files.
To avoid this, source the file to your bashrc script so that it is executed upon opening a new terminal.

Example: echo ". ~/Desktop/software/Geant4/geant4-v11.0.3-install/share/Geant4-11.0.3/geant4make/geant4make.sh" >> ~/.bashrc

I prefer to set up an alias for this command so I can easily switch between a regular build and a multithread build.

Whenever you make a change to any of the files in this project, make sure to run cmake and make.
