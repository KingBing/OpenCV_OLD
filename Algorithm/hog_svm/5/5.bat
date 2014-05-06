dir /b /s /p /w *.bmp >num.txt
pause
setlocal enabledelayedexpansion
for /f "delims=  " %%a in (num.txt) do (
set /a line =5
echo %%a >>5.txt
echo !line! >>5.txt
)