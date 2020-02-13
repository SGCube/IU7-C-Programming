CC := gcc

CCFLAGS := -std=c99 -Wall -Werror -pedantic

OBJECTS := array.o

app.exe: ${OBJECTS} main.o
	${CC} -o $@ $^

test.exe: ${OBJECTS} test.o
	${CC} -o $@ $^
	
%.o: %.c *.h
	${CC} ${CCFLAGS} -c $<
	
clean: 
	${RM} *.o *.exe