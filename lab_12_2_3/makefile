CC := gcc
CFLAGS := -std=c99 -Wall -Werror -D ARR_EXPORTS
OBJS := arr_lib.o

ifeq ($(mode), debug)
    CFLAGS += -g3 -ggdb
endif

ifeq ($(mode), release)
    CFLAGS += -DNDEBUG -g0
endif

lib: $(OBJS)
	gcc -shared $^ -Wl,--subsystem,windows -o arr.dll
	
%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.o *.exe *.dll