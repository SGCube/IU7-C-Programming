#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define ERR -1

void from_num_to_str(short int num, char *s, int *len, int n)
{
	char str[6];
	int i = 0;
	if (num < 0)
	{
		if (s != NULL && n - 1 > *len)
			s[*len] = '-';
		*len += 1;
	}
	num = abs(num);
	while (num > 0)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	for (int j = i - 1; j >= 0; j--)
	{
		if (s != NULL && n - 1 > *len)
			s[*len] = str[j];
		*len += 1;
	}
}

int my_snprintf(char *restrict s, size_t n,
       const char *restrict format, ...)
{
	if (s == NULL && n != 0)
		return ERR;
	if (n < 0)
		return ERR;
	if (format == NULL)
		return ERR;
	int len = 0;
	va_list vl;
	va_start(vl, format);
	const char *ptr = format;
	if (*ptr == '\0')
		return ERR;
	while (*ptr != '\0')
	{
		if (*ptr != '%')
		{
			if (s != NULL && n - 1 > len)
				s[len] = *ptr;
			len++;
		}
		else
		{
			ptr++;
			if (*ptr != 's' && *ptr != 'h')
				return ERR;
			if (*ptr == 's')
			{
				char *str = va_arg(vl, char *);
				if (!str)
					return ERR;
				char *ch = str;
				while (*ch != '\0')
				{
					if (s != NULL && n - 1 > len)
						s[len] = *ch;
					ch++;
					len++;
				}
			}
			else if (*ptr == 'h')
			{
				ptr++;
				if (*ptr != 'd')
					return ERR;
				short int num = va_arg(vl, int);
				from_num_to_str(num, s, &len, n);
			}
		}
		ptr++;
	}
	va_end(vl);
	if (s != NULL && n - 1 > len)
		s[len] = '\0';
	else if (s != NULL && n - 1 <= len)
		s[n - 1] = '\0';
	return len;
}