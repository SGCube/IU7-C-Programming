CC := gcc
CFLAGS := -std=c99 -Wall -Werror
OBJ := array_io.o array.o
CFILES := array_io.c array.c

ifeq ($(mode), release)
	$(CFLAGS) += -g0
endif

ifeq ($(mode), debug)
	$(CFLAGS) += -g3 -DNDEBUG
endif

app_1.exe : main.o
	$(CC) $^ -L. -larr -o app_1.exe
	
app_2.exe : main.c
	$(CC) $(CFLAGS) -D T -c $<
	$(CC) $^ -L. -larr -o app_2.exe
	
app_3.exe : main_2.o
	$(CC) $^ -o app_3.exe

test : test.o
	$(CC) $^ -L. -larr -o test.exe

lib_stat : $(OBJ)
	ar rc libarr.a $^
	ranlib libarr.a

lib_dyn : $(CFILES)
	$(CC) $(CFLAGS) -D T -D ARR_EXPORTS -c $^
	$(CC) -shared $(OBJ) -Wl,--subsystem,windows -o arr.dll
	
%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<
	
clean :
	$(RM) *.o *.exe *.a *.dll
	