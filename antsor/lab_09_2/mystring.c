#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mystring.h"
#include "errcode.h"

int my_strlen(const char *s)
{
	if (!s)
		return -1;
	int len = 0;
	while (s[len] != '\0')
		len++;
	return len;
}

int my_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return -1;
	const char *ptr1 = s1, *ptr2 = s2;
	while (*ptr1 != 0 || *ptr2 != 0)
	{
		if (*ptr1 != *ptr2)
			return *ptr1 - *ptr2;
		ptr1++;
		ptr2++;
	}
	return 0;
}

int my_strcmpn(const char *s1, const char *s2, int n)
{
	if (!s1 || !s2)
		return -1;
	const char *ptr1 = s1, *ptr2 = s2;
	int i = 0;
	while ((*ptr1 != 0 || *ptr2 != 0) && i < n)
	{
		if (*ptr1 != *ptr2)
			return *ptr1 - *ptr2;
		ptr1++;
		ptr2++;
		i++;
	}
	return 0;
}

char *my_strcat_s(char *dst, size_t dstsz, const char *src)
{
	if (!dst || dstsz < 0 || !src)
		return NULL;
	int i = my_strlen(dst), k;
	const char *psrc;
	for (k = 0, psrc = src; k < dstsz && *src != '\0'; k++, psrc++)
		dst[i + k] = *psrc;
	dst[i + k] = '\0';
	return dst;
}

char *str_replace(const char *source, const char *search,
	const char *replace)
{
	if (!source || !search || !replace)
		return NULL;
	int src_len = my_strlen(source);
	int search_len = my_strlen(search);
	int replace_len = my_strlen(replace);
	int dst_len = 0;
	if (search_len != 0)
		dst_len = src_len / search_len * replace_len + src_len % search_len;
	if (src_len > dst_len)
		dst_len = src_len;
	
	char *dst = malloc((dst_len + 1) * sizeof(char));
	if (!dst)
		return NULL;
	
	const char *ptr = source;
	dst[0] = '\0';
	
	while (*ptr != '\0' && ptr <= source + src_len)
	{
		if (my_strcmpn(ptr, search, search_len) == 0)
		{
			my_strcat_s(dst, replace_len, replace);
			ptr += search_len;
		}
		else
		{
			my_strcat_s(dst, 1, ptr);
			ptr++;	
		}
	}
	
	return dst;
}

ssize_t my_getline(char **lineptr, ssize_t *n, FILE *stream)
{
	if (stream == NULL || lineptr == NULL || n == NULL)
		return -1;
	if (*n == 0 || *lineptr == NULL)
	{
		*lineptr = malloc(MEMORY_BLOCK * sizeof(char));
		*n = MEMORY_BLOCK;
	}
	
	ssize_t len = 0;
	char buff[MEMORY_BLOCK];
	char *ptr = *lineptr;
	char *t;
	ssize_t buff_len = 0;

	do
	{
		if (fgets(buff, MEMORY_BLOCK, stream) == NULL)
			return -1;
		buff_len = my_strlen(buff);
		if (len + buff_len + 1 > *n)
		{
			t = (char *)realloc(*lineptr,
				(len + MEMORY_BLOCK) * sizeof(char));
			if (!t)
				return -1;
			*lineptr = t;
			*n = len + MEMORY_BLOCK;
		}
		ptr = *lineptr + len;
		len += buff_len;
		for (const char *pc = buff; *pc != '\0'; pc++, ptr++)
			*ptr = *pc;
	}
	while (!feof(stream) && buff[buff_len - 1] != '\n');
	
	if (len == 0)
		return -1;
	(*lineptr)[len] = '\0';
	*n = len + 1;
	return len;
}