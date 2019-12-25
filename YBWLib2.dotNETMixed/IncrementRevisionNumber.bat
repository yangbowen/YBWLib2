@echo off
setlocal enabledelayedexpansion

for /f "eol=#" %%a in (RevisionNumber.txt) do (
	set /a VERSION_REVISION=%%a
)

set /a VERSION_REVISION_NEXT=!VERSION_REVISION!+1

set /p=!VERSION_REVISION_NEXT!<nul>RevisionNumber.txt

set /p=^<# System.UInt32 RevisionNumber_YBWLib2_dotNETMixed = !VERSION_REVISION!; #^><nul>RevisionNumber.t4

endlocal
