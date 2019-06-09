#include <stdlib.h>
#include <math.h>
#include "error.h"
#include "matrix.h"

struct matrix_type
{
	item_t *a;
	int ro;
	int co;
};

matrix_t create()
{
	matrix_t ma = malloc(sizeof(struct matrix_type));
	if (!ma)
		return NULL;
	ma->a = NULL;
	ma->ro = 0;
	ma->co = 0;
	return ma;
}

void destroy(matrix_t ma)
{
	if (ma)
	{
		if (ma->a)
			free(ma->a);
		free(ma);
	}
}

int read(matrix_t ma, FILE *f)
{
	if (!f)
		return ERR_FILE;
	int rc = fscanf(f, "%d%d", &(ma->ro), &(ma->co));
	if (rc == EOF)
		return ERR_EMPTY;
	if (rc != 2)
		return ERR_INPUT;
	ma->a = calloc(ma->ro * ma->co, sizeof(item_t));
	if (!ma->a)
		return ERR_MEMORY;
	for (int i = 0; i < ma->ro; i++)
		for (int j = 0; j < ma->co; j++)
		{
			rc = fscanf(f, "%d", &(ma->a[i * ma->co + j]));
			if (rc == EOF)
				return ERR_NDATA;
			if (rc != 1)
				return ERR_INPUT;
		}
	return OK;
}

void print(matrix_t ma)
{
	for (int i = 0; i < ma->ro; i++)
	{
		for (int j = 0; j < ma->co; j++)
			printf("%d ", ma->a[i * ma->co + j]);
		printf("\n");
	}
}

void write(matrix_t ma, FILE *f)
{
	if (!f || !ma->a)
		return;
	fprintf(f, "%d %d\n", ma->ro, ma->co);
	for (int i = 0; i < ma->ro; i++)
	{
		for (int j = 0; j < ma->co; j++)
			fprintf(f, "%d ", ma->a[i * ma->co + j]);
		fprintf(f, "\n");
	}
}

int sum(matrix_t ma1, matrix_t ma2, matrix_t ma)
{
	if (ma1->ro != ma2->ro || ma1->co != ma2->co)
		return ERR_MATCH;
	
	ma->ro = ma1->ro;
	ma->co = ma1->co;
	
	ma->a = calloc(ma->ro * ma->co, sizeof(item_t));
	if (!ma->a)
		return ERR_MEMORY;
	
	for (int i = 0; i < ma->ro; i++)
		for (int j = 0; j < ma->co; j++)
			ma->a[i * ma->co + j] = ma1->a[i * ma1->co + j] +
				ma2->a[i * ma2->co + j];
	return OK;
}

int multiply(matrix_t ma1, matrix_t ma2, matrix_t ma)
{
	if (ma1->co != ma2->ro)
		return ERR_MATCH;
	ma->ro = ma1->ro;
	ma->co = ma2->co;
	
	ma->a = calloc(ma->ro * ma->co, sizeof(item_t));
	if (!ma->a)
		return ERR_MEMORY;
	for (int i = 0; i < ma->ro; i++)
		for (int j = 0; j < ma->co; j++)
			for (int k = 0; k < ma1->co; k++)
				ma->a[i * ma->co + j] += ma1->a[i * ma1->co + k] *
					ma2->a[k * ma2->co + j];
	return OK;
}

int compare(matrix_t ma1, matrix_t ma2)
{
	if (!ma1 || !ma2)
		return -1;
	if (!ma1->a || !ma2->a)
		return -1;
	if (ma1->ro != ma2->ro || ma1->co != ma2->co)
		return -1;
	for (int i = 0; i < ma1->ro; i++)
		for (int j = 0; j < ma1->co; j++)
			if (ma1->a[i * ma1->co + j] != ma2->a[i * ma2->co + j])
				return 0;
	return 1;
}
