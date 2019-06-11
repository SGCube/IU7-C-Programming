gcc -std=c99 -Wall -Werror -pedantic -c test.c
gcc -std=c99 -Wall -Werror -pedantic -c array.c
gcc -std=c99 -Wall -Werror -pedantic -c process.c
gcc -o test.exe array.o process.o test.o