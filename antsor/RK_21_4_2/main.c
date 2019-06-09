/*
Программа поиска элемента в последовательности чисел, произведение
которого с предыдущим максимально

Для первого элемента предыдущий равен 1.

Допущения: выбран диапазон значений, определённый типом int.
Программа не проверяет числа, записанные после 0.
*/
#include <stdio.h>

#define OK 0
#define NO_FILE -1
#define IO_ERROR -2
#define NO_NUMBERS -3

//функция поиска при наличии входного файла
int process_file(FILE *, int *, int *);

//функция поиска при отсутствии входного файла
int process_no_file(int *, int *);

int main(int argc, char *argv[])
{
	int rc = OK; //код ошибки
	int numb, numb_pos; //искомый элемент и его позиция
	FILE *f = NULL;
	
	setbuf(stdout, NULL);
	
	if (argc != 2)
		rc = process_no_file(&numb, &numb_pos);
	else
	{
		f = fopen(argv[1],"r");
		if (f == NULL)
		{
			printf("File doesn't exist or can't be opened!\n");
			fclose(f);
			return NO_FILE;
		}
		rc = process_file(f, &numb, &numb_pos);
	}
	
	if (rc == IO_ERROR)
		printf("Incorrect input!\n");
	else if (rc == NO_NUMBERS)
		printf("No integer numbers (except maybe of 0)!\n");
	else
		printf("Number: %d\nPosition: %d\n", numb, numb_pos);
	
	if (f != NULL)
		fclose(f);
	
	return rc;
}

int process_file(FILE *f, int *x_res, int *x_pos)
{
	int pr_cur, pr_max; //произведение текущего с предыдущим и максимальное
	int x_cur, x_prev = 1; //текущий и предыдущий члены последовательности
	int i = 0; //текущая позиция
	
	if (fscanf(f, "%d", &x_cur) == 1)
	{
		if (x_cur == 0)
			return NO_NUMBERS;
		
		pr_max = x_cur;
		*x_res = x_cur;
		*x_pos = 0;
		while(fscanf(f, "%d", &x_cur) == 1)
		{
			if (x_cur == 0)
				return OK;
			i++;
			pr_cur = x_prev * x_cur;
			if (pr_cur > pr_max)
			{
				pr_max = pr_cur;
				*x_res = x_cur;
				*x_pos = i;
			}
			x_prev = x_cur;
		}
		return IO_ERROR;
	}
	
	return NO_NUMBERS;
}

int process_no_file(int *x_res, int *x_pos)
{
	int pr_cur, pr_max = 0; //произведение текущего с предыдущим и максимальное
	int x_cur, x_prev = 1; //текущий и предыдущий члены последовательности
	int i = 0; //текущая позиция
	
	printf("Enter numbers (0 - input end): ");
	while(scanf("%d", &x_cur) == 1)
	{
		if (x_cur == 0)
		{
			if (pr_max == 0)
				return NO_NUMBERS;
			else
				return OK;
		}
		pr_cur = x_prev * x_cur;
		if (pr_max == 0 || pr_cur > pr_max)
		{
			pr_max = pr_cur;
			*x_res = x_cur;
			*x_pos = i;
		}
		x_prev = x_cur;
		i++;
	}
	
	if (pr_max == 0)
		return NO_NUMBERS;
	
	return IO_ERROR;
}