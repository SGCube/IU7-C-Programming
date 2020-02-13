@echo off

app.exe 2> out_err.txt ftests/in_0.txt out.txt -s aa -r bb
fc out_err.txt ftests\out_0.txt
pause

app.exe 2> out_err.txt ftests/in_-1.txt out.txt -s aa -r bb
fc out_err.txt ftests\out_errfile.txt
pause

app.exe 2> out_err.txt ftests/in_1.txt out.txt -s aa r bb
fc out_err.txt ftests\out_errflag.txt
pause

app.exe 2> out_err.txt ftests/in_1.txt out.txt -s aa
fc out_err.txt ftests\out_errarg.txt
pause
