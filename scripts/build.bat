@echo OFF

cd ..
mkdir build
cd build
cmake -DHW_SDL2_INCLUDE_DIR= -DHW_SDL2_LIBRARY_DIR= ..
cmake --build .

