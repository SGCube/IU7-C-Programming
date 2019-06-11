CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    CFLAGS += -DNDEBUG -g0
endif

app.exe : array.o process.o main.o
	$(CC) $^ -o $@

test.exe : array.o process.o test.o
	$(CC) $^ -o $@
	
%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe