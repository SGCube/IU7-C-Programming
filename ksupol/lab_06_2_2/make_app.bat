gcc -std=c99 -Wall -Werror -pedantic -c main.c
gcc -std=c99 -Wall -Werror -pedantic -c array.c
gcc -std=c99 -Wall -Werror -pedantic -c process.c
gcc -o app.exe array.o process.o main.o