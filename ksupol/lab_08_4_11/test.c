#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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
#define EPS 0.0001

void test_read_str_col()
{
	int err_cnt = 0;
	{
		FILE *f;
		int n = 0, m = 0;
		f = fopen("tsts_test/read_str_col/in_0.txt", "r");
		if (read_str_col(f, &n, &m) != EMPTY)
			err_cnt++;
		fclose(f);
	}
	{
		FILE *f;
		int n = 0, m = 0;
		f = fopen("tsts_test/read_str_col/in_1.txt", "r");
		if (read_str_col(f, &n, &m) != ERR_STR)
			err_cnt++;
		fclose(f);
	}
	{
		FILE *f;
		int n = 0, m = 0;
		f = fopen("tsts_test/read_str_col/in_2.txt", "r");
		if (read_str_col(f, &n, &m) != ERR_STR)
			err_cnt++;
		fclose(f);
	}
	{
		FILE *f;
		int n = 0, m = 0;
		f = fopen("tsts_test/read_str_col/in_3.txt", "r");
		if (read_str_col(f, &n, &m) != NO_COL)
			err_cnt++;
		fclose(f);
	}
	{
		FILE *f;
		int n = 0, m = 0;
		f = fopen("tsts_test/read_str_col/in_4.txt", "r");
		if (read_str_col(f, &n, &m) != ERR_COL)
			err_cnt++;
		fclose(f);
	}
	{
		FILE *f;
		int n = 0, m = 0;
		f = fopen("tsts_test/read_str_col/in_5.txt", "r");
		if (read_str_col(f, &n, &m) != ERR_COL)
			err_cnt++;
		fclose(f);
	}
	{
		FILE *f;
		int n = 0, m = 0;
		int n1 = 5, m1 = 2;
		f = fopen("tsts_test/read_str_col/in_6.txt", "r");
		if (read_str_col(f, &n, &m) != OK)
			err_cnt++;
		if (n != n1 && m != m1)
			err_cnt++;
		fclose(f);
	}
	printf("\n\ntest_read_str_col %s", err_cnt ? "FAILED" : "OK");
}

void test_read_matrix()
{
	int err_cnt = 0;
	
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		
		f = fopen("tsts_test/read_matrix/in_0.txt", "r");
		read_str_col(f, &n, &m);
		if (read_matrix(f, &matrix, n, m) != ERR_ELEM)
			err_cnt++;
		free_matrix(matrix);
		fclose(f);
	}
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		
		f = fopen("tsts_test/read_matrix/in_2.txt", "r");
		read_str_col(f, &n, &m);
		if (read_matrix(f, &matrix, n, m) != NO_ELEM)
			err_cnt++;
		free_matrix(matrix);
		fclose(f);
	}
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		
		f = fopen("tsts_test/read_matrix/in_1.txt", "r");
		read_str_col(f, &n, &m);
		if (read_matrix(f, &matrix, n, m) != NOT_ENOUGH_ELEM)
			err_cnt++;
		free_matrix(matrix);
		fclose(f);
	}
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		double a[3][2] = { { 2.2, 4.1 }, { 3.5, 1.2 }, { -2.2, -4.1 } };
		
		f = fopen("tsts_test/read_matrix/in_3.txt", "r");
		read_str_col(f, &n, &m);
		if (read_matrix(f, &matrix, n, m) != OK)
			err_cnt++;
		else
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					if (fabs(matrix[i][j] - a[i][j]) > EPS)
					{
						err_cnt++;
						break;
					}
		free_matrix(matrix);
		fclose(f);
	}
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		double a[1][1] = { { 5.03 } };
		
		f = fopen("tsts_test/read_matrix/in_4.txt", "r");
		read_str_col(f, &n, &m);
		if (read_matrix(f, &matrix, n, m) != OK)
			err_cnt++;
		else
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					if (fabs(matrix[i][j] - a[i][j]) > EPS)
					{
						err_cnt++;
						break;
					}
		free_matrix(matrix);
		fclose(f);
	}
	printf("\n\ntest_read_matrix %s", err_cnt ? "FAILED" : "OK");
}

