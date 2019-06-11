CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), release)
	CFLAGS += -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -DNDEBUG -g3
endif

app.exe : matrix.o main.o
	$(CC) $^ -o $@

test.exe : test.o matrix.o
	$(CC) $^ -o $@

%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe