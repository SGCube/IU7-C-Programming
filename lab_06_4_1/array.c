#include <stdio.h>

#define OK 0
#define CMD_ERR -1
#define FILE_ERR -2
#define NO_DATA -3
#define IO_ERR -4

//функция чтения массива из файла
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

//функция вывода массива на экран
void PrintArray(const int *pbegin, const int *pend)
{
	const int *pcur = pbegin; //указатель на текущий элемент
	
	while(pcur < pend)
	{
		printf("%d ", *pcur);
		pcur++;
	}
}

//функция, определяющая количество различных чисел
void DiffNumbSearch(const int *pbegin, const int *pend, int *kol)
{
	*kol = 1;
	const int *pcomp = pbegin + 1;	//указатель на элемент сравнения
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