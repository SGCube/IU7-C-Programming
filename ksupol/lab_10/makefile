CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

OBJS := list.o prod.o
ifeq ($(mode), release)
	CFLAGS += -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -DNDEBUG -g3
endif

app.exe : $(OBJS) main.o
	$(CC) $^ -o $@
	
test.exe : $(OBJS) test.o
	$(CC) $^ -o $@
	
%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	$(RM) *.o *.exe