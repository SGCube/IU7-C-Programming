CC := gcc

CFLAGS := -std=c99 -Wall -Werror
LINKFLAGS := -L. -larr -o

CFILES := arr_io.c arr_sort.c
OBJS := arr_io.o arr_sort.o
LIB := libarr.a

ifeq ($(mode), debug)
    CFLAGS += -g3 -ggdb
endif

ifeq ($(mode), release)
    CFLAGS += -DNDEBUG -g0
endif

app_stat: main.o
	$(CC) main.o $(LINKFLAGS) app.exe
	
app_dyn1: main.c
	$(CC) $(CFLAGS) -D DLL_BUILD -c $<
	$(CC) main.o $(LINKFLAGS) app.exe
	
app_dyn2: main_2.o
	$(CC) $^ -o app.exe
	
test.exe: test.c
	$(CC) $(CFLAGS) -D DLL_BUILD -c $<
	$(CC) test.o $(LINKFLAGS) $@
	
statlib: $(OBJS)
	ar rc $(LIB) $^
	ranlib $(LIB)

dynlib:
	gcc -std=c99 -Wall -Werror -D DLL_BUILD -D ARR_EXPORTS -c $(CFILES)
	gcc -shared $(OBJS) -Wl,--subsystem,windows -o arr.dll
	
%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.o *.exe *.a *.dll