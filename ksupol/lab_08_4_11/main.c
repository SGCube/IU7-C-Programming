#include <stdio.h>
#include <string.h>
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

int main(int argc, char **argv)
{
	FILE *f1 = NULL;
	FILE *f2 = NULL;
	FILE *f3 = NULL;
	double **matrix1 = NULL, **matrix2 = NULL, **matrix3 = NULL;
	int n1 = 0, m1 = 0;
	int n2 = 0, m2 = 0;
	int rc = 0;
	
	if (argc == 1)
	{
		printf("Not enough data!\n");
		return ERR_NOT_ENOUGH;
	}
	if (strcmp(argv[1], "h") == 0)
	{
		printf("\nInformation about programm:\nName: Polyakova Ksenya\n"
			"Group: IU7-32B\nDate: 09.10.18");
		return INF;
	}
	if (strcmp(argv[1], "a") != 0 &&
		strcmp(argv[1], "m") != 0 && strcmp(argv[1], "o") != 0)
	{
		printf("There's no such action!\n");
		return ERR_I;
	}
	if (argc < 4)
	{
		printf("Not enough data!\n");
		return ERR_NOT_ENOUGH;
	}
	if (argc == 4 && strcmp(argv[1], "o") != 0)
	{
		printf("Not enough data!\n");
		return ERR_NOT_ENOUGH;
	}
	rc = file_work(argc, argv, &f1, &f2, &f3);
	if (rc != OK)
	{
		err_code(rc, argv[2]);
		return rc;
	}
	rc = read_str_col(f1, &n1, &m1);
	if (rc != OK)
	{
		err_code(rc, argv[2]);
		if (argc == 4)
		{
			fclose(f1);
			fclose(f2);
		}
		else
		{
			fclose(f1);
			fclose(f2);
			fclose(f3);
			return rc;
		}
	}
	if (strcmp(argv[1], "o") == 0)
	{
		if (n1 != m1)
		{
			printf("Couldn't find determinant of this matrix!\n");
			fclose(f1);
			fclose(f2);
			return ERR;
		}
		rc = read_matrix(f1, &matrix1, n1, m1);
		if (rc != OK)
		{
			err_code(rc, argv[2]);
			fclose(f1);
			fclose(f2);
			free_matrix(matrix1);
			return rc;
		}
		print_det(f2, det(matrix1, n1));
		fclose(f1);
		fclose(f2);
		free_matrix(matrix1);
	}
	if (strcmp(argv[1], "a") == 0)
	{
		rc = read_str_col(f2, &n2, &m2);
		if (rc != OK)
		{
			err_code(rc, argv[3]);
			fclose(f1);
			fclose(f2);
			fclose(f3);
			return rc;
		}
		rc = read_matrix(f1, &matrix1, n1, m1);
		if (rc != OK)
		{
			err_code(rc, argv[2]);
			fclose(f1);
			fclose(f2);
			fclose(f3);
			free_matrix(matrix1);
			return rc;
		}
		rc = read_matrix(f2, &matrix2, n2, m2);
		if (rc != OK)
		{
			err_code(rc, argv[3]);
			fclose(f1);
			fclose(f2);
			fclose(f3);
			free_matrix(matrix1);
			free_matrix(matrix2);
			return rc;
		}
		if (n1 != n2 || m1 != m2)
		{
			printf("We can't fold matrix with "
				"different amount of strings or/and columns!\n");
			fclose(f1);
			fclose(f2);
			fclose(f3);
			free_matrix(matrix1);
			free_matrix(matrix2);
			return ERR;
		}
		matrix3 = allocate_matrix(n1, m1);
		if (!matrix3)
		{
			printf("Memory allocation error!");
			fclose(f1);
			fclose(f2);
			fclose(f3);
			free_matrix(matrix1);
			free_matrix(matrix2);
			free_matrix(matrix3);
			return ERR_MALLOC;
		}
		addition(matrix1, n1, m1, matrix2, matrix3);
		print_matrix(f3, n1, m1, matrix3);
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
		fclose(f3);
	}
	if (strcmp(argv[1], "m") == 0)
	{
		rc = read_str_col(f2, &n2, &m2);
		if (rc != OK)
		{
			err_code(rc, argv[3]);
			fclose(f1);
			fclose(f2);
			fclose(f3);
			return rc;
		}
		if (m1 != n2)
		{
			printf("We can't multiply matrix!\n");
			fclose(f1);
			fclose(f2);
			fclose(f3);
			return ERR;
		}
		rc = read_matrix(f1, &matrix1, n1, m1);
		if (rc != OK)
		{
			err_code(rc, argv[2]);
			fclose(f1);
			fclose(f2);
			fclose(f3);
			free_matrix(matrix1);
			return rc;
		}
		rc = read_matrix(f2, &matrix2, n2, m2);
		if (rc != OK)
		{
			err_code(rc, argv[3]);
			fclose(f1);
			fclose(f2);
			fclose(f3);
			free_matrix(matrix1);
			free_matrix(matrix2);
			return rc;
		}
		matrix3 = allocate_matrix(n1, m2);
		if (!matrix3)
		{
			fclose(f1);
			fclose(f2);
			fclose(f3);
			free_matrix(matrix1);
			free_matrix(matrix2);
			free_matrix(matrix3);
			return ERR_MALLOC;
		}
		multiply(matrix1, n1, m2, n2, matrix2, matrix3);
		print_matrix(f3, n1, m2, matrix3);
		free_matrix(matrix1);
		free_matrix(matrix2);
		free_matrix(matrix3);
		fclose(f1);
		fclose(f2);
		fclose(f3);
	}
	return rc;
}