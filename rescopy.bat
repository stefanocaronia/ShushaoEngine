@REM Inserti in Code-blocks Project root
@REM Pre-Build Steps: cmd /c rescopy <Debug|Release>
@%WINDIR%\system32\robocopy res\ bin\%1\ /MIR /XF *.exe /nfl /ndl /njh /njs /nc /ns /np  > nul
@SET ERRNO = %ERRORLEVEL%
@REM @if %ERRORLEVEL% EQU 16 echo RES COPY RESULT: ***FATAL ERROR*** & goto error
@REM @if %ERRORLEVEL% EQU 15 echo RES COPY RESULT: OKCOPY + FAIL + MISMATCHES + XTRA & goto error
@REM @if %ERRORLEVEL% EQU 14 echo RES COPY RESULT: FAIL + MISMATCHES + XTRA & goto error
@REM @if %ERRORLEVEL% EQU 13 echo RES COPY RESULT: OKCOPY + FAIL + MISMATCHES & goto error
@REM @if %ERRORLEVEL% EQU 12 echo RES COPY RESULT: FAIL + MISMATCHES& goto error
@REM @if %ERRORLEVEL% EQU 11 echo RES COPY RESULT: OKCOPY + FAIL + XTRA & goto end
@REM @if %ERRORLEVEL% EQU 10 echo RES COPY RESULT: FAIL + XTRA & goto error
@REM @if %ERRORLEVEL% EQU 9 	echo RES COPY RESULT: OKCOPY + FAIL & goto end
@REM @if %ERRORLEVEL% EQU 8 	echo RES COPY RESULT: FAIL & goto error
@REM @if %ERRORLEVEL% EQU 7 	echo RES COPY RESULT: OKCOPY + MISMATCHES + XTRA & goto end
@REM @if %ERRORLEVEL% EQU 6 	echo RES COPY RESULT: MISMATCHES + XTRA & goto end
@REM @if %ERRORLEVEL% EQU 5 	echo RES COPY RESULT: OKCOPY + MISMATCHES & goto end
@REM @if %ERRORLEVEL% EQU 4 	echo RES COPY RESULT: MISMATCHES & goto end
@REM @if %ERRORLEVEL% EQU 3 	echo RES COPY RESULT: OKCOPY + XTRA & goto end
@REM @if %ERRORLEVEL% EQU 2 	echo RES COPY RESULT: No Change + XTRA & goto end
@REM @if %ERRORLEVEL% EQU 1 	echo RES COPY RESULT: OKCOPY & goto end
@REM @if %ERRORLEVEL% EQU 0 	echo RES COPY RESULT: No Change & goto end
:error
@EXIT /B %ERRNO%
:end
