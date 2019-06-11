#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "str.h"

#define MAX_LEN 128
#define OK 0
#define ERR -1
#define ERR_FILE -2
#define ERR_MAL -3
#define ERR_G -4

size_t my_getline(char **line, int *n, FILE *f)
{
	if (!f || !n || !line)
		return ERR;
	int len = 0;
	char buffer[MAX_LEN];
	int end_line = 0;
	char *point = NULL;
	char *t;
	
	do
	{
		end_line = 0;
		if (fgets(buffer, MAX_LEN, f) == NULL)
			return ERR;
		if (my_strlen(buffer) + 1 > *n)
		{
			t = realloc(*line, (len + MAX_LEN) * sizeof(char));
			if (!t)
				return ERR;
			*line = t;
			*n = len + MAX_LEN;
		}
		point = *line + len;
		len += my_strlen(buffer);
		for (char *pc = buffer; *pc != '\0'; pc++, point++)
		{
			if (*pc == '\n')
				end_line = 1;
			*point = *pc;
		}
	}
	while (!feof(f) && !end_line);
	
	if (len == 0)
		return ERR;
	(*line)[len] = '\0';
	
	*n = len + 1;
	return len * sizeof(char);
}

char *str_replace(const char *source, const char *search, const char *replace)
{
	if (source == NULL || search == NULL || replace == NULL)
		return NULL;
	int len1 = my_strlen(source);
	int len2 = my_strlen(search);
	int len3 = my_strlen(replace);
	const char *start = source, *end = source;
	int len = 0;
	char *t = NULL;
	char *result;
	int len_cur = 0;
	int k = 0, i = 0;
	result = malloc(len1 + 1);
	if (!result)
		return NULL;
	while (i < len1)
	{
		len = 0;
		for (int j = 0; j < len2 && (i + j) < len1; j++)
		{
			if (source[i + j] == search[j])
				len++;
			else
			{
				len = 0;
				break;
			}
		}
		if (len == len2)
		{
			end = source + i;
			len_cur += len3 + end - start;
			t = (char *)realloc(result, (len_cur + 1) * sizeof(char));
			if (!t)
				return NULL;
			result = t;
			for (const char *pc = start; pc < end; pc++, k++)
				result[k] = *pc;
			for (int c = 0; c < len3; c++, k++)
				result[k] = replace[c];
			end += len2;
			start = end;
			i += len2;
		}
		else
			i++;
	}
	end = source + len1;
	if (start != end)
	{
		len_cur += end - start;
		t = (char *)realloc(result, (len_cur + 1) * sizeof(char));
		if (!t)
			return NULL;
		result = t;
		for (const char *pc = start; pc < end; pc++, k++)
			result[k] = *pc;
	}
	result[len_cur] = '\0';

	return result;
}

int my_strlen(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

int my_strcmp(char *s1, char *s2)
{
    int len1, len2, i, min;
    int compare = 0;
    min = len1 = my_strlen(s1);
    len2 = my_strlen(s2);
    if (len2 < min)
    {
        min = len2;
    }
    for (i = 0; i <= min; i++)
    {
        compare = s1[i] - s2[i];
        if (compare != 0)
            return compare;
    }
    return 0;
}
