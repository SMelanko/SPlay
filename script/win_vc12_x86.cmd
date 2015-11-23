@echo off

mkdir ..\build\vc14_x86
pushd ..\build\vc14_x86

cmake^
	-G"Visual Studio 12 2013" -T "v120_xp" ^
	"-Wno-dev" ^
	../..

if errorlevel 1 goto :error

echo [*] Project generation succeeded!

popd
goto :eof

:error
echo [!] ERROR: Failed to generate project... See above and correct!
popd
exit /b 1