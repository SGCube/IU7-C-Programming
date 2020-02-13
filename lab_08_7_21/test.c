#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrixio.h"
#include "macalc.h"
#include "math.h"

#define OK 0
#define ERR_ALLOC -4

#define EPS 1e-12
#define EPS_L 1e-6

#define ERR_EMPTY -10
#define ERR_SIZE -11
#define ERR_NZ_AM -12
#define ERR_NZ_OVER -18
#define ERR_INDEX -13
#define ERR_ELEM -14
#define NOT_ENOUGH_DATA -15
#define ERR_OVERWRITE -16
#define ERR_INPUT_ZERO -17

#define ERR_SIZE_MATCH -20
#define NOT_SQUARE_M -21
#define SINGULAR_M -22

int matrcmp(double **ma1, double **ma2, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (fabs(ma1[i][j] - ma2[i][j]) > EPS_L)
				return 0;
	return 1;
}

int read_matrix_out(FILE *f, double **ma, int n, int m)
{
	assert(f);
	assert(ma);
	assert(n > 0 && m > 0);
	
	int sc;
	double x;
	
	init_matrix(ma, n, m);
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			sc = fscanf(f, "%lf", &x);
			if (sc == EOF)
				return NOT_ENOUGH_DATA;
			if (sc != 1)
				return ERR_ELEM;
			ma[i][j] = x;
		}
	return OK;
}

void read_testmatr(FILE *f1, FILE *f2, FILE *f3,
	int *n1, int *n2, int *n, int *m1, int *m2, int *m,
	double ***ma1, double ***ma2, double ***ma, double ***mar)
{
	read_matrix_size(f1, n1, m1);
	read_matrix_size(f2, n2, m2);
	read_matrix_size(f3, n, m);
	*ma1 = alloc_matrix(*n1, *m1);
	*ma2 = alloc_matrix(*n2, *m2);
	*ma = alloc_matrix(*n, *m);
	*mar = alloc_matrix(*n, *m);
	assert(*ma && *mar && *ma1 && *ma2);
	assert(read_matrix(f1, *ma1, *n1, *m1) == OK);
	assert(read_matrix(f2, *ma2, *n2, *m2) == OK);
	assert(read_matrix_out(f3, *mar, *n, *m) == OK);
}

void read_testmatrrev(FILE *f1, FILE *f2, int *n,
	double ***ma0, double ***ma, double ***mar)
{
	read_matrix_size(f1, n, n);
	read_matrix_size(f2, n, n);
	*ma0 = alloc_matrix(*n, *n);
	*ma = alloc_matrix(*n, *n);
	*mar = alloc_matrix(*n, *n);
	assert(*ma && *mar && *ma0);
	assert(read_matrix(f1, *ma0, *n, *n) == OK);
	assert(read_matrix_out(f2, *mar, *n, *n) == OK);
	ident_matrix(*ma, *n);
}

