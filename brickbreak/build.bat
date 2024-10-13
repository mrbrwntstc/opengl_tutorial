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

set SRC_FILES="main.cpp"
set INCLUDE_DIRS="/I."

echo %THRDPRTY_INCLUDES% %INCLUDE_DIRS% %SRC_FILES% "%THRDPRTY_GLAD%\src\glad.c" > compile_link.rsp
echo /link /out:brickbreak.exe /LIBPATH:"%THRDPRTY_GLFW%\lib-vc2022" %LIBS_PATHS% >> compile_link.rsp
cl /MD /EHsc @compile_link.rsp

:: clean up
del compile_link.rsp
del *.obj
