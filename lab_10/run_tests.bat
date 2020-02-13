@echo off
cls

for %%i in (0 1 2 3) do call test_pop_back.bat %%i
for %%i in (0 1 2 3 4 5) do call test_insert.bat %%i
for %%i in (0 1 2 3 4 5 6) do call test_dupl.bat %%i
for %%i in (0 1 2 3 4) do call test_sort.bat %%i