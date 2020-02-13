CC := gcc

CFLAGS := -std=c99 -posix -Wall -Werror -pedantic

OBJS := mystdio.o

ifeq ($(mode), debug)
    CFLAGS += -g3 -ggdb
endif

ifeq ($(mode), release)
    CFLAGS += -DNDEBUG -g0
endif
	
test.exe: $(OBJS) test.o
	$(CC) $^ -o $@
	
%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.o *.exe