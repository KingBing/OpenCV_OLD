dir /b /s /p /w *.bmp >num.txt
pause
setlocal enabledelayedexpansion
for /f "delims=  " %%a in (num.txt) do (
set /a line =4
echo %%a >>4.txt
echo !line! >>4.txt
)