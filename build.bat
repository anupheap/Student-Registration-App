@echo off
echo ------------------------------------------------
echo   Building Student Grouping App (Standalone)
echo ------------------------------------------------

:: 1. Create output folder if missing
if not exist output mkdir output

:: 2. Copy VM Graphics Fix (if present)
if exist opengl32.dll (
    copy /Y opengl32.dll output\ >nul
    echo [OK] OpenGL Fix copied.
)

:: 3. Compile
:: -static : Bakes libraries into the exe so it runs anywhere
:: -mwindows : Hides the black console window
echo Compiling...
g++ main.cpp -o output/main.exe -O2 -I include -L lib -lraylib -lopengl32 -lgdi32 -lwinmm -static -mwindows

:: 4. Check for errors
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build Failed! Check your code.
    pause
    exit /b
)

echo [SUCCESS] Running Application...
echo.

:: 5. Run it
output\main.exe