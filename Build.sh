rm -rf build
mkdir build
cd build
cmake Unix Makefiles -DCMAKE_BUILD_TYPE=Debug ..
make
./Application
