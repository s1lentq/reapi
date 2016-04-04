@echo OFF
::
:: Post-build auto-deploy script
:: Create and fill PublishPath.txt file with path to deployment folder
:: I.e. PublishPath.txt should contain one line with a folder path
:: Call it so:
:: IF EXIST "$(ProjectDir)PostBuild.bat" (CALL "$(ProjectDir)PostBuild.bat" "$(TargetDir)" "$(TargetName)" "$(TargetExt)" "$(ProjectDir)")
::

SET hlds=ServerStart_cs
SET status=0

SET targetDir=%~1
SET targetName=%~2
SET targetExt=%~3
SET projectDir=%~4
SET destination=

IF EXIST "%hlds%.bat" (
	set status=1
)
echo "%projectDir%\PublishPath.txt"

IF NOT EXIST "%projectDir%\PublishPath.txt" (
	ECHO 	No deployment path specified. Create PublishPath.txt near PostBuild.bat with paths on separate lines for auto deployment.
	exit /B 0
)

FOR /f "tokens=* delims= usebackq" %%a IN ("%projectDir%\PublishPath.txt") DO (
	ECHO Deploying to: %%a
	IF NOT "%%a" == "" (
		copy /Y "%targetDir%%targetName%%targetExt%" "%%a"

		IF "%status%" == "1" (
			SET status=1
		)

		IF NOT ERRORLEVEL 1 (
			IF EXIST "%targetDir%%targetName%.pdb" (
				copy /Y "%targetDir%%targetName%.pdb" "%%a"
			)
		) ELSE (
			ECHO PostBuild.bat ^(27^) : warning : Can't copy '%targetName%%targetExt%' to deploy path '%%a'
		)
	)
)

IF "%status%" == "2" (
	start %hlds%.bat
)

IF "%%a" == "" (
	ECHO 	No deployment path specified.
)

exit /B 0