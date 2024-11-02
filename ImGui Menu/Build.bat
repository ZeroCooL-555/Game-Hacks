@echo off

:: ====================[ PATH CONFIGURATION ] ====================================

:: Set the project name
SET PROJECT_NAME=Menu-Base

:: Set the root directory (Current Working Directory) without trailing backslash
SET CWD=%~dp0
IF "%CWD:~-1%"=="\" SET CWD=%CWD:~0,-1%

:: Set the build directory
SET WORK_DIR=%CWD%\TEMP_WORK

:: Set the destination directories for libraries and includes
SET LIB_DEST_DIR=%CWD%\%PROJECT_NAME%\lib
SET INCLUDE_DEST_DIR=%CWD%\%PROJECT_NAME%\include

:: Set the destination directories for GLEW and GLFW
SET GLEW_SOURCE_DIR=%WORK_DIR%\glew-2.1.0
SET GLFW_SOURCE_DIR=%WORK_DIR%\glfw-master
SET GLFW_SOURCE_DIR_BUILD=%GLFW_SOURCE_DIR%\Build

:: Create necessary directories
IF NOT EXIST "%WORK_DIR%" MKDIR "%WORK_DIR%"
IF NOT EXIST "%GLFW_SOURCE_DIR_BUILD%" MKDIR "%GLFW_SOURCE_DIR_BUILD%"
IF NOT EXIST "%LIB_DEST_DIR%" MKDIR "%LIB_DEST_DIR%"
IF NOT EXIST "%INCLUDE_DEST_DIR%" MKDIR "%INCLUDE_DEST_DIR%"

:: ==================================================================================


:: ==============================[ START OF BUILD PROCESS ] ======================================

:: Move into WORK_DIR
CD %WORK_DIR%

:: Check if CMake is installed
cmake --version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
    ECHO ======[ CMake Not Installed! ]======
    EXIT /B
)

:: Move into WORK_DIR directory
CD %WORK_DIR%

:: Download and extract GLEW
ECHO "[+] Downloading and extracting GLEW"
curl -L https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download -o glew-2.1.0-win32.zip
IF %ERRORLEVEL% NEQ 0 (
    ECHO "Error downloading GLEW. Check your internet connection."
    EXIT /B
)
tar -xf glew-2.1.0-win32.zip

:: Copy GLEW headers and libraries
ECHO "[+] Copying GLEW headers and libraries..."
ECHO F | XCOPY "%GLEW_SOURCE_DIR%\include\GL" "%INCLUDE_DEST_DIR%\GL" /E /I /Y
ECHO F | XCOPY "%GLEW_SOURCE_DIR%\lib\Release\Win32\glew32s.lib" "%LIB_DEST_DIR%\glew32s_x86.lib" /I /Y
ECHO F | XCOPY "%GLEW_SOURCE_DIR%\lib\Release\x64\glew32s.lib" "%LIB_DEST_DIR%\glew32s_x64.lib" /I /Y

:: Download and extract GLFW
ECHO "[+] Downloading and extracting GLFW"
curl -L https://github.com/glfw/glfw/archive/refs/heads/master.zip -o glfw-master.zip
IF %ERRORLEVEL% NEQ 0 (
    ECHO "Error downloading GLFW. Check your internet connection."
    EXIT /B
)
tar -xf glfw-master.zip

:: Build GLFW for Win32
ECHO "[+] Configuring and building GLFW for Win32"
cmake -G "Visual Studio 17 2022" -A Win32 -S "%GLFW_SOURCE_DIR%" -B "%GLFW_SOURCE_DIR_BUILD%"
IF %ERRORLEVEL% NEQ 0 (
    ECHO "CMake configuration failed for Win32. Check if Visual Studio 17 2022 is installed."
    EXIT /B
)
cmake --build "%GLFW_SOURCE_DIR_BUILD%" --config Debug --target INSTALL
ECHO F | XCOPY "%GLFW_SOURCE_DIR%\include\GLFW" "%INCLUDE_DEST_DIR%\GLFW" /E /I /Y
ECHO F | XCOPY "%GLFW_SOURCE_DIR_BUILD%\src\Debug\glfw3.lib" "%LIB_DEST_DIR%\glfw3_x86.lib" /I /Y

:: Clean up Win32 build to prepare for x64
RMDIR /S /Q "%GLFW_SOURCE_DIR_BUILD%"
MKDIR "%GLFW_SOURCE_DIR_BUILD%"

:: Build GLFW for x64
ECHO "[+] Configuring and building GLFW for x64"
cmake -G "Visual Studio 17 2022" -A x64 -S "%GLFW_SOURCE_DIR%" -B "%GLFW_SOURCE_DIR_BUILD%"
IF %ERRORLEVEL% NEQ 0 (
    ECHO "CMake configuration failed for x64. Check if Visual Studio 17 2022 is installed."
    EXIT /B
)
cmake --build "%GLFW_SOURCE_DIR_BUILD%" --config Debug --target INSTALL
ECHO F | XCOPY "%GLFW_SOURCE_DIR_BUILD%\src\Debug\glfw3.lib" "%LIB_DEST_DIR%\glfw3_x64.lib" /I /Y

ECHO "[+] Build process completed successfully."

:: Cleanup
CD %CWD%
RMDIR /S /Q "%WORK_DIR%"
