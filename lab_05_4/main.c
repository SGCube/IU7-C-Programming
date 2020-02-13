/*
ѕрограмма, опред€л€юща€ количество различных целых чисел в файле

ƒопущени€: в качестве целочисленного типа данных используетс€ тип int
Ёлементов не больше 100. Ёлементы, введЄнные после 100ого, не учитываютс€.
*/
#include <stdio.h>

#define OK 0
#define CMD_ERR -1
#define FILE_ERR -2
#define NO_DATA -3
#define IO_ERR -4

#define MAX_N 100

//прототип функции чтени€ массива из файла
int ReadArray(FILE *f, int * const pbegin, int **pend);

//прототип функции вывода массива на экран
void PrintArray(const int *pbegin, const int *pend);

//протототип функции, определ€ющей количество различных чисел
void DiffNumbSearch(const int *pbegin, const int *pend, int *kol);

int main(int argc, char **argv)
{
	FILE *f; 					//файлова€ переменна€ дл€ входного файла
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

//функци€ чтени€ массива из файла
int ReadArray(FILE *f, int * const pbegin, int ** pend)
{
	int *pcur = pbegin; //указатель на текущий элемент
	int sc; //признак ввода числа
	while(pcur < *pend)
	{
		sc = fscanf(f, "%d", pcur);
		if (sc != 1)
		{
			if (sc == EOF)
			{
				if (pcur == pbegin)
					return NO_DATA;
				else
				{
					*pend = pcur;
					return OK;
				}
			}
			return IO_ERR;
		}
		pcur++;
	}
	printf("Array overflow! Only first 100 numbers were handled.\n");
	return OK;
}

//функци€ вывода массива на экран
void PrintArray(const int *pbegin, const int *pend)
{
	const int *pcur = pbegin; //указатель на текущий элемент
	
	while(pcur < pend)
	{
		printf("%d ", *pcur);
		pcur++;
	}
}

//функци€, определ€юща€ количество различных чисел
void DiffNumbSearch(const int *pbegin, const int *pend, int *kol)
{
	*kol = 1;
	const int *pcomp = pbegin + 1;	//указатель на элемент сравнени€
	//найдено ли совпадающее число со сравниваемым (0 - не найдено)
	short int flag = 0; 
	const int *pcur = pcomp - 1; //указатель на текущий элемент
	while(pcomp < pend)
	{
		pcur = pcomp - 1;
		flag = 0;
		while(pcur >= pbegin && flag == 0)
		{
			if (*pcur == *pcomp)
				flag = 1;
			pcur--;
		}
		if (flag == 0)
			*kol += 1;
		pcomp++;
	}
}
