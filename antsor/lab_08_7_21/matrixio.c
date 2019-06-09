#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "matrixio.h"

#define OK 0

#define ERR_EMPTY -10
#define ERR_SIZE -11
#define ERR_NZ_AM -12
#define ERR_NZ_OVER -18
#define ERR_INDEX -13
#define ERR_ELEM -14
#define NOT_ENOUGH_DATA -15
#define ERR_OVERWRITE -16
#define ERR_INPUT_ZERO -17

#define EPS 1e-12

int read_matrix_size(FILE *f, int *n, int *m)
{
	assert(f);
	
	int sc = fscanf(f, "%d", n);
	if (sc == EOF)
		return ERR_EMPTY;
	if (sc != 1)
		return ERR_SIZE;
	
	sc = fscanf(f, "%d", m);
	if (sc == EOF)
		return NOT_ENOUGH_DATA;
	if (sc != 1)
		return ERR_SIZE;
	
	if (*n <= 0 || *m <= 0)
		return ERR_SIZE;
	
	return OK;
}

double **alloc_matrix(int n, int m)
{
	assert(n > 0 && m > 0);
	
	double **ma = malloc(n * sizeof(double*) + n * m * sizeof(double));
	if (!ma)
		return NULL;
	
	for (int i = 0; i < n; i++)
		ma[i] = (double*)((char*) ma + n * sizeof(double*) +
			i * m * sizeof(double));
					
	return ma;
}

void init_matrix(double **ma, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ma[i][j] = 0;
}

void ident_matrix(double **ma, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				ma[i][j] = 1;
			else
				ma[i][j] = 0;
		}
}

int read_matrix(FILE *f, double **ma, int n, int m)
{
	assert(f);
	assert(ma);
	assert(n > 0 && m > 0);
	
	int ro, i, j;
	double x;
	int sc = fscanf(f, "%d", &ro);
	if (sc == EOF)
		return NOT_ENOUGH_DATA;
	if (sc != 1 || ro < 0)
		return ERR_NZ_AM;
	if (ro > n * m)
		return ERR_NZ_OVER;
	
	init_matrix(ma, n, m);
	
	for (int k = 0; k < ro; k++)
	{
		sc = fscanf(f, "%d%d", &i, &j); 
		if (sc == EOF)
			return NOT_ENOUGH_DATA;
		if (sc != 2)
			return ERR_INDEX;
		if (i <= 0 || i > n || j <= 0 || j > m)
			return ERR_INDEX;
		
		if (fabs(ma[i - 1][j - 1]) > EPS)
			return ERR_OVERWRITE;
		
		sc = fscanf(f, "%lf", &x);
		if (sc == EOF)
			return NOT_ENOUGH_DATA;
		if (sc != 1)
			return ERR_ELEM;
		if (x == 0)
			return ERR_INPUT_ZERO;
		ma[i - 1][j - 1] = x;
	}
	return OK;
}

void print_matrix(FILE *f, double **ma, int n, int m)
{
	fprintf(f, "%d %d\n", n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			fprintf(f, "%lf ", ma[i][j]);
		fprintf(f, "\n");
	}
}