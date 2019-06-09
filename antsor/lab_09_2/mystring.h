#ifndef __MYSTRING_H__
#define __MYSTRING_H__
#include <unistd.h>

int my_strlen(const char *s);
int my_strcmp(const char *s1, const char *s2);
int my_strcmpn(const char *s1, const char *s2, int n);
char *my_strcat_s(char *dst, size_t dstsz, const char *src);
char *str_replace(const char *source, const char *search,
	const char *replace);
ssize_t my_getline(char **lineptr, ssize_t *n, FILE *stream);

#endif