/*
Программа, формирующая новый массив из чисел исходного, которые
больше среднего арифметического элементов исходного

Допущения: в качестве целочисленного типа данных используется int
*/
#include <stdio.h>

#define OK 0
#define N_IO_ERROR -2
#define IO_ERROR -1

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

//Функция, формирующая новый массив
void array_form(int arr[], int arr_n, int new_arr[], int *new_n)
{
	*new_n = 0;
	int sum = 0;
	float avg = 0;
	
	for (int i = 0; i < arr_n; i++)
		sum += arr[i];
	
	avg = (float) sum / arr_n;

	for (int i = 0; i < arr_n; i++)
		if (arr[i] > avg)
		{
			new_arr[*new_n] = arr[i];
			*new_n += 1;
		}
}

int main()
{
	setbuf(stdout, NULL);
	
	int arr[MAX_N], arr_new[MAX_N];
	int arr_numb, new_arr_numb;
	
	int rc = input_array(arr,&arr_numb);
	
	if (rc == OK)
	{
		array_form(arr, arr_numb, arr_new, &new_arr_numb);
		printf("Source array: ");
		print_array(arr, arr_numb);
		printf("New array: ");
		print_array(arr_new, new_arr_numb);
	}
	else if (rc == N_IO_ERROR)
		printf("Array number incorrect input!");
	else
		printf("Incorrect input!");
	
	return rc;
}