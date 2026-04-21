rem used to disable the echo of the commands in the batch file so it doesnt print the commands to the console
@echo off

REM Check for -clean argument
if "%1"=="-clean" (
   
   rem remove the build directory
    rmdir /s /q build
    rem create the build directory
    mkdir build
)

mkdir build

REM Configure with CMake
cmake -S . -B build

REM Build
cmake --build build

REM Run executable
build\WRender.exe

