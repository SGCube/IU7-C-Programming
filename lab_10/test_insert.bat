@echo off
app.exe i tests_insert/data_%1.txt out.txt < tests_insert/in_%1.txt
fc out.txt tests_insert\out_%1.txt
pause