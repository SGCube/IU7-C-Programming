CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic

OBJS := list.o job.o error.o

OBJST := test_list.o

ifeq ($(mode), debug)
    CFLAGS += -g3 -ggdb
endif

ifeq ($(mode), release)
    CFLAGS += -DNDEBUG -g0
endif

app.exe: $(OBJS) main.o
	$(CC) $^ -o $@
	
test.exe: $(OBJS) $(OBJST) test.o
	$(CC) $^ -o $@
	
%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.o *.exe
