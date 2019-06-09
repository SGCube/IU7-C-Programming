#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fileio.h"

#define OK 0

#define ERR_IFILE1 -1
#define ERR_IFILE2 -2
#define ERR_OFILE -3

#define ERR_FILE -3
#define ERR_EMPTY -10
#define ERR_SIZE -11
#define ERR_NZ_AM -12
#define ERR_NZ_OVER -18
#define ERR_INDEX -13
#define ERR_ELEM -14
#define NOT_ENOUGH_DATA -15
#define ERR_OVERWRITE -16
#define ERR_INPUT_ZERO -17

int file_open(char act, char **argv, FILE **fin1, FILE **fin2, FILE **fout)
{
	assert(act == 'a' || act == 'm' || act == 'o');
	assert(argv);
	
	*fin1 = fopen(argv[2], "r");
	if (!*fin1)
		return ERR_IFILE1;
	
	if (act == 'o')
	{
		*fout = fopen(argv[3], "w");
		if (!*fout)
		{
			//fclose(*fin1);
			return ERR_OFILE;
		}
	}
	else
	{
		*fin2 = fopen(argv[3], "r");
		if (!*fin2)
		{
			//fclose(*fin1);
			return ERR_IFILE2;
		}
		*fout = fopen(argv[4], "w");
		if (!*fout)
		{
			//fclose(*fin1);
			//fclose(*fin2);
			return ERR_OFILE;
		}
	}
	
	return OK;
}

void ioerror_msg(int rc, char *fname)
{
	if (rc == ERR_FILE)
		fprintf(stderr, "Couldn't open %s!\n", fname);
	if (rc == ERR_EMPTY)
		fprintf(stderr, "%s: File is empty!\n", fname);
	if (rc == NOT_ENOUGH_DATA)
		fprintf(stderr, "%s: Not enough data!\n", fname);
	if (rc == ERR_SIZE)
		fprintf(stderr, "%s: Matrix size incorrect input!\n", fname);
	if (rc == ERR_NZ_AM)
		fprintf(stderr, "%s: Non-zero amount incorrect input!\n", fname);
	if (rc == ERR_NZ_OVER)
		fprintf(stderr, "%s: Non-zero amount is larger than matrix size!\n",
			fname);
	if (rc == ERR_INDEX)
		fprintf(stderr, "%s: Element index incorrect input!\n", fname);
	if (rc == ERR_ELEM)
		fprintf(stderr, "%s: Matrix element incorrect input!\n", fname);
	if (rc == ERR_OVERWRITE)
		fprintf(stderr, "%s: Matrix element overwrite!\n", fname);
	if (rc == ERR_INPUT_ZERO)
		fprintf(stderr, "%s: Writing 0 as non-zero element!\n", fname);
}

void fclose_all(FILE *f1, FILE *f2, FILE *f3)
{
	if (f1)
		fclose(f1);
	if (f2)
		fclose(f2);
	if (f3)
		fclose(f3);
}