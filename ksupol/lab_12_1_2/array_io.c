#include <stdio.h>
#include <stdlib.h>
#include "array_io.h"

#define OK 0
#define NO_OUTPUT -2
#define ERR_MALLOC -3
#define EMPTY_FILE -4
#define WRONG_ELEMENT -5
#define ERR_PRINT -6

TYPE(int) readarr(FILE *f, int **pa, int **pb)
{
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

TYPE(int) printarr(FILE *f, const int *pa, const int *pb)
{
	const int *pc = pa;

	for (pc = pa; pc < pb; pc++)
		if (fprintf(f, "%d ", *pc) < 0)
			return ERR_PRINT;
	return OK;
}