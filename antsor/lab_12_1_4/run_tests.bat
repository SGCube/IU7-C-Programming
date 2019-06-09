@echo off
cls
for %%i in (0 1 2 3 4 10) do call test_msg.bat %%i
for %%i in (5 6 7 8 9) do call test_file.bat %%i
for %%i in (0 1 2 3 4 5 6 7 8 9 10) do call test_mem.bat %%i