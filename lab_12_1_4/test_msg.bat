@echo off
app.exe tests\in_%1.txt > out.txt out2.txt f
fc out.txt tests\out_%1.txt
pause