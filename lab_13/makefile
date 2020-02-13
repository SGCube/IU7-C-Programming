CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
OBJS := gshow_f.o list_u.o filter.o sort.o

ifeq ($(mode), release)
	CFLAGS += -g0 -DNDEBUG
endif

ifeq ($(mode), debug)
	CFLAGS += -ggdb -g3
endif

app.exe : $(OBJS) main.o
	$(CC) $^ -o $@

test.exe : $(OBJS) test_sort.o test.o
	$(CC) $^ -o $@
	
ftests : app.exe
	chmod a+rx test_err.sh
	chmod a+rx test.sh
	./test.sh

%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe