#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mystdio.h"

void stos(char *s, char **ptrs, int *len, size_t n, char *src)
{
	char *ptr = src;
	while (*ptr)
	{
		if (s && *ptrs - s < n - 1)
		{
			**ptrs = *ptr;
			*ptrs += 1;
		}
		*len += 1;
		ptr++;
	}
}

void lldtos(char *s, char **ptrs, int *len, size_t n, long long number)
{
	char digits[20];
	char *ptrd = digits;
	
	if (number == 0)
	{
		if (s && *ptrs - s < n - 1)
		{
			**ptrs = '0';
			*ptrs += 1;
		}
		*len += 1;
		return;
	}
	
	if (number < 0)
	{
		if (s && *ptrs - s < n - 1)
		{
			**ptrs = '-';
			*ptrs += 1;
		}
		*len += 1;
	}
	while (number != 0)
	{
		long long d = number % 10;
		*ptrd++ = '0' + abs((int)d);
		number /= 10;
	}
	ptrd--;
	while (ptrd >= digits)
	{
		if (s && *ptrs - s < n - 1)
		{
			**ptrs = *ptrd--;
			*ptrs += 1;
		}
		*len += 1;
	}
}

int my_snprintf(char *restrict s, size_t n,
	const char *restrict format, ...)
{
	if (n < 0)
		return -1;
	if (!s && n != 0)
		return -1;
	if (!format || !*format)
		return -1;
	
	int len = 0;
	char *ptrs = s;
	const char *ptrf = format;
	va_list arg;
	va_start(arg, format);
	
	while (*ptrf)
	{
		if (*ptrf != '%')
		{
			if (s && ptrs - s < n - 1)
				*ptrs++ = *ptrf;
			len++;
		}
		else
		{
			ptrf++;
			if (*ptrf == '%')
			{
				if (s && ptrs - s < n - 1)
					*ptrs++ = *ptrf;
				len++;
			}
			else if (*ptrf == 'l')
			{
				ptrf++;
				if (*ptrf != 'l')
					return -1;
				ptrf++;
				if (*ptrf != 'd')
					return -1;
				
				long long number = va_arg(arg, long long);
				lldtos(s, &ptrs, &len, n, number);
			}
			else if (*ptrf == 's')
			{
				char *ptr = va_arg(arg, char *);
				if (!ptr)
					return -1;
				stos(s, &ptrs, &len, n, ptr);
			}
			else if (*ptrf)
				return -1;
		}
		if (*ptrf)
			ptrf++;
	}
	if (n != 0 && s)
		*ptrs = '\0';
	va_end(arg);
	return len;
}