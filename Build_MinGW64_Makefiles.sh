#CAN ONLY BE RUN WITH: MSYS2 MING64 SHELL. Toutorial found here:
# https://stackoverflow.com/questions/30069830/how-to-install-mingw-w64-and-msys2
rm -rf build
mkdir build
cd build
MSYS2_ARG_CONV_EXCL=- cmake .. -G"MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=$MINGW_PREFIX -DCMAKE_BUILD_TYPE=Debug
make
cd Sandbox
./Sandbox.exe
