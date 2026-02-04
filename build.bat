@echo off
SET "BUILD_DIR=build"
SET "OUTPUT_DIR=output"
SET "GENERATOR=Ninja" 

REM --- Step 1: Run CMake to configure the project ---
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

REM --- Step 2: Build the project ---
echo [STEP 2] Building project...
cmake --build "%BUILD_DIR%"

IF %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake build failed. Exiting.
    pause
    exit /b 1
)

REM --- Step 3: Run the executable from the output folder ---
REM Note: This assumes a single .exe is placed in the .\output\ folder during the build process.
echo [STEP 3] Running the executable...

REM Find the first executable in the output directory and run it
FOR %%F IN ("%OUTPUT_DIR%\*.exe") DO (
    echo Found executable: %%F
    call "%%F"
    GOTO end_run
)

echo [WARNING] No executable found in "%OUTPUT_DIR%".
:end_run

echo [INFO] Script finished.
pause
