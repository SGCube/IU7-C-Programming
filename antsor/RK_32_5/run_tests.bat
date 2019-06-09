@echo off
cls

for %%i in (0 1 2 3 8 9) do call test_incorrect.bat %%i
for %%i in (4 5 6 7) do call test_correct.bat %%i