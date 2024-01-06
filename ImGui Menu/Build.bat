@echo off

:: Set the project name
SET PROJECT_NAME="Menu-Base"

:: Set the root directory (Current Working Directory)
SET CWD=%~dp0

:: Set the build directory
SET WORK_DIR=%CWD%\TEMP_WORK

:: Set the destination directories for libraries and includes
SET LIB_DEST_DIR=%CWD%\%PROJECT_NAME%\lib
SET INCLUDE_DEST_DIR=%CWD%\%PROJECT_NAME%\include

:: Set the destination directories for GLEW and GLFW
SET GLEW_SOURCE_DIR=%WORK_DIR%\glew-2.1.0
SET GLFW_SOURCE_DIR=%WORK_DIR%\glfw-master
SET GLFW_SOURCE_DIR_BUILD=%GLFW_SOURCE_DIR%\Build

:: Check if CMake is installed
cmake --version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
    ECHO ======[ CMake Not Installed! ]======
    EXIT /B
)

:: Create the WORK_DIR directory if it doesn't exist
IF NOT EXIST %WORK_DIR% (
    MKDIR %WORK_DIR%
)

:: Create the build directory if it doesn't exist
IF NOT EXIST %GLFW_SOURCE_DIR_BUILD% (
    MKDIR %GLFW_SOURCE_DIR_BUILD%
)

:: Create destination directories if they don't exist
 IF NOT EXIST %LIB_DEST_DIR% (
     MKDIR %LIB_DEST_DIR%
 )

 IF NOT EXIST %INCLUDE_DEST_DIR% (
     MKDIR %INCLUDE_DEST_DIR%
 )



:: Move into WORK_DIR directory
CD %WORK_DIR%

:: Download, extract and copy compiled libraries and headers to the projects lib and include directory
ECHO "[+] Downloading and extracting GLEW"

curl -L https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download -o glew-2.1.0-win32.zip
tar -xf glew-2.1.0-win32.zip


ECHO [+] Copying headers and renaming GLEW libraries...

ECHO F | XCOPY "%GLEW_SOURCE_DIR%\include\GL" "%INCLUDE_DEST_DIR%\GL" /E /I /Y

ECHO F | XCOPY "%GLEW_SOURCE_DIR%\lib\Release\Win32\glew32s.lib" "%LIB_DEST_DIR%\glew32s_x86.lib" /E /I /Y
ECHO F | XCOPY "%GLEW_SOURCE_DIR%\lib\Release\x64\glew32s.lib" "%LIB_DEST_DIR%\glew32s_x64.lib" /E /I /Y




:: clone, build and copy libraries and headers into the include and lib directories
ECHO [+] Downloading and extracting GLFW

curl -L https://github.com/glfw/glfw/archive/refs/heads/master.zip -o glfw-master.zip
tar -xf glfw-master.zip


:: Run CMake to configure and build the project
ECHO [+] Configuring and building the project for Win32...

CD %GLFW_SOURCE_DIR%

cmake -G "Visual Studio 17 2022" -A Win32 -B %GLFW_SOURCE_DIR_BUILD%

CD %GLFW_SOURCE_DIR_BUILD%
cmake --build . --target INSTALL

:: Copy GLFW Win32 library and header files
ECHO F | XCOPY %GLFW_SOURCE_DIR%\include\GLFW %INCLUDE_DEST_DIR%\GLFW /E /I /Y
ECHO F | XCOPY %GLFW_SOURCE_DIR_BUILD%\src\Debug\glfw3.lib %LIB_DEST_DIR%\glfw3_x86.lib /E /I /Y

:: Cleanup the configuration for the Win32 build to start x64 build
CD %GLFW_SOURCE_DIR%
:: DEL %GLFW_SOURCE_DIR_BUILD%
RMDIR /S /Q %GLFW_SOURCE_DIR_BUILD%
MKDIR %GLFW_SOURCE_DIR_BUILD%


:: Copy GLFW x64 library
ECHO [+] Configuring and building the project for x64...

CD %GLFW_SOURCE_DIR%
cmake -G "Visual Studio 17 2022" -A x64 -B %GLFW_SOURCE_DIR_BUILD%

CD %GLFW_SOURCE_DIR_BUILD%
cmake --build . --target INSTALL

ECHO F | XCOPY %GLFW_SOURCE_DIR_BUILD%\src\Debug\glfw3.lib %LIB_DEST_DIR%\glfw3_x64.lib /E /I /Y

ECHO [+] Build process completed.

CD %CWD%
RMDIR /S /Q %WORK_DIR%