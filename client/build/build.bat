@echo off
REM ============================================================
REM RiftX — Public Release Build
REM riftxboot.mp4 IS the launch screen — no splash image
REM Multi-language support: 9 languages embedded
REM ============================================================

echo.
echo  ==============================
echo   RIFTX - Public Build
echo  ==============================
echo.

if "%XEDK%"=="" (
    echo [ERROR] XEDK environment variable is not set.
    pause
    exit /b 1
)

set OUTDIR=%~dp0bin
if not exist "%OUTDIR%" mkdir "%OUTDIR%"

echo [1/5] Compiling C++ source...
cl /nologo /EHsc /O2 /DNDEBUG ^
   /I"%XEDK%\include\xbox" ^
   /I"%~dp0..\source" ^
   /I"%~dp0..\source\ui" ^
   /c "%~dp0..\source\*.cpp" "%~dp0..\source\ui\*.cpp" ^
   /Fo"%OUTDIR%\\"
if errorlevel 1 ( echo [ERROR] Compile failed. & pause & exit /b 1 )

echo [2/5] Compiling launch video resource...
rc /nologo /fo"%OUTDIR%\riftxboot.res" "%~dp0..\source\resources\video\riftxboot.rc"
if errorlevel 1 ( echo [ERROR] Video resource failed. & pause & exit /b 1 )

echo [3/5] Compiling icon resource...
rc /nologo /fo"%OUTDIR%\icon.res" "%~dp0..\source\resources\icons\icon.rc"

echo [4/5] Compiling font resource...
rc /nologo /fo"%OUTDIR%\fonts.res" "%~dp0..\source\resources\fonts\fonts.rc"

echo [5/5] Compiling 9 language resources + linking...
rc /nologo /fo"%OUTDIR%\lang.res" "%~dp0..\source\resources\lang\lang.rc"

link /nologo /OUT:"%OUTDIR%\RiftX.xex" ^
     /LIBPATH:"%XEDK%\lib\xbox" ^
     "%OUTDIR%\*.obj" ^
     "%OUTDIR%\riftxboot.res" ^
     "%OUTDIR%\icon.res" ^
     "%OUTDIR%\fonts.res" ^
     "%OUTDIR%\lang.res" ^
     xapilib.lib xboxkrnl.lib d3d9.lib xonline.lib xmedia.lib
if errorlevel 1 ( echo [ERROR] Link failed. & pause & exit /b 1 )

echo.
echo   Output: %OUTDIR%\RiftX.xex
echo   Distribute this ONE file.
echo   Languages embedded: EN, ES, FR, DE, IT, PT, RU, JA, ZH
echo.
pause
