#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"

#define OK 0
#define INF -1
#define ERR_NOT_ENOUGH -2
#define ERR_I -3
#define ERR_FILE -4
#define EMPTY -5
#define ERR_STR -6
#define NO_COL -7
#define ERR_COL -8
#define ERR -9
#define ERR_MALLOC -10
#define ERR_ELEM -11
#define NO_ELEM -12
#define NOT_ENOUGH_ELEM -13

int file_work(int argc, char **argv, FILE **f1, FILE **f2, FILE **f3)
{
	assert(argc > 3);
	assert(argv);
	
	if (argc == 5)
	{
		*f1 = fopen(argv[2], "r");
		if (*f1 == NULL)
			return ERR_FILE;
		*f2 = fopen(argv[3], "r");
		if (*f2 == NULL)
		{
			fclose(*f1);
			return ERR_FILE;
		}
		*f3 = fopen(argv[4], "w");
		if (*f3 == NULL)
		{
			fclose(*f1);
			fclose(*f2);
			return ERR_FILE;
		}
	}
	if (argc == 4)
	{
		*f1 = fopen(argv[2], "r");
		if (*f1 == NULL)
			return ERR_FILE;
		*f2 = fopen(argv[3], "w");
		if (*f2 == NULL)
		{
			fclose(*f1);
			return ERR_FILE;
		}
	}
	return OK;
}

int read_str_col(FILE *f, int *n, int *m)
{
	assert(f);
	assert(n && m);
	
	int rc = 0;
	rc = fscanf(f, "%d", n);
	if (rc == EOF)
		return EMPTY;
	if (rc != 1 || *n < 1)
		return ERR_STR;
	rc = fscanf(f, "%d", m);
	if (rc == EOF)
		return NO_COL;
	if (rc != 1 || *m < 1)
		return ERR_COL;
	return OK;
}

void free_matrix(double **matrix)
{
	assert(matrix);
	
    free(matrix[0]);
    free(matrix);
}

double **allocate_matrix(int n, int m)
{
	assert(n > 0 && m > 0);
	
	double **matrix, *data;
	matrix = malloc(n * sizeof(double*));
	if (!matrix)
		return NULL;
	data = malloc(n * m * sizeof(double));
	if (!data)
	{
		free(matrix);
		return NULL;
	}
	for (int i = 0; i < n; i++)
		matrix[i] = data + i * m;
	return matrix;
}

int read_matrix(FILE *f, double ***matrix, int n, int m)
{
	assert(f);
	assert(matrix);
	assert(n > 0 && m > 0);
	
	int rc = 0;
	int flag = 0;
	
	*matrix = allocate_matrix(n, m);
	if (!*matrix)
		return ERR_MALLOC;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			rc = fscanf(f, "%lf", &(*matrix)[i][j]);
			if (rc != 1 && rc != EOF)
				return ERR_ELEM;
			if (flag == 0 && rc == EOF)
				return NO_ELEM;
			if (rc == 1) 
				flag++;
		}
	if (flag != n * m)
		return NOT_ENOUGH_ELEM;
	
	return OK;
}

void err_code(int rc, char *argv)
{
	assert(rc != OK); 
	
	if (rc == ERR_FILE)
		printf("Couldn't open %s file!", argv);
	if (rc == EMPTY)
		printf("File %s is empty!\n", argv);
	if (rc == ERR_STR)
		printf("Wrong amount of strings in %s!\n", argv);
	if (rc == NO_COL)
		printf("No amount of columns in %s!\n", argv);
	if (rc == ERR_COL)
		printf("Wrong amount of columns in %s!\n", argv);
	if (rc == ERR_MALLOC)
		printf("Memory allocation error in %s!\n", argv);
	if (rc == ERR_ELEM)
		printf("Wrong element of matrix in %s!\n", argv);
	if (rc == NO_ELEM)
		printf("There is no matrix in %s!\n", argv);
	if (rc == NOT_ENOUGH_ELEM)
		printf("There is not enough elements of matrix in %s!\n", argv);
}

void addition(double **matrix1, int n, int m, double **matrix2, double **matrix3)
{
	assert(matrix1);
	assert(matrix2);
	assert(matrix3);
	assert(n > 0 && m > 0);
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
}

void multiply(double **matrix1, int n, int m, int q, double **matrix2, double **matrix3)
{
	assert(matrix1);
	assert(matrix2);
	assert(matrix3);
	assert(n > 0 && m > 0 && q > 0);
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			matrix3[i][j] = 0;
			for (int k = 0; k < q; k++)
				matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
		}
}

double **matr(double **a, int n, int x, double **res)
{
	assert(a);
	assert(n > 0);
	assert(res);
	
    for (int i = 1; i < n; i++)
        for (int j = 0, k = 0; j < n; j++, k++)
		{
            if (j == x)
			{
                k--;
                continue;
            }
            res[i - 1][k] = a[i][j];
        }
    return res;
}
 
double det(double **a, int n)
{
	assert(a);
	
    if (n == 1)
        return a[0][0];
    if (n == 2)
	{
		return (a[1][1] * a[0][0]) - (a[0][1] * a[1][0]);
	}
	double **res = malloc((n - 1) * sizeof(double *));
    for (int i = 0; i < n - 1; i++)
        res[i] = malloc((n - 1) * sizeof(double));
    double ans = 0, sig = 1;
    for (int i = 0; i < n; ++i)
	{
        ans += (sig * a[0][i] * det(matr(a, n, i, res), n - 1));
        sig *= -1;
    }
	for (int i = 0; i < n - 1; i++)
        free(res[i]);
	free(res);
    return ans;
}

void print_matrix(FILE *f, int n, int m, double **matrix)
{
	assert(f);
	assert(n > 0 && m > 0);
	assert(matrix);
	
	fprintf(f, "%d %d\n", n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			fprintf(f, "%lf ", matrix[i][j]);
		fprintf(f, "\n");
	}
}

void print_det(FILE *f, double det)
{
	assert(f);
	
	fprintf(f, "%lf", det);
}