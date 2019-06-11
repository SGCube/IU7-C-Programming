#ifndef __PR_H__
#define __PR_H__
int my_snprintf(char *restrict s, size_t n,
	const char *restrict format, ...);
char *from_num_to_str(int num, char *s, int len, int n);
#endif