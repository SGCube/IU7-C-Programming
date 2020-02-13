@echo off
cls

for %%i in (0 1 2 3) do call test_mempopback.bat %%i
for %%i in (0 1 2 3 4 5) do call test_meminsert.bat %%i
for %%i in (0 1 2 3 4 5 6) do call test_memdupl.bat %%i
for %%i in (0 1 2 3 4) do call test_memsort.bat %%i