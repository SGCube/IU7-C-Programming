@echo off
app.exe m tests_m/in_%1_0.txt tests_m/in_%1_1.txt out.txt
fc out.txt tests_m\out_%1.txt
pause