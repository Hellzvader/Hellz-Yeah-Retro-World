@echo off
setlocal
cd /d "%~dp0"
where cmake >nul 2>nul
if errorlevel 1 (
 echo CMake was not found. Install Visual Studio 2022 Desktop development with C++ and CMake.
 pause
 exit /b 1
)
cmake -S . -B build -A x64
if errorlevel 1 goto fail
cmake --build build --config Release
if errorlevel 1 goto fail
echo.
echo BUILD COMPLETE
echo EXE: %CD%\build\Release\HellzYeahRetroEngine.exe
pause
exit /b 0
:fail
echo.
echo BUILD FAILED - see errors above.
pause
exit /b 1
