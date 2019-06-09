CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic

OBJ1 := matrix.o

OBJ2 := matrix_2.o

ifeq ($(mode), debug)
    CFLAGS += -g3 -ggdb
endif

ifeq ($(mode), release)
    CFLAGS += -DNDEBUG -g0
endif

app_1: $(OBJ1) main.o
	$(CC) $^ -o app.exe
	
app_2: $(OBJ2) main.o
	$(CC) $^ -o app.exe
	
test_1: $(OBJ1) test.o
	$(CC) $^ -o test.exe
	
test_2: $(OBJ2) test.o
	$(CC) $^ -o test.exe
	
%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.o *.exe