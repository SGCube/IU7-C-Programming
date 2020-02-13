@echo off

drmemory -- app.exe ftests/in_1.txt out.txt -s ABCDEF -r abk
pause

drmemory -- app.exe ftests/in_2.txt out.txt -s a -r !
pause

drmemory -- app.exe ftests/in_3.txt out.txt -s c -r !
pause

drmemory -- app.exe ftests/in_4.txt out.txt -s a -r !
pause

drmemory -- app.exe ftests/in_5.txt out.txt -s abcdeabcdea -r ?abc!
pause

drmemory -- app.exe ftests/in_6.txt out.txt -s abc -r xyz_
pause

drmemory -- app.exe ftests/in_7.txt out.txt -s def -r _xyz_
pause

drmemory -- app.exe ftests/in_8.txt out.txt -s fgh -r _xyz
pause

drmemory -- app.exe ftests/in_9.txt out.txt -s bcde -r ?
pause

drmemory -- app.exe ftests/in_10.txt out.txt -s abc -r bb
pause

drmemory -- app.exe ftests/in_11.txt out.txt -s a -r ccc
pause

drmemory -- app.exe ftests/in_12.txt out.txt -s aa -r bbb!
pause

drmemory -- app.exe ftests/in_13.txt out.txt -s aa -r bbb!
pause

drmemory -- app.exe ftests/in_14.txt out.txt -s 12 -r 73
pause