void test_addition()
{
	int err_cnt = 0;
	{
		FILE *f1, *f2;
		double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
		int n1 = 0, m1 = 0;
		int n2 = 0, m2 = 0;
		double a[1][1] = { { -3 } };
		
		f1 = fopen("tsts_test/addition/in_1.txt", "r");
		f2 = fopen("tsts_test/addition/in_1_1.txt", "r");
		read_str_col(f1, &n1, &m1);
		read_matrix(f1, &matrix1, n1, m1);
		read_str_col(f2, &n2, &m2);
		read_matrix(f2, &matrix2, n2, m2);
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
			printf("Memory allociaton error!\n");
		addition(matrix1, n1, m1, matrix2, matrix3);
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < m1; j++)
				if (fabs(matrix3[i][j] - a[i][j]) > EPS)
				{
					err_cnt++;
					break;
				}
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
	}
	{
		FILE *f1, *f2;
		double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
		int n1 = 0, m1 = 0;
		int n2 = 0, m2 = 0;
		double a[3][3] = { { 1, 2, 3 }, { -5, -3.2, -5 }, { 7.4, 0, -9 } };
		
		f1 = fopen("tsts_test/addition/in_2.txt", "r");
		f2 = fopen("tsts_test/addition/in_2_1.txt", "r");
		read_str_col(f1, &n1, &m1);
		read_matrix(f1, &matrix1, n1, m1);
		read_str_col(f2, &n2, &m2);
		read_matrix(f2, &matrix2, n2, m2);
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
			printf("Memory allocation error!\n");
		addition(matrix1, n1, m1, matrix2, matrix3);
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < m1; j++)
				if (fabs(matrix3[i][j] - a[i][j]) > EPS)
				{
					err_cnt++;
					break;
				}
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
	}
	{
		FILE *f1, *f2;
		double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
		int n1 = 0, m1 = 0;
		int n2 = 0, m2 = 0;
		double a[3][1] = { { 0 }, { 0 }, { 0 } };
		
		f1 = fopen("tsts_test/addition/in_3.txt", "r");
		f2 = fopen("tsts_test/addition/in_3_1.txt", "r");
		read_str_col(f1, &n1, &m1);
		read_matrix(f1, &matrix1, n1, m1);
		read_str_col(f2, &n2, &m2);
		read_matrix(f2, &matrix2, n2, m2);
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
			printf("Memory allocation error!\n");
		addition(matrix1, n1, m1, matrix2, matrix3);
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < m1; j++)
				if (fabs(matrix3[i][j] - a[i][j]) > EPS)
				{
					err_cnt++;
					break;
				}
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
	}
	{
		FILE *f1, *f2;
		double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
		int n1 = 0, m1 = 0;
		int n2 = 0, m2 = 0;
		double a[1][3] = { { 4, 4, 4 } };
		
		f1 = fopen("tsts_test/addition/in_4.txt", "r");
		f2 = fopen("tsts_test/addition/in_4_1.txt", "r");
		read_str_col(f1, &n1, &m1);
		read_matrix(f1, &matrix1, n1, m1);
		read_str_col(f2, &n2, &m2);
		read_matrix(f2, &matrix2, n2, m2);
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
			printf("Memory allocation error!\n");
		addition(matrix1, n1, m1, matrix2, matrix3);
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < m1; j++)
				if (fabs(matrix3[i][j] - a[i][j]) > EPS)
				{
					err_cnt++;
					break;
				}
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
	}
	printf("\n\ntest_addition %s", err_cnt ? "FAILED" : "OK");
}

