@echo off
REM Smoke test build script: activate MSVC env, configure with Ninja, build
REM Usage: run scripts\smoke_build.bat from project root

set VCPKG_ROOT=C:\dev\vcpkg
set VCVARS=C:\Program Files\Microsoft Visual Studio\18\Professional\VC\Auxiliary\Build\vcvarsall.bat
set NINJA_DIR=C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja

REM Put ninja dir first on PATH
set "PATH=%NINJA_DIR%;%PATH%"

REM Activate MSVC x64 build environment
call "%VCVARS%" x64
if errorlevel 1 (
    echo [ERROR] vcvarsall.bat failed
    exit /b 1
)

echo === cl.exe check ===
where cl
if errorlevel 1 (
    echo [ERROR] cl.exe not found after vcvars
    exit /b 1
)

echo === ninja check ===
where ninja
if errorlevel 1 (
    echo [ERROR] ninja not found
    exit /b 1
)

echo === CMake configure ===
cmake -B build -S . -G Ninja ^
    -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake ^
    -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 (
    echo [ERROR] CMake configure failed
    exit /b 1
)

echo === Build ===
cmake --build build
if errorlevel 1 (
    echo [ERROR] Build failed
    exit /b 1
)

echo.
echo === BUILD OK ===
echo exe: build\mini-rend.exe
