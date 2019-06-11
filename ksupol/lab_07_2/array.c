#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include <assert.h>
#include <string.h>

#define OK 0
#define NO_OUTPUT -2
#define ERR_MALLOC -3
#define EMPTY_FILE -4
#define WRONG_ELEMENT -5
#define ERR_PRINT -6
#define NOTHING_AFTER_F -8


int readarr(FILE *f, int **pa, int **pb)
{
	assert(f);
	int rc;
	int num;
	int am = 0;
	
	do 
	{
		rc = fscanf(f, "%d", &num);
		if (rc == EOF)
		{
			if (am == 0)
				return EMPTY_FILE;
		}
		else if (rc == 1)
			am++;
		else
			return WRONG_ELEMENT;
	}
	while (rc != EOF);
	rewind(f);
	
	*pa = calloc(am, am * sizeof(int)); // адрес начала массива
	*pb = *pa; // адрес конца массива
	if (!pa)
		return ERR_MALLOC;
	
	for (*pb = *pa; *pb < *pa + am; *pb += 1)
		fscanf(f, "%d", *pb);
	
	return OK;
}


int printarr(FILE *f, const int *pa, const int *pb)
{
	assert(f);
	assert(pa && pb);
	assert(pa < pb);
	
	const int *pc = pa;

	for (pc = pa; pc < pb; pc++)
		if (fprintf(f, "%d ", *pc) < 0)
			return ERR_PRINT;
	return OK;
}

int key(const int *pa, const int *pb, int **pa_new, int **pb_new)
{
	/*
	assert(pa && pb);
	assert(pa < pb);
	*/
	if (pa == NULL || pb == NULL)
		return 3;
	if (pa >= pb)
		return 4;
	
	const int *pc = pa;
	int am = 0;
	
	while (pc < pb && *pc >= 0) 
	{
		am++;
		pc++;
	}
	if (am == 0)
		return NOTHING_AFTER_F;
	*pa_new = calloc(am, am * sizeof(int));
	if (!*pa_new)
		return ERR_MALLOC;
	for (*pb_new = *pa_new; *pb_new < *pa_new + am; *pb_new += 1)
		**pb_new = *pa++;
	return OK;
}

int cmpint(const void *pa, const void *pb)
{
	/*
	assert(pa && pb);
	*/
	
	const int *p1 = (int *)pa;
	const int *p2 = (int *)pb;
	return *p1 - *p2;
}

int cmpchar(const void *pa, const void *pb)
{
	/*
	assert(pa && pb);
	*/
	const char *p1 = (char *)pa;
	const char *p2 = (char *)pb;
	return *p1 - *p2;
}

int cmpfloat(const void *pa, const void *pb)
{
	/*
	assert(pa && pb);
	*/
	const float *p1 = (float *)pa;
	const float *p2 = (float *)pb;
	if (*p1 - *p2 > 0)
		return 1;
	if (*p1 - *p2 < 0)
		return -1;
	return 0;
}

void movarr(char *pbeg, char *pend, size_t size)
{
	/*
	assert(pbeg && pend);
	assert(pbeg < pend);
	assert(size > 0);
	*/
	
	for (size_t byte = 0; byte < size; byte++)
	{
		char tmp = *(pend + byte);
		for (char *pv = pend + byte; pv > pbeg + byte; pv -= size)
			*pv = *(pv - size);
		*(pbeg + byte) = tmp;
	}
}

void mysort(void *base, size_t nmemb, size_t size,
	int (*compar)(const void *, const void *))
{
	/*
	assert(base);
	assert(nmemb > 0);
	assert(size > 0);
	assert(compar);
	*/
	
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