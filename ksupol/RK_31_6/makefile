CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), release)
	CFLAGS += -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -DNDEBUG -g3
endif

app.exe : str.o main.o
	$(CC) $^ -o $@
	
test.exe : str.o test.o
	$(CC) $^ -o $@
	
%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	$(RM) *.o *.exe