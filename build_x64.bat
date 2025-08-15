@echo off
REM --- 1. Активуємо середовище для x64-компілятора ---
call "E:\Microsoft Visual Studio\VC\Auxiliary\Build\vcvars64.bat"

REM --- 2. Переходимо у каталог проекту ---
cd /d C:\Users\User\source\repos\My3DEngine\My3DEngine

REM --- 3. Очищаємо старий build ---
if exist build rmdir /S /Q build

REM --- 4. Запускаємо CMake з vcpkg toolchain ---
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=E:/VcPkG/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows

REM --- 5. Збираємо проект (Debug)
cmake --build build --config Debug

pause