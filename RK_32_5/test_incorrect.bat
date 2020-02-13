@echo off
app.exe ftests/in_%1.txt > out_err.txt out.txt
fc out_err.txt ftests\out_%1.txt
pause