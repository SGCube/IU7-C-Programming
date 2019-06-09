@echo off
app.exe b tests_pop_back/in_%1.txt out.txt
fc out.txt tests_pop_back\out_%1.txt
pause