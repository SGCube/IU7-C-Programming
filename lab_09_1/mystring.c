#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

size_t my_strspn(const char *str1, const char *str2)
{
	const char *pc1 = str1, *pc2 = str2;
	size_t size = 0;
	
	while (*pc1 != 0 && *pc2 != 0)
	{
		if (*pc2 == *pc1)
		{
			pc2 = str2;
			pc1++;
			size++;
		}
		else
			pc2++;
	}
	
	return size;
}

char *my_strrchr(const char *str, int symb)
{
	const char *ptr = NULL;
	char ch = (char) symb;
	do
	{
		if (*str == ch)
			ptr = str;
	}
	while (*(str++) != '\0');
	return (char *)ptr;
}