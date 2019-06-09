/*
программа, определяющая количество различных целых чисел в файле

Допущения: в качестве целочисленного типа данных используетс€ тип int
Элементов не больше 100. Элементы, введённые после 100ого, не учитываются.
*/
#include <stdio.h>

#define OK 0
#define CMD_ERR -1
#define FILE_ERR -2
#define NO_DATA -3
#define IO_ERR -4

#define MAX_N 100

int ReadArray(FILE *, int * const, int **);
void PrintArray(const int *, const int *);
void DiffNumbSearch(const int *, const int *, int *);

int main(int argc, char **argv)
{
	FILE *f; 					//файловая переменная для входного файла
	int var_kol = 0; 			//количество различных чисел
	int arr[MAX_N]; 			//массив целых чисел
	int * const pbegin = arr; 	//указатель на начало массива
	int *pend = arr + MAX_N; 	//указатели на конец массива
	int rc = OK; 				//код ошибки
	
	setbuf(stdout,NULL);
	
	if (argc < 2)
	{
		printf("No input file!\n");
		return CMD_ERR;
	}
	f = fopen(argv[1],"r");
	if (f == NULL)
	{
		printf("File doesn't exists or can't be opened!\n");
		rc = FILE_ERR;
	}
	else
	{
		rc = ReadArray(f, pbegin, &pend);
		if (rc == NO_DATA)
			printf("No input!\n");
		else if (rc == IO_ERR)
			printf("Incorrect input!\n");
		else
		{
			printf("Array: ");
			PrintArray(pbegin,pend);
			DiffNumbSearch(pbegin, pend, &var_kol);
			printf("\nQuantity of various numbers: %d\n",var_kol);
		}
	}
	
	fclose(f);
	return rc;
}


