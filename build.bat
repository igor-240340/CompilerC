@echo off
setlocal

echo [1/2] Assembling...
ml64 /c /Fo output.obj output.asm
if errorlevel 1 goto :error

echo [2/2] Linking...
link /SUBSYSTEM:CONSOLE /ENTRY:main output.obj
if errorlevel 1 goto :error

echo Build successful. Output: output.exe
goto :eof

:error
echo Build failed.
exit /b 1
