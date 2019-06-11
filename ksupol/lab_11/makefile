CC := gcc
CFLAGS := -std=c99 -posix -Wall -Werror -pedantic

ifeq ($(mode), release)
	CFLAGS += -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -DNDEBUG -g3
endif
	
test.exe : pr.o test.o
	$(CC) $^ -o $@
	
%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	$(RM) *.o *.exe