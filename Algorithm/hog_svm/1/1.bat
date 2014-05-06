dir /b /s /p /w *.bmp >num.txt
pause
setlocal enabledelayedexpansion
for /f "delims=  " %%a in (num.txt) do (
set /a line =1
echo %%a >>1.txt
echo !line! >>1.txt
)