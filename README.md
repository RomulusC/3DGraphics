## A simple OpenGL application, producing user generated 3D graphics.

The focus of this project is to obtain experience in the following:
* Fammiliarize with using CMake for project handling
* Fammiliarize with Linux development
* Complete the LearnOpenGL tutorial found on https://learnopengl.com
* Implement graphics manipulaiton through my user created matrix calculation library (Translation, Scaling, Rotation) in 3D Space (Try to not use GML library)

## Usage (General):
Install CMake for your command line. Found at https://cmake.org/download/. Make sure to select "add system PATH for all users" during instillation.
## Usage (Linux + Unix Makefiles):

```bash
git clone --recursive https://github.com/RomulusC/3DGraphics.git
cd 3DGraphics
mkdir build
cd build
cmake Unix Makefiles ..
make
./main
```

## Usage (Windows + MSVC):
* I recommend using git for windows found here: https://gitforwindows.org/ ,
this prevents the manual setting up of environmental variables to access git through cmd.

* Install most recent Microsoft Visual Studio version, with the "Desktop Development for C++" in the installation. 
 * Follow commands below using git bash in desired directory. 
```bash
git clone --recursive https://github.com/RomulusC/3DGraphics.git
cd 3DGraphics
mkdir build
cd build
cmake -G "[INSTALLED MSVC VERSION]" .. #Replace [INSTALLED MSVC VERSION] with your installed version. e.g:
# cmake -G "Visual Studio 16 2019" ..
```
* Open the Sandbox.sln
* Right click on the "Solution 'Sandbox'" and select "Single startup project" to "Main"

![output result](BuildStartupProject.png)

* Run the project




