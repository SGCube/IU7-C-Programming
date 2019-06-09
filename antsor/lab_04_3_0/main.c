/*
Программа, удаляющая из исходного массива все числа-палиндромы

Допущения: в качестве целочисленного типа данных используется long int
Отрицательные числа не являются палиндромами (знак "-" не ставится в конец)
*/
#include <stdio.h>

#define OK 0
#define N_IO_ERROR -2
#define IO_ERROR -1

#define PALINDROM 1
#define NOT_PALINDROM 2

#define MAX_N 10

//функция ввода массива
int input_array(long int arr[], int *arr_n)
{
	printf("Input number of array elements (<=10): ");
	if (scanf("%d",arr_n) != 1 || *arr_n < 1 || *arr_n > 10)
		return N_IO_ERROR;
	int i = 0;
	printf("Input array: ");
	while(i < *arr_n)
	{
		if (scanf("%ld",&arr[i]) != 1)
			return IO_ERROR;
		i++;
	}
	
	return OK;
}

//функция вывода массива
void print_array(long int arr[], int arr_n)
{
	if (arr_n == 0)
		printf("Array is empty.");
	else
		for (int i = 0; i < arr_n; i++)
			printf("%ld ",arr[i]);
	printf("\n");
}

//Функция, определяющая, является ли число палиндромом
int is_palindrom(long int x)
{
	if (x < 0)
		return NOT_PALINDROM;
	
	long int x_rev = 0, x_temp = x;
	int k = 0; //изначательно кол-во разрядов числа, затем половина от этого
	
	while(x_temp > 0)
	{
		x_rev *= 10;
		x_rev += x_temp % 10;
		x_temp /= 10;
		k++;
	}
	
	if (k % 2 == 0)
		k /= 2;
	else
		k = k/2 + 1;
	
	for(int i = 0; i < k; i++)
	{
		if (x_rev % 10 != x % 10)
			return NOT_PALINDROM;
		x_rev /= 10;
		x /= 10;
	}
	
	return PALINDROM;
}

//функция, удаляющая из массива числа-палиндромы
void delete_palindroms(long int arr[], int *arr_n)
{
	int i = 0;
	while(i < *arr_n)
	{
		if (is_palindrom(arr[i]) == PALINDROM)
		{
			for(int j = i; j < *arr_n - 1; j++)
				arr[j] = arr[j+1];
			*arr_n -= 1;
		}
		else
			i++;
	}
}

int main()
{
	setbuf(stdout, NULL);
	
	long int arr[MAX_N];
	int arr_numb;
	
	int rc = input_array(arr,&arr_numb);
	
	if (rc == OK)
	{
		printf("\nSource array:\n");
		print_array(arr, arr_numb);
		
		delete_palindroms(arr, &arr_numb);
		
		printf("Modified array:\n");
		print_array(arr, arr_numb);
	}
	else if (rc == N_IO_ERROR)
		printf("Array number incorrect input!");
	else
		printf("Incorrect input!");
	
	return rc;
}