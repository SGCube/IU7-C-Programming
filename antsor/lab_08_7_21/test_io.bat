@echo off
app.exe o tests_io\in_%1.txt > out.txt tests\out.txt
fc out.txt tests_io\out_%1.txt
pause