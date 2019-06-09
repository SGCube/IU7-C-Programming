/**
 * \file iofile.h
 * \brief File I/O function headers
 * \details Code contains input/output array from/into file functions headers
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "iofile.h"

#define OK 0
#define ERR_EMPTY -3
#define ERR_INPUT -4
#define ERR_OUTPUT -5
#define ERR_MEMORY -6

int read_array(FILE *f, int **pb, int **pe)
{
	assert(f);
	int sc = 1;
	int num, n = 0;
	do
	{
		sc = fscanf(f, "%d", &num);
		if (sc == EOF)
		{
			if (n == 0)
				return ERR_EMPTY;
		}
		else if (sc != 1)
			return ERR_INPUT;
		else
			n++;
	}
	while (sc != EOF);
	rewind(f);
	*pb = malloc(n * sizeof(int));
	if (!pb)
		return ERR_MEMORY;
	*pe = *pb;
	for (*pe = *pb; *pe < *pb + n; *pe += 1)
		fscanf(f, "%d", *pe);
	return OK;
}

int print_array(FILE *f, const int *pb, const int *pe)
{
	assert(f);
	assert(pb && pe);
	assert(pb < pe);
	for (const int *pc = pb; pc < pe; pc++)
		if (fprintf(f, "%d ", *pc) < 0)
			return ERR_OUTPUT;
	return OK;
}