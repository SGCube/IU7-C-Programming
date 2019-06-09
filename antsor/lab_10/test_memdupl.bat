@echo off
drmemory -- app.exe d tests_dupl/in_%1.txt out.txt
fc out.txt tests_dupl\out_%1.txt
pause