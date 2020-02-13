@echo off
app.exe a tests_a/in_%1_0.txt tests_a/in_%1_1.txt out.txt
fc out.txt tests_a\out_%1.txt
pause