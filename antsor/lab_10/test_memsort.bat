@echo off
drmemory -- app.exe s tests_sort/in_%1.txt out.txt
fc out.txt tests_sort\out_%1.txt
pause