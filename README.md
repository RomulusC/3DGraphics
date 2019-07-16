## A simple OpenGL application, producing user generated 3D graphics.

![output result](Example.gif)

The focus of this project is to obtain experience in the following:
* Fammiliarize with using CMake for project handling
* Fammiliarize with Linux development
* Complete the LearnOpenGL tutorials found on https://learnopengl.com and https://www.opengl-tutorial.org/ 
* Implement graphics manipulaiton through my user created matrix calculation library (Translation, Scaling, Rotation) in 3D Space (Try to not use GML library)
## Usage (Executable Only):
* Download the file for your operating system, located here: https://github.com/RomulusC/3DGraphics/releases
* Extract, run the executable located inside the folder.
## Usage (General):
Install CMake for your command line. Found at https://cmake.org/download/. Make sure to select "add system PATH for all users" during instillation.
## Usage (Linux + Unix Makefiles):
```bash
git clone --recursive https://github.com/RomulusC/3DGraphics.git
```
* Run the build.sh shellscript.
* Run the Application executable located in /build.
* The repository includes a .vs folder, including configuration for gdb debugging with Visual Studio Code. (Tested on Fedora 30) 
## Usage (Windows + MSVC):
* I recommend using git for windows found here: https://gitforwindows.org/ ,
this prevents the manual setting up of environmental variables to access git through cmd.
* Install most recent Microsoft Visual Studio version, with the "Desktop Development for C++" in the installation. 
* Follow commands below using git bash in desired directory. 
```bash
git clone --recursive https://github.com/RomulusC/3DGraphics.git
```
* Run the build.bat script file. (If your Visual Studio version isn't Visual Studio 16 2019, then edit the batch file to include your installed version. EG: [ cmake -G "Visual Studio 15 2017" .. ], additionally you can use the generator type of your choice.)
* Open the Sandbox.sln located in /build.
* Run the project
