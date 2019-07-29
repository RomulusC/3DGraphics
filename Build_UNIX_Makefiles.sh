rm -rf build
mkdir build
cp Engine\vendors\CMakeLists\ImGui\CMakeLists.txt Engine\vendors\imgui
cd build
cmake Unix Makefiles -DCMAKE_BUILD_TYPE=Debug ..
make
cd Sandbox
./Sandbox
