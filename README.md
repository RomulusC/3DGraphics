## A simple OpenGL application, producing user generated 3D graphics.

![output result](Example.gif)

The focus of this project is to obtain experience in the following:
* Fammiliarize with using CMake for project handling
* Fammiliarize with Linux development
* Complete LearnOpenGL tutorials found on: https://learnopengl.com, https://www.opengl-tutorial.org/, https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT
## Usage (Executable Only):
* Download the file for your operating system, located here: https://github.com/RomulusC/3DGraphics/releases
* Extract, run the executable located inside the folder.
## Usage (General):
Install CMake for your command line. Found at https://cmake.org/download/. Make sure to select "add system PATH for all users" during instillation.
```bash
git clone --recursive https://github.com/RomulusC/3DGraphics.git
```
## Usage (Linux + Unix Makefiles):
* Clone the repository with the --recursive argument. 
* Run the build.sh shellscript.
* Run the Sandbox executable located in /build/Sandbox/.
* The repository includes a .vs folder, including configuration for gdb debugging with Visual Studio Code. (Tested on Fedora 30) 
## Usage (Windows + MSVC):
* Install Git or Git_For_Windows if you haven't already so. 
* Install most recent Microsoft Visual Studio version, with the "Desktop Development for C++" in the installation. 
* Clone the repository with the --recursive argument. 
* Run the build.bat script file. (If your Visual Studio version isn't Visual Studio 16 2019, then edit the batch file to include your installed version. EG: [ cmake -G "Visual Studio 15 2017" -A x64 .. ], additionally you can use the generator type of your choice.)
* Open the Graphics_Dev.sln located in /build.
* Build and Run the Sandbox project