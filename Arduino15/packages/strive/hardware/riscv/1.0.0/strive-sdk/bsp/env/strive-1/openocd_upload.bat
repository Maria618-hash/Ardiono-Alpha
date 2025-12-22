@echo off
REM Author: Taimur Islam Khan
REM Date: 01 Nov, 2022

setlocal enabledelayedexpansion

REM Echoing all arguments
echo Original Argument 1: %1
echo Original Argument 2: %2
echo Original Argument 3: %3
echo Original Argument 4: %4
echo Original Argument 5: %5

REM Replacing backslashes with forward slashes
set "arg1=%1"
set "arg2=%2"
set "arg3=%3"
set "arg4=%4"
set "arg5=%5"

set "arg1=!arg1:\=/!"
set "arg2=!arg2:\=/!"
set "arg3=!arg3:\=/!"
set "arg4=!arg4:\=/!"
set "arg5=!arg5:\=/!"

REM Verify arguments
if not defined arg1 echo "Argument 1 is missing!" & exit /b 1
if not exist "!arg3!" echo "OpenOCD path (!arg3!) does not exist!" & exit /b 1

REM Echo modified arguments
echo Modified Argument 1: !arg1!
echo Modified Argument 2: !arg2!
echo Modified Argument 3: !arg3!
echo Modified Argument 4: !arg4!
echo Modified Argument 5: !arg5!

REM Execute OpenOCD command
echo Running OpenOCD command...
"!arg5!" -f "!arg2!" -c "reset halt; load_image !arg1!; resume 0x0; exit"

endlocal
