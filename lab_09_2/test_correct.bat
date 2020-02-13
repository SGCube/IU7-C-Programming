@echo off

app.exe ftests/in_1.txt out.txt -s ABCDEF -r abk
fc out.txt ftests\out_1.txt
pause

app.exe ftests/in_2.txt out.txt -s a -r !
fc out.txt ftests\out_2.txt
pause

app.exe ftests/in_3.txt out.txt -s c -r !
fc out.txt ftests\out_3.txt
pause

app.exe ftests/in_4.txt out.txt -s a -r !
fc out.txt ftests\out_4.txt
pause

app.exe ftests/in_5.txt out.txt -s abcdeabcdea -r ?abc!
fc out.txt ftests\out_5.txt
pause

app.exe ftests/in_6.txt out.txt -s abc -r xyz_
fc out.txt ftests\out_6.txt
pause

app.exe ftests/in_7.txt out.txt -s def -r _xyz_
fc out.txt ftests\out_7.txt
pause

app.exe ftests/in_8.txt out.txt -s fgh -r _xyz
fc out.txt ftests\out_8.txt
pause

app.exe ftests/in_9.txt out.txt -s bcde -r ?
fc out.txt ftests\out_9.txt
pause

app.exe ftests/in_10.txt out.txt -s abc -r bb
fc out.txt ftests\out_10.txt
pause

app.exe ftests/in_11.txt out.txt -s a -r ccc
fc out.txt ftests\out_11.txt
pause

app.exe ftests/in_12.txt out.txt -s aa -r bbb!
fc out.txt ftests\out_12.txt
pause

app.exe ftests/in_13.txt out.txt -s aa -r bbb!
fc out.txt ftests\out_13.txt
pause

app.exe ftests/in_14.txt out.txt -s 12 -r 73
fc out.txt ftests\out_14.txt
pause
