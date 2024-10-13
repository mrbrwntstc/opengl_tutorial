@echo off

:: Set the directories where GLAD and GLFW are located
set THRDPRTY=C:\thrdprty

set THRDPRTY_GLFW=%THRDPRTY%\libs\glfw-3.4.bin.WIN64
set THRDPRTY_GLAD=%THRDPRTY%\glad

:: Set the include paths for GLAD and GLFW
set THRDPRTY_INCLUDES=/I"%THRDPRTY%" /I"%THRDPRTY_GLFW%\include" /I"%THRDPRTY_GLAD%\include"

:: Set the library paths for GLFW and necessary system libraries
set LIBS_PATHS=glfw3.lib opengl32.lib gdi32.lib user32.lib kernel32.lib shell32.lib

:: Set up the Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

set SRC_FILES=
set INCLUDE_DIRS=
set EXE_NAME=

:: Iterate over all passed arguments
:parse_arguments
if "%~1"=="" goto done_arguments

if "%~x1"==".cpp" (
  :: Source file
  set SRC_FILES=%SRC_FILES% "%~1"
) else if "%~x1"==".exe" (
  :: Executable name
  set EXE_NAME=%~n1
) else (
  :: header directory
  set INCLUDE_DIRS=%INCLUDE_DIRS% /I"%~1"
)

shift
goto parse_arguments

:done_arguments

:: Create a response file to compile and link the project
:: --- 
:: Source + header files
echo %THRDPRTY_INCLUDES% %INCLUDE_DIRS% %SRC_FILES% "%THRDPRTY%\stb_image.c" "%THRDPRTY_GLAD%\src\glad.c" > compile_link.rsp
:: Link
echo /link /out:%EXE_NAME%.exe /LIBPATH:"%THRDPRTY_GLFW%\lib-vc2022" %LIBS_PATHS% >> compile_link.rsp

:: Print and execute the compile command using the response file
echo cl /EHsc @compile_link.rsp
cl /MD /EHsc @compile_link.rsp

:: Clean up
del compile_link.rsp
del *.obj

