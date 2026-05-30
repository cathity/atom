@echo off
chcp 65001 >nul
echo ============================================
echo  Projekt GK - Model Atomu (Windows)
echo ============================================
echo.

where cmake >nul 2>&1
if errorlevel 1 (
    echo BLAD: Nie znaleziono CMake. Zainstaluj CMake lub Visual Studio z workload C++.
    echo Zobacz INSTALACJA_WINDOWS.md
    exit /b 1
)

where git >nul 2>&1
if errorlevel 1 (
    echo BLAD: Nie znaleziono Git. Potrzebny do pobrania GLFW i GLM.
    echo Pobierz: https://git-scm.com/download/win
    exit /b 1
)

echo [1/2] Konfiguracja CMake...
cmake -B build -S .
if errorlevel 1 (
    echo BLAD konfiguracji. Zobacz INSTALACJA_WINDOWS.md
    exit /b 1
)

echo.
echo [2/2] Kompilacja Release...
cmake --build build --config Release
if errorlevel 1 (
    echo BLAD kompilacji.
    exit /b 1
)

echo.
echo ============================================
echo  GOTOWE!
echo  Uruchom:  build\Release\atom.exe
echo ============================================
echo.
