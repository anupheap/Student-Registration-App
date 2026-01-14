@echo off
echo ------------------------------------------------
echo   Building Student Grouping App (Standalone)
echo ------------------------------------------------

:: Creates Output Folder if it doesn't exist
if not exist output mkdir output
if not exist output\assets mkdir output\assets
if not exist output\assets\fonts mkdir output\assets\fonts
if not exist output\assets\textures mkdir output\assets\textures

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

if not exist output\assets\textures\confirm_button.png (
    echo [WARNING] confirm_button.png not yet found! Pulling it from the source file...
    copy /Y assets\textures\confirm_button.png output\assets\textures\
) else (
    echo [OKAY] confirm_button.png found.
)

if not exist output\assets\textures\confirm_hover.png (
    echo [WARNING] confirm_hover.png not yet found! Pulling it from the source file...
    copy /Y assets\textures\confirm_hover.png output\assets\textures\
) else (
    echo [OKAY] confirm_hover.png found.
)

if not exist output\assets\textures\confirm_pressed.png (
    echo [WARNING] confirm_pressed.png not yet found! Pulling it from the source file...
    copy /Y assets\textures\confirm_pressed.png output\assets\textures\
) else (
    echo [OKAY] confirm_pressed.png found.
)

if not exist output\assets\fonts\Orbitron-SemiBold.ttf (
    echo [WARNING] Orbitron-SemiBold.ttf not yet found! Pulling it from the source file...
    copy /Y assets\fonts\Orbitron-SemiBold.ttf output\assets\fonts\
) else (
    echo [OKAY] Orbitron-SemiBold.ttf found.
)

if not exist output\assets\fonts\Sekuya-Regular.ttf (
    echo [WARNING] Sekuya-Regular.ttf not yet found! Pulling it from the source file...
    copy /Y assets\fonts\Sekuya-Regular.ttf output\assets\fonts\
) else (
    echo [OKAY] Sekuya-Regular.ttf found.
)
::Compiles the code
echo Compiling...
g++ main1.cpp -o output/main1.exe -O2 -I include -L lib -lraylib -lopengl32 -lgdi32 -lwinmm -static -mwindows

:: Error Detection
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build Failed! Check your code.
    pause
    exit /b
)

echo [SUCCESS] Running Application...
echo.

output\main1.exe