CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    CFLAGS += -DNDEBUG -g0
endif

app.exe : array.o main.o
	${CC} -o $@ $^
	
%.o : %.c
	${CC} ${CFLAGS} -c $<

clean :
	$(RM) *.o *.exe