void test_multiply()
{
	int err_cnt = 0;
	{
		FILE *f1, *f2;
		double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
		int n1 = 0, m1 = 0;
		int n2 = 0, m2 = 0;
		double a[1][1] = { { -35 } };
		
		f1 = fopen("tsts_test/multiply/in_1.txt", "r");
		f2 = fopen("tsts_test/multiply/in_1_1.txt", "r");
		read_str_col(f1, &n1, &m1);
		read_matrix(f1, &matrix1, n1, m1);
		read_str_col(f2, &n2, &m2);
		read_matrix(f2, &matrix2, n2, m2);
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
			printf("Memory allocation error!\n");
		multiply(matrix1, n1, m2, n2, matrix2, matrix3);
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < m1; j++)
				if (fabs(matrix3[i][j] - a[i][j]) > EPS)
				{
					err_cnt++;
					break;
				}
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
	}
	{
		FILE *f1, *f2;
		double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
		int n1 = 0, m1 = 0;
		int n2 = 0, m2 = 0;
		double a[2][1] = { { 4 }, { 8 } };
		
		f1 = fopen("tsts_test/multiply/in_2.txt", "r");
		f2 = fopen("tsts_test/multiply/in_2_1.txt", "r");
		read_str_col(f1, &n1, &m1);
		read_matrix(f1, &matrix1, n1, m1);
		read_str_col(f2, &n2, &m2);
		read_matrix(f2, &matrix2, n2, m2);
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
			printf("Memory allocation error!\n");
		multiply(matrix1, n1, m2, n2, matrix2, matrix3);
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < m2; j++)
				if (fabs(matrix3[i][j] - a[i][j]) > EPS)
				{
					err_cnt++;
					break;
				}
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
	}
	{
		FILE *f1, *f2;
		double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
		int n1 = 0, m1 = 0;
		int n2 = 0, m2 = 0;
		double a[3][2] = { { 1, 2 }, { 2, 4 }, { 3, 6 } };
		
		f1 = fopen("tsts_test/multiply/in_3.txt", "r");
		f2 = fopen("tsts_test/multiply/in_3_1.txt", "r");
		read_str_col(f1, &n1, &m1);
		read_matrix(f1, &matrix1, n1, m1);
		read_str_col(f2, &n2, &m2);
		read_matrix(f2, &matrix2, n2, m2);
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
			printf("Memory allocation error!\n");
		multiply(matrix1, n1, m2, n2, matrix2, matrix3);
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < m2; j++)
				if (fabs(matrix3[i][j] - a[i][j]) > EPS)
				{
					err_cnt++;
					break;
				}
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
	}
	{
		FILE *f1, *f2;
		double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
		int n1 = 0, m1 = 0;
		int n2 = 0, m2 = 0;
		double a[1][2] = { { 0, 0 } };
		
		f1 = fopen("tsts_test/multiply/in_4.txt", "r");
		f2 = fopen("tsts_test/multiply/in_4_1.txt", "r");
		read_str_col(f1, &n1, &m1);
		read_matrix(f1, &matrix1, n1, m1);
		read_str_col(f2, &n2, &m2);
		read_matrix(f2, &matrix2, n2, m2);
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
			printf("Memory allocation error!\n");
		multiply(matrix1, n1, m2, n2, matrix2, matrix3);
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < m2; j++)
				if (fabs(matrix3[i][j] - a[i][j]) > EPS)
				{
					err_cnt++;
					break;
				}
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
	}
	{
		FILE *f1, *f2;
		double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
		int n1 = 0, m1 = 0;
		int n2 = 0, m2 = 0;
		double a[2][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
		
		f1 = fopen("tsts_test/multiply/in_5.txt", "r");
		f2 = fopen("tsts_test/multiply/in_5_1.txt", "r");
		read_str_col(f1, &n1, &m1);
		read_matrix(f1, &matrix1, n1, m1);
		read_str_col(f2, &n2, &m2);
		read_matrix(f2, &matrix2, n2, m2);
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
			printf("Memory allocation error!\n");
		multiply(matrix1, n1, m2, n2, matrix2, matrix3);
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < m2; j++)
				if (fabs(matrix3[i][j] - a[i][j]) > EPS)
				{
					err_cnt++;
					break;
				}
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
	}
	printf("\n\ntest_multiply %s", err_cnt ? "FAILED" : "OK");
}

void test_det()
{
	int err_cnt = 0;
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		double a = 5;
		
		f = fopen("tsts_test/det/in_1.txt", "r");
		read_str_col(f, &n, &m);
		read_matrix(f, &matrix, n, m);
		if (det(matrix, n) != a)
			err_cnt++;
		free_matrix(matrix);
		fclose(f);
	}
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		double a = -2;
		
		f = fopen("tsts_test/det/in_2.txt", "r");
		read_str_col(f, &n, &m);
		read_matrix(f, &matrix, n, m);
		if (det(matrix, n) != a)
			err_cnt++;
		free_matrix(matrix);
		fclose(f);
	}
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		double a = 0;
		
		f = fopen("tsts_test/det/in_3.txt", "r");
		read_str_col(f, &n, &m);
		read_matrix(f, &matrix, n, m);
		if (det(matrix, n) != a)
			err_cnt++;
		free_matrix(matrix);
		fclose(f);
	}
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		double a = 0;
		
		f = fopen("tsts_test/det/in_4.txt", "r");
		read_str_col(f, &n, &m);
		read_matrix(f, &matrix, n, m);
		if (det(matrix, n) != a)
			err_cnt++;
		free_matrix(matrix);
		fclose(f);
	}
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		double a = 0;
		
		f = fopen("tsts_test/det/in_5.txt", "r");
		read_str_col(f, &n, &m);
		read_matrix(f, &matrix, n, m);
		if (det(matrix, n) != a)
			err_cnt++;
		free_matrix(matrix);
		fclose(f);
	}
	{
		FILE *f;
		double **matrix = NULL;
		int n = 0, m = 0;
		double a = 15;
		
		f = fopen("tsts_test/det/in_6.txt", "r");
		read_str_col(f, &n, &m);
		read_matrix(f, &matrix, n, m);
		if (det(matrix, n) != a)
			err_cnt++;
		free_matrix(matrix);
		fclose(f);
	}
	printf("\n\ntest_multiply %s", err_cnt ? "FAILED" : "OK");
}


int main()
{
	test_read_str_col();
	test_read_matrix();
	test_addition();
	test_multiply();
	test_det();
	
	return 0;
}