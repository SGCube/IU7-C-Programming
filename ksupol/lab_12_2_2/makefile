CC := gcc
CFLAGS := -std=c99 -Wall -Werror

ifeq ($(mode), release)
	$(CFLAGS) += -g0
endif

ifeq ($(mode), debug)
	$(CFLAGS) += -g3 -DNDEBUG
endif

lib_dyn : array.o
	$(CC) -shared $^ -Wl,--subsystem,windows -o arr.dll
	
%.o : %.c *.h
	$(CC) $(CFLAGS) -D ARR_EXPORTS -c $< 
	
clean :
	$(RM) *.o *.exe *.dll	