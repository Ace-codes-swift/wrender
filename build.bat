@echo off

REM Check for -clean argument
if "%1"=="-clean" (
    rmdir /s /q build
    mkdir build
)

REM Configure with CMake
cmake -S . -B build

REM Build
cmake --build build

REM Run executable
build\WRender.exe