CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic 

app.exe : array.o main.o
	${CC} -o app.exe array.o main.o

test.exe : array.o test.o
	${CC} -o test.exe array.o test.o

%.o : %.c *.h
	${CC} ${CFLAGS} -c $<
	
clean:
	${RM} *.o *.exe