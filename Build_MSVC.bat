mkdir build
xcopy /y ".\Engine\vendors\CMakeLists\ImGui\CMakeLists.txt" ".\Engine\vendors\imgui"
cd build
	
cmake -G "Visual Studio 16 2019" -A x64 ..
PAUSE