@echo off
SET "BUILD_DIR=build"
SET "OUTPUT_DIR=output"
SET "GENERATOR=Ninja" 

echo [STEP 1] Configuring project with CMake...
cmake -S . -B "%BUILD_DIR%" -G "%GENERATOR%"
IF %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake configuration failed with Ninja. Switching generator.
    pause
    SET "GENERATOR=MinGW Makefiles"
    cmake -S . -B "%BUILD_DIR%" -G "%GENERATOR%"
)
IF %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake configuration failed. Exiting.
    pause
    exit /b 1
)

echo [STEP 2] Building project...
cmake --build "%BUILD_DIR%"

IF %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake build failed. Exiting.
    pause
    exit /b 1
)

echo [STEP 3] Running the executable...

FOR %%F IN ("%OUTPUT_DIR%\*.exe") DO (
    echo Found executable: %%F
    call "%%F"
    GOTO end_run
)

echo [WARNING] No executable found in "%OUTPUT_DIR%".
:end_run

echo [INFO] Script finished.
pause
