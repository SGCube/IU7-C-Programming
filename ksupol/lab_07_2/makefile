CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic 

OBJ := array.o
 
ifeq ($(mode), debug)
	CFLAGS += -g3 -ggdb
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

app.exe : $(OBJ) main.o
	$(CC) $^ -o $@

test.exe : $(OBJ) test.o
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe