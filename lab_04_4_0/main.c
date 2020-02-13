/*
Программа, сортирующая массив по возрастанию методом пузырька

Допущения: в качестве целочисленного типа данных используется int
*/
#include <stdio.h>

#define OK 0
#define N_IO_ERROR -2
#define IO_ERROR -1

#define SORTED 1
#define NOT_SORTED 2

#define MAX_N 10

//функция ввода массива
int input_array(int arr[], int *arr_n)
{
	printf("Input number of array elements (<=10): ");
	if (scanf("%d",arr_n) != 1 || *arr_n < 1 || *arr_n > 10)
		return N_IO_ERROR;
	int i = 0;
	printf("Input array: ");
	while(i < *arr_n)
	{
		if (scanf("%d",&arr[i]) != 1)
			return IO_ERROR;
		i++;
	}
	
	return OK;
}

//функция вывода массива
void print_array(int arr[], int arr_n)
{
	if (arr_n == 0)
		printf("empty");
	else
		for (int i = 0; i < arr_n; i++)
			printf("%d ",arr[i]);
	printf("\n");
}

//Функция сортировки
void array_sort(int arr[], int arr_n)
{
	short int is_sorted; //флаг, означающий отсортированность массива
	int temp;
	for (int i = 0; i < arr_n - 1; i++)
	{
		is_sorted = SORTED;
		for (int j = 0; j < arr_n - i - 1; j++)
			if (arr[j] > arr[j+1])
			{
				temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
				is_sorted = NOT_SORTED;
			}
		if (is_sorted == SORTED)
			break;	
	}
}

int main()
{
	setbuf(stdout, NULL);
	
	int arr[MAX_N], arr_numb;
	
	int rc = input_array(arr,&arr_numb);
	
	if (rc == OK)
	{
		printf("Source array: ");
		print_array(arr, arr_numb);
		
		array_sort(arr, arr_numb);
		
		printf("Sorted array: ");
		print_array(arr, arr_numb);
	}
	else if (rc == N_IO_ERROR)
		printf("Array number incorrect input!");
	else
		printf("Incorrect input!");
	
	return rc;
}