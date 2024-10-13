@echo off

:: Set the directories where GLAD and GLFW are located
set THRDPRTY=C:\thrdprty

set THRDPRTY_GLFW=%THRDPRTY%\libs\glfw-3.4.bin.WIN64
set THRDPRTY_GLAD=%THRDPRTY%\glad

:: Set the include paths for GLAD and GLFW
set THRDPRTY_INCLUDES=/I"%THRDPRTY_GLFW%\include" /I"%THRDPRTY_GLAD%\include"

:: Set the library paths for GLFW and necessary system libraries
set LIBS_PATHS=glfw3.lib opengl32.lib gdi32.lib user32.lib kernel32.lib shell32.lib

:: Set up the Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

for %%f in (%1) do set EXE_NAME=%%~nf

:: Create a response file to compile and link the project
:: ---
:: source + header files
echo %THRDPRTY_INCLUDES% %1 "%THRDPRTY_GLAD%\src\glad.c" > compile_link.rsp
:: link
echo /link /out:%EXE_NAME%.exe /LIBPATH:"%THRDPRTY_GLFW%\lib-vc2022" %LIBS_PATHS% >> compile_link.rsp

:: Print and execute the compile command using the response file
echo cl /EHsc @compile_link.rsp
cl /MD /EHsc @compile_link.rsp

:: Clean up
del compile_link.rsp
del *.obj

