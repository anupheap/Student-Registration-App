@echo off
echo ------------------------------------------------
echo   Building Student Grouping App (Standalone)
echo ------------------------------------------------

:: Creates Output Folder if it doesn't exist
if not exist output mkdir output
if not exist output\textures mkdir output\textures

:: Makes sure opengl32.dll is in the output folder
if exist output\opengl32.dll (
    copy /Y opengl32.dll output\ > nul
    echo [OKAY] Copied opengl32.dll to output folder.
)

:: Pull in raylib.dll if not already present
if not exist output\raylib.dll (
    echo [WARNING] raylib.dll not yet found! Pulling it from the source file...
    copy /Y raylib.dll output\
) else (
    echo [OKAY] raylib.dll found.
)

if not exist output\textures\confirm_button.png (
    echo [WARNING] confirm_button.png not yet found! Pulling it from the source file...
    copy /Y textures\confirm_button.png output\textures\
) else (
    echo [OKAY] confirm_button.png found.
)

if not exist output\textures\confirm_hover.png (
    echo [WARNING] confirm_hover.png not yet found! Pulling it from the source file...
    copy /Y textures\confirm_hover.png output\textures\
) else (
    echo [OKAY] confirm_hover.png found.
)


if not exist output\textures\confirm_pressed.png (
    echo [WARNING] confirm_pressed.png not yet found! Pulling it from the source file...
    copy /Y textures\confirm_pressed.png output\textures\
) else (
    echo [OKAY] confirm_pressed.png found.
)
::Compiles the code
echo Compiling...
g++ main.cpp -o output/main.exe -O2 -I include -L lib -lraylib -lopengl32 -lgdi32 -lwinmm -static -mwindows

:: Error Detection
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build Failed! Check your code.
    pause
    exit /b
)

echo [SUCCESS] Running Application...
echo.

output\main.exe