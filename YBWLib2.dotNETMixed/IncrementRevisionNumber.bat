@echo off
setlocal enabledelayedexpansion

for /f "eol=#" %%a in (revisionnumber.txt) do (
	set /a VERSION_REVISION=%%a+1
	echo !VERSION_REVISION!>revisionnumber.txt
)

endlocal
