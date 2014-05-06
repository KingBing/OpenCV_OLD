dir /b /s /p /w *.bmp >num.txt
pause
setlocal enabledelayedexpansion
for /f "delims=  " %%a in (num.txt) do (
set /a line =3
echo %%a >>3.txt
echo !line! >>3.txt
)
