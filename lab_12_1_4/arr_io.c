#include <stdio.h>
#include "error.h"
#include "arr_io.h"

FN_TYPE(int) array_len(FILE *f)
{
	if (!f)
		return ERR_FILE;
	int sc, num, n = 0;
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
	return n;
}

FN_TYPE(int) read_array(FILE *f, int *pb, int **pe, int n)
{
	if (!f)
		return ERR_FILE;
	if (!pb)
		return ERR_MEMORY;
	*pe = pb;
	for (*pe = pb; *pe < pb + n; *pe += 1)
		fscanf(f, "%d", *pe);
	return OK;
}

FN_TYPE(int) print_array(FILE *f, const int *pb, const int *pe)
{
	if (!f)
		return ERR_FILE;
	if (!pb || !pe)
		return ERR_MEMORY;
	if (pb >= pe)
		return ERR_MEMORY;
	for (const int *pc = pb; pc < pe; pc++)
		if (fprintf(f, "%d ", *pc) < 0)
			return ERR_OUTPUT;
	return OK;
}