void test_matrsum_check(FILE *f1, FILE *f2, FILE *f3)
{
	assert(f1 && f2 && f3);
	int n, m;
	double **ma1 = NULL, **ma2 = NULL;
	double **ma = NULL, **mar = NULL;
	read_testmatr(f1, f2, f3, &n, &n, &n, &m, &m, &m, &ma1, &ma2, &ma, &mar);
	
	matrsum(ma1, ma2, ma, n, m);
	if (matrcmp(ma, mar, n, m))
		printf("OK\n");
	else
		printf("FAILED\n");
	
	free(ma);
	free(mar);
	free(ma1);
	free(ma2);
	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void test_matrmult_check(FILE *f1, FILE *f2, FILE *f3)
{
	assert(f1 && f2 && f3);
	int n1, m1, n2, m2;
	double **ma1 = NULL, **ma2 = NULL;
	double **ma = NULL, **mar = NULL;
	read_testmatr(f1, f2, f3, &n1, &n2, &n1, &m1, &m2, &m2,
		&ma1, &ma2, &ma, &mar);
	
	matrmult(ma1, ma2, ma, n1, m1, n2, m2);
	if (matrcmp(ma, mar, n1, m2))
		printf("OK\n");
	else
		printf("FAILED\n");
	
	free(ma);
	free(mar);
	free(ma1);
	free(ma2);
	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void test_matrrev_check(FILE *f1, FILE *f2)
{
	assert(f1 && f2);
	int n;
	double **ma0 = NULL, **ma = NULL, **mar = NULL;
	read_testmatrrev(f1, f2, &n, &ma0, &ma, &mar);
	
	matrrev(ma0, ma, n);
	if (matrcmp(ma, mar, n, n))
		printf("OK\n");
	else
		printf("FAILED\n");
	
	free(ma);
	free(mar);
	free(ma0);
	fclose(f1);
	fclose(f2);
}

void test_read_matrix_size(void)
{
	FILE *f;
	int n, m;
	printf("read_matrix_size:\n");
	{
		printf("#1: ");
		f = fopen("tests_io/in_0.txt", "r");
		assert(f);
		if (read_matrix_size(f, &n, &m) != ERR_EMPTY)
			printf("FAILED\n");
		else
			printf("OK\n");
		fclose(f);
	}
	{
		printf("#2: ");
		f = fopen("tests_io/in_1.txt", "r");
		assert(f);
		if (read_matrix_size(f, &n, &m) != ERR_SIZE)
			printf("FAILED\n");
		else
			printf("OK\n");
		fclose(f);
	}
	{
		printf("#3: ");
		f = fopen("tests_io/in_2.txt", "r");
		assert(f);
		if (read_matrix_size(f, &n, &m) != ERR_SIZE)
			printf("FAILED\n");
		else
			printf("OK\n");
		fclose(f);
	}
	{
		printf("#4: ");
		f = fopen("tests_io/in_3.txt", "r");
		assert(f);
		if (read_matrix_size(f, &n, &m) != ERR_SIZE)
			printf("FAILED\n");
		else
			printf("OK\n");
		fclose(f);
	}
	{
		printf("#5: ");
		f = fopen("tests_io/in_4.txt", "r");
		assert(f);
		if (read_matrix_size(f, &n, &m) != ERR_SIZE)
			printf("FAILED\n");
		else
			printf("OK\n");
		fclose(f);
	}
	printf("\n");
}

void test_read_matrix(void)
{
	int rcodes[13] = { ERR_NZ_AM, ERR_INDEX, ERR_NZ_AM, ERR_NZ_OVER,
		ERR_INDEX, ERR_INDEX, ERR_INDEX, ERR_INDEX, ERR_INDEX,
		ERR_ELEM, NOT_ENOUGH_DATA, ERR_OVERWRITE, ERR_INPUT_ZERO };
	char *str[13] = { "tests_io/in_5.txt",
		"tests_io/in_6.txt",
		"tests_io/in_7.txt",
		"tests_io/in_8.txt",
		"tests_io/in_9.txt",
		"tests_io/in_10.txt",
		"tests_io/in_11.txt",
		"tests_io/in_12.txt",
		"tests_io/in_13.txt",
		"tests_io/in_14.txt",
		"tests_io/in_15.txt",
		"tests_io/in_16.txt",
		"tests_io/in_17.txt" };
	FILE *f;
	int n, m;
	double **ma;
	printf("read_matrix:\n");
	for (int i = 0; i < 13; i++)
	{
		printf("#%d: ", i + 1);
		f = fopen(str[i], "r");
		assert(f);
		assert(read_matrix_size(f, &n, &m) == OK);
		ma = alloc_matrix(n, m);
		assert(ma);
		if (read_matrix(f, ma, n, m) != rcodes[i])
			printf("FAILED\n");
		else
			printf("OK\n");
		fclose(f);
		free(ma);
	}
	printf("\n");
}

void test_init_matrix(void)
{
	double **ma;
	printf("init_matrix:\n");
	{
		printf("#1: ");
		ma = alloc_matrix(1, 1);
		assert(ma);
		init_matrix(ma, 1, 1);
		if (ma[0][0] != 0)
			printf("FAILED\n");
		else
			printf("OK\n");
		free(ma);
	}
	{
		printf("#2: ");
		ma = alloc_matrix(3, 3);
		assert(ma);
		init_matrix(ma, 3, 3);
		short int not_null = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				if (ma[0][0] != 0)
				{
					not_null = 1;
					break;
				}
			if (not_null)
				break;
		}
		if (not_null)
			printf("FAILED\n");
		else
			printf("OK\n");
		free(ma);
	}
	printf("\n");
}

void test_ident_matrix(void)
{
	double **ma;
	printf("ident_matrix:\n");
	{
		printf("#1: ");
		ma = alloc_matrix(1, 1);
		assert(ma);
		ident_matrix(ma, 1);
		if (ma[0][0] != 1)
			printf("FAILED\n");
		else
			printf("OK\n");
		free(ma);
	}
	{
		printf("#2: ");
		ma = alloc_matrix(3, 3);
		assert(ma);
		ident_matrix(ma, 3);
		short int not_ident = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				if ((i == j && ma[i][j] != 1) || (i != j && ma[i][j] != 0))
				{
					not_ident = 1;
					break;
				}
			if (not_ident)
				break;
		}
		if (not_ident)
			printf("FAILED\n");
		else
			printf("OK\n");
		free(ma);
	}
	printf("\n");
}

