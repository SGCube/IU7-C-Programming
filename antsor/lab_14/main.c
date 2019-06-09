#include <stdio.h>
#include <string.h>

#include "error.h"
#include "matrix.h"

void errmsg(int rc)
{
	switch (rc)
	{
		case OK:
			break;
		case ERR_CMD:
			printf("Not enough arguments!\n");
			break;
		case ERR_FILE:
			printf("File open error!\n");
			break;
		case ERR_INPUT:
			printf("Invalid input!\n");
			break;
		case ERR_SIZE:
			printf("Matrix size error!\n");
			break;
		case ERR_NDATA:
			printf("Not enough data!\n");
			break;
		case ERR_MEMORY:
			printf("Memory allocation error!\n");
			break;
		case ERR_MATCH:
			printf("Sizes are not matched!\n");
			break;
		default:
			printf("Unknown error!\n");
	}
}

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	
	///*** объявление переменных ********************************************
	
	int rc = OK;
	FILE *fin1 = NULL, *fin2 = NULL, *fout = NULL;
	matrix_t ma1 = create();	// 1ая матрица
	matrix_t ma2 = create();	// 2ая матрица
	matrix_t ma = create();		// матрица-результат
	
	///*** обработка аргументов *********************************************
	
	if (argc < 2)
	{
		errmsg(ERR_CMD);
		return ERR_CMD;
	}
	
	if (strcmp(argv[1], "h") == 0)
	{
		printf("app.exe in1.txt in2.txt out.txt\n"
			" - in1.txt - input file with first matrix\n"
			" - in2.txt - input file with second matrix\n"
			" - out.txt - output file\n");
		return OK;
	}
	
	if (argc < 4)
	{
		errmsg(ERR_CMD);
		return ERR_CMD;
	}
	
	///*** открытие файлов **************************************************
	
	fin1 = fopen(argv[1], "r");
	if (!fin1)
	{
		errmsg(ERR_FILE);
		destroy(ma1);
		destroy(ma2);
		destroy(ma);
		return ERR_FILE;
	}
	
	fin2 = fopen(argv[2], "r");
	if (!fin2)
	{
		errmsg(ERR_FILE);
		fclose(fin1);
		destroy(ma1);
		destroy(ma2);
		destroy(ma);
		return ERR_FILE;
	}
	
	fout = fopen(argv[3], "w");
	if (!fout)
	{
		errmsg(ERR_FILE);
		fclose(fin1);
		fclose(fin2);
		destroy(ma1);
		destroy(ma2);
		destroy(ma);
		return ERR_FILE;
	}
	
	rc = read(ma1, fin1);
	if (!rc)
	{
		rc = read(ma2, fin2);
		if (!rc)
		{
			printf("1st matrix:\n");
			print(ma1);
			printf("\n2nd matrix:\n");
			print(ma2);
			
			printf("\nChoose action\n"
				"1 - sum, 2 - multiply: ");
			char ch;
			scanf("%c", &ch);
			if (ch == '1')
				rc = sum(ma1, ma2, ma);
			else if (ch == '2')
				rc = multiply(ma1, ma2, ma);
			else
			{
				printf("Wrong action!\n");
				rc = ERR_CMD;
			}
			if (!rc)
			{
				printf("\nResult matrix:\n");
				print(ma);
				write(ma, fout);
			}
		}
	}
	
	errmsg(rc);
	fclose(fin1);
	fclose(fin2);
	fclose(fout);
	destroy(ma1);
	destroy(ma2);
	destroy(ma);
	
	return rc;
}