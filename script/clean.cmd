@echo off

rd /q /s ..\build

:: Prevent Hudson from stopping the build.
set errorlevel=0