#include <stdio.h>
#include "error.h"
#include "arr_sort.h"

FN_TYPE(int) arr_avg(const int *pb_src, const int *pe_src,
	float *avg)
{
	if (!pb_src || !pe_src || pb_src >= pe_src)
		return ERR_ARG;
	
	int sum = 0, n = 0;
	
	for (const int *pc = pb_src; pc < pe_src; pc++)
		sum += *pc;
	*avg = (float) sum / (pe_src - pb_src);
	
	for (const int *pc = pb_src; pc < pe_src; pc++)
		if (*pc > *avg)
			n++;
	return n;
}

FN_TYPE(int) key(const int *pb_src, const int *pe_src,
	int *pb_dst, int **pe_dst, float avg)
{
	if (!pb_src || !pe_src || pb_src >= pe_src || !pb_dst)
		return ERR_ARG;
	
	*pe_dst = pb_dst;
	for (const int *pc = pb_src; pc < pe_src; pc++)
		if (*pc > avg)
		{
			**pe_dst = *pc;
			*pe_dst += 1;
		}
	return OK;
}

FN_TYPE(int) compar_int(const void *pa, const void *pb)
{
	const int *p1 = (int*) pa;
	const int *p2 = (int*) pb;
	return *p1 - *p2;
}

FN_TYPE(int) compar_float(const void *pa, const void *pb)
{
	const float *p1 = (float*) pa;
	const float *p2 = (float*) pb;
	if (*p1 - *p2 > 0)
		return 1;
	if (*p1 - *p2 < 0)
		return -1;
	return 0;
}

FN_TYPE(int) compar_char(const void *pa, const void *pb)
{
	const char *p1 = (char*) pa;
	const char *p2 = (char*) pb;
	return *p1 - *p2;
}

FN_TYPE(int) shift(char *pb, char *pe, size_t size)
{
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

FN_TYPE(void) mysort(void *base, size_t nmemb, size_t size,
	int (*compar)(const void*, const void*))
{
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
}