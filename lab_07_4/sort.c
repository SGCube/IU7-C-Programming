#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"

#define OK 0
#define ERR_MEMORY -6
#define NONE_TO_SORT -7
#define ERR_ARG -9

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
	/*UNIT TESTING fails due to assert
	assert(pb_src && pe_src);
	assert(pb_src < pe_src);
	*/
	if (!pb_src || !pe_src || pb_src >= pe_src)
		return ERR_ARG;
	
	int n = 0, sum = 0;
	float avg;
	
	for (const int *pc = pb_src; pc < pe_src; pc++)
		sum += *pc;
	avg = (float) sum / (pe_src - pb_src);
	
	for (const int *pc = pb_src; pc < pe_src; pc++)
		if (*pc > avg)
			n++;
	if (n == 0)
		return NONE_TO_SORT;
	
	*pb_dst = calloc(n, n * sizeof(int));
	if (!*pb_dst)
		return ERR_MEMORY;
	
	*pe_dst = *pb_dst;
	for (const int *pc = pb_src; pc < pe_src; pc++)
		if (*pc > avg)
		{
			**pe_dst = *pc;
			*pe_dst += 1;
		}
	return OK;
}

int compar_int(const void *pa, const void *pb)
{
	/*UNIT TESTING fails due to assert
	assert(pa && pb);
	*/
	const int *p1 = (int*) pa;
	const int *p2 = (int*) pb;
	return *p1 - *p2;
}

int compar_float(const void *pa, const void *pb)
{
	/*UNIT TESTING fails due to assert
	assert(pa && pb);
	*/
	const float *p1 = (float*) pa;
	const float *p2 = (float*) pb;
	if (*p1 - *p2 > 0)
		return 1;
	if (*p1 - *p2 < 0)
		return -1;
	return 0;
}

int compar_char(const void *pa, const void *pb)
{
	/*UNIT TESTING fails due to assert
	assert(pa && pb);
	*/
	const char *p1 = (char*) pa;
	const char *p2 = (char*) pb;
	return *p1 - *p2;
}

int shift(char *pb, char *pe, size_t size)
{
	/*UNIT TESTING fails due to assert
	assert(pb && pe);
	assert(pb < pe);
	assert(size > 0);
	*/
	if (!pb || !pe || pb >= pe || size <= 0)
		return ERR_ARG;
	
	char *pc;
	char tmp;
	for (size_t byte = 0; byte < size; byte++)
	{
		pc = pe - size + byte;
		tmp = *pc;
		while (pc > pb + byte)
		{
			*pc = *(pc - size);
			pc -= size;
		}
		*(pb + byte) = tmp;
	}
	return OK;
}

int mysort(void *base, size_t nmemb, size_t size,
	int (*compar)(const void*, const void*))
{
	/*UNIT TESTING fails due to assert
	assert(base);
	assert(nmemb > 0);
	assert(size > 0);
	assert(compar);
	*/
	
	if (!base || !compar || nmemb <= 0 || size <= 0)
		return ERR_ARG;
	
	char *pb = (char *) base;
	char *pe = pb + nmemb * size;
	char *pi, *pj;
	for (pi = pb + size; pi < pe; pi += size)
	{
		pj = pi - size;
		while (pj >= pb && compar(pj, pi) > 0)
			pj -= size;
		shift(pj + size, pi + size, size);
	}
	return OK;
}