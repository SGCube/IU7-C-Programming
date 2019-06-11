#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#define OK 0
#define NOTHING_AFTER_F -8

TYPE(int) cmpint(const void *pa, const void *pb)
{
	const int *p1 = (int *)pa;
	const int *p2 = (int *)pb;
	return *p1 - *p2;
}

TYPE(int) cmpchar(const void *pa, const void *pb)
{
	const char *p1 = (char *)pa;
	const char *p2 = (char *)pb;
	return *p1 - *p2;
}

TYPE(int) cmpfloat(const void *pa, const void *pb)
{
	const float *p1 = (float *)pa;
	const float *p2 = (float *)pb;
	if (*p1 - *p2 > 0)
		return 1;
	if (*p1 - *p2 < 0)
		return -1;
	return 0;
}

TYPE(void) movarr(char *pbeg, char *pend, size_t size)
{
	for (size_t byte = 0; byte < size; byte++)
	{
		char tmp = *(pend + byte);
		for (char *pv = pend + byte; pv > pbeg + byte; pv -= size)
			*pv = *(pv - size);
		*(pbeg + byte) = tmp;
	}
}

TYPE(void) mysort(void *base, size_t nmemb, size_t size,
	int (*compar)(const void *, const void *))
{
	char *pb = (char *) base;
	char *pc;
	for (pc = pb + size; pc < pb + size * nmemb; pc += size)
	{
		char *pg = pb;
		while (compar(pg, pc) < 0 && pg < pc)
			pg += size;
		if (pg < pc)
			movarr(pg, pc, size);
	}
}


TYPE(int) calc_amount(const int *pa, const int *pb)
{
	const int *pc = pa;
	int am = 0;
	
	while (pc < pb && *pc >= 0) 
	{
		am++;
		pc++;
	}
	if (am == 0)
		return NOTHING_AFTER_F;
	return am;
}

TYPE(int) key(const int *pa, const int *pb, int *pa_new, int **pb_new, int am)
{
	if (pa == NULL || pb == NULL)
		return 3;
	if (pa >= pb)
		return 4;
	for (*pb_new = pa_new; *pb_new < pa_new + am; *pb_new += 1)
		**pb_new = *pa++;
	return OK;
}