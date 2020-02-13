@echo off
app.exe ftests/in_%1.txt out.txt
fc out.txt ftests\out_%1.txt
pause