void test_matrsum(void)
{
	printf("matrsum:\n");
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#1: ");
		f1 = fopen("tests_a/in_1_0.txt", "r");
		f2 = fopen("tests_a/in_1_1.txt", "r");
		f3 = fopen("tests_a/out_1.txt", "r");
		test_matrsum_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#2: ");
		f1 = fopen("tests_a/in_2_0.txt", "r");
		f2 = fopen("tests_a/in_2_1.txt", "r");
		f3 = fopen("tests_a/out_2.txt", "r");
		test_matrsum_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#3: ");
		f1 = fopen("tests_a/in_3_0.txt", "r");
		f2 = fopen("tests_a/in_3_1.txt", "r");
		f3 = fopen("tests_a/out_3.txt", "r");
		test_matrsum_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#4: ");
		f1 = fopen("tests_a/in_4_0.txt", "r");
		f2 = fopen("tests_a/in_4_1.txt", "r");
		f3 = fopen("tests_a/out_4.txt", "r");
		test_matrsum_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#5: ");
		f1 = fopen("tests_a/in_5_0.txt", "r");
		f2 = fopen("tests_a/in_5_1.txt", "r");
		f3 = fopen("tests_a/out_5.txt", "r");
		test_matrsum_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#6: ");
		f1 = fopen("tests_a/in_6_0.txt", "r");
		f2 = fopen("tests_a/in_6_1.txt", "r");
		f3 = fopen("tests_a/out_6.txt", "r");
		test_matrsum_check(f1, f2, f3);
	}
	printf("\n");
}

void test_matrmult(void)
{
	printf("matrmult:\n");
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#1: ");
		f1 = fopen("tests_m/in_1_0.txt", "r");
		f2 = fopen("tests_m/in_1_1.txt", "r");
		f3 = fopen("tests_m/out_1.txt", "r");
		test_matrmult_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#2: ");
		f1 = fopen("tests_m/in_2_0.txt", "r");
		f2 = fopen("tests_m/in_2_1.txt", "r");
		f3 = fopen("tests_m/out_2.txt", "r");
		test_matrmult_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#3: ");
		f1 = fopen("tests_m/in_3_0.txt", "r");
		f2 = fopen("tests_m/in_3_1.txt", "r");
		f3 = fopen("tests_m/out_3.txt", "r");
		test_matrmult_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#4: ");
		f1 = fopen("tests_m/in_4_0.txt", "r");
		f2 = fopen("tests_m/in_4_1.txt", "r");
		f3 = fopen("tests_m/out_4.txt", "r");
		test_matrmult_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#5: ");
		f1 = fopen("tests_m/in_5_0.txt", "r");
		f2 = fopen("tests_m/in_5_1.txt", "r");
		f3 = fopen("tests_m/out_5.txt", "r");
		test_matrmult_check(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#6: ");
		f1 = fopen("tests_m/in_6_0.txt", "r");
		f2 = fopen("tests_m/in_6_1.txt", "r");
		f3 = fopen("tests_m/out_6.txt", "r");
		test_matrmult_check(f1, f2, f3);
	}
	printf("\n");
}

void test_matrrev(void)
{
	printf("matrrev:\n");
	{
		int n = 0;
		double **ma0 = NULL, **ma = NULL;
		FILE *f1 = NULL;
		printf("#1: ");
		f1 = fopen("tests_o/in_1.txt", "r");
		assert(f1);
		
		read_matrix_size(f1, &n, &n);
		ma0 = alloc_matrix(n, n);
		ma = alloc_matrix(n, n);
		assert(ma && ma0);
		assert(read_matrix(f1, ma0, n, n) == OK);
		ident_matrix(ma, n);
		
		if (matrrev(ma0, ma, n) == SINGULAR_M)
			printf("OK\n");
		else
			printf("FAILED\n");
		
		free(ma);
		free(ma0);
		fclose(f1);
	}
	{
		FILE *f1 = NULL, *f2 = NULL;
		printf("#2: ");
		f1 = fopen("tests_o/in_2.txt", "r");
		f2 = fopen("tests_o/out_2.txt", "r");
		test_matrrev_check(f1, f2);
	}
	{
		FILE *f1 = NULL, *f2 = NULL;
		printf("#3: ");
		f1 = fopen("tests_o/in_3.txt", "r");
		f2 = fopen("tests_o/out_3.txt", "r");
		test_matrrev_check(f1, f2);
	}
	{
		FILE *f1 = NULL, *f2 = NULL;
		printf("#4: ");
		f1 = fopen("tests_o/in_4.txt", "r");
		f2 = fopen("tests_o/out_4.txt", "r");
		test_matrrev_check(f1, f2);
	}
	printf("\n");
}

int main(void)
{
	test_read_matrix_size();
	test_read_matrix();
	test_init_matrix();
	test_ident_matrix();
	test_matrsum();
	test_matrmult();
	test_matrrev();
	return 0;
}