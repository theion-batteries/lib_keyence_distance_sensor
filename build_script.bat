mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make
.\keyence_bin.exe
cd ../docs
doxygen