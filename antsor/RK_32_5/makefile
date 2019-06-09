CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
OBJS := list.o stud.o

ifeq ($(mode), debug)
	CFLAGS += -g3
endif
	
app.exe: $(OBJS) main.o
	$(CC) $^ -o $@
	
test.exe: $(OBJS) test.o
	$(CC) $^ -o $@
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.o *.exe