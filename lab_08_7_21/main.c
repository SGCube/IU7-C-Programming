#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileio.h"
#include "matrixio.h"
#include "macalc.h"

#define OK 0

#define ERR_CMD -1
#define ERR_FLAG -2
#define ERR_FILE -3

#define ERR_IFILE1 -1
#define ERR_IFILE2 -2
#define ERR_OFILE -3

#define ERR_ALLOC -4

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

int main(int argc, char **argv)
{
	int rc = OK;
	char act = 0;
	FILE *fin1 = NULL, *fin2 = NULL, *fout = NULL;
	double **ma1 = NULL, **ma2 = NULL, **ma = NULL;
	int n1 = 0, m1 = 0;
	int n2 = 0, m2 = 0;
	int n = 0, m = 0;
	
	///обработка аргументов командной строки
	if (argc < 2)
	{
		fprintf(stderr, "Not enough arguments!\n");
		return ERR_CMD;
	}
	
	if (strcmp(argv[1], "h") == 0)
	{
		fprintf(stdout, "app.exe <action> <input1> [<input2>] <output>\n"
			" - <action>:\n"
			" - \ta - sum 2 matrices\n"
			" - \tm - multiply 2 matrices\n"
			" - \to - find reverse matrix to source one\n"
			" - \th - show help\n"
			" - <input1> - input file with first matrix\n"
			" - <input2> - input file with second matrix "
			"(in case of 'a' or 'm' action)\n"
			" - <output> - output file\n");
		return OK;
	}
	if (strcmp(argv[1], "a") != 0 && strcmp(argv[1], "m") != 0 &&
		strcmp(argv[1], "o") != 0)
	{
		fprintf(stderr, "No such action!\n");
		return ERR_FLAG;	
	}
	act = argv[1][0];
	if ((act != 'o' && argc < 5) || argc < 4)
	{
		fprintf(stderr, "Not enough arguments!\n");
		return ERR_CMD;
	}
	
	///открытие файлов
	rc = file_open(act, argv, &fin1, &fin2, &fout);
	if (!fin1)
		ioerror_msg(ERR_FILE, argv[2]);
	else if (act != 'o' && !fin2)
		ioerror_msg(ERR_FILE, argv[3]);
	else if (act != 'o' && !fout)
		ioerror_msg(ERR_FILE, argv[4]);
	else if (!fout)
		ioerror_msg(ERR_FILE, argv[3]); 
	if (rc != OK)
	{
		fclose_all(fin1, fin2, fout);
		return ERR_FILE;
	}
	
	///выделение памяти под матрицы и их чтение
	rc = read_matrix_size(fin1, &n1, &m1);
	if (rc != OK)
	{
		ioerror_msg(rc, argv[2]);
		fclose_all(fin1, fin2, fout);
		return rc;
	}
	ma1 = alloc_matrix(n1, m1);
	if (!ma1)
	{
		fprintf(stderr, "Memory allocation error!\n");
		fclose_all(fin1, fin2, fout);
		return ERR_ALLOC;
	}
	rc = read_matrix(fin1, ma1, n1, m1);
	if (rc != OK)
	{
		ioerror_msg(rc, argv[2]);
		fclose_all(fin1, fin2, fout);
		free(ma1);
		return rc;
	}
	//fclose(fin1);
	
	if (act != 'o')
	{
		rc = read_matrix_size(fin2, &n2, &m2);
		if (rc != OK)
		{
			ioerror_msg(rc, argv[3]);
			fclose_all(fin1, fin2, fout);
			free(ma1);
			return rc;
		}
		ma2 = alloc_matrix(n2, m2);
		if (!ma2)
		{
			fprintf(stderr, "Memory allocation error!\n");
			fclose_all(fin1, fin2, fout);
			free(ma1);
			return ERR_ALLOC;
		}
		rc = read_matrix(fin2, ma2, n2, m2);
		if (rc != OK)
		{
			ioerror_msg(rc, argv[3]);
			fclose_all(fin1, fin2, fout);
			free(ma1);
			free(ma2);
			return rc;
		}
		//fclose(fin2);
		
		if (act == 'a')
		{
			if (n1 != n2 || m1 != m2)
				rc = ERR_SIZE_MATCH;
			else
			{
				n = n1;
				m = m1;
				ma = alloc_matrix(n, m);
				if (!ma)
				{
					fprintf(stderr, "Memory allocation error!\n");
					fclose_all(fin1, fin2, fout);
					free(ma1);
					free(ma2);
					return ERR_ALLOC;
				}
				matrsum(ma1, ma2, ma, n1, m1);
			}
		}
		if (act == 'm')
		{
			if (m1 != n2)
				rc = ERR_SIZE_MATCH;
			else
			{
				n = n1;
				m = m2;
				ma = alloc_matrix(n, m);
				if (!ma)
				{
					fprintf(stderr, "Memory allocation error!\n");
					fclose_all(fin1, fin2, fout);
					free(ma1);
					free(ma2);
					return ERR_ALLOC;
				}
				matrmult(ma1, ma2, ma, n1, m1, n2, m2);
			}
		}
		if (rc == ERR_SIZE_MATCH)
			fprintf(stderr, "Matrices sizes are not appropriate!\n");
		else
			print_matrix(fout, ma, n, m);
	}
	else
	{
		if (n1 != m1)
		{
			fprintf(stderr, "Matrix is not square!\n");
			rc = NOT_SQUARE_M;
		}
		else
		{
			n = n1;
			m = n1;
			ma = alloc_matrix(n, m);
			if (!ma)
			{
				fprintf(stderr, "Memory allocation error!\n");
				fclose_all(fin1, fin2, fout);
				free(ma1);
				return ERR_ALLOC;
			}
			ident_matrix(ma, n);
			rc = matrrev(ma1, ma, n);
			if (rc == SINGULAR_M)
				fprintf(stderr, "Matrix is singular!\n");
			else
				print_matrix(fout, ma, n, m);
		}
	}
	
	fclose_all(fin1, fin2, fout);
	if (ma1)
		free(ma1);
	if (ma2)
		free(ma2);
	if (ma)
		free(ma);
	
	return rc;
}