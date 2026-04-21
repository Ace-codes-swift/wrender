@echo off

if "%1"=="-clean" rmdir /s /q build

if not exist build mkdir build

cmake -S . -B build
cmake --build build

build\WRender.exe
