/*
Программа, считающая сумму чётных чисел массива

Допущения: в качестве целочисленного типа данных используется int
*/
#include <stdio.h>

#define OK 0
#define N_IO_ERROR -2
#define IO_ERROR -1
#define NO_EVEN 1

#define MAX_N 10

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

int even_sum(int arr[], int arr_n, int *sum)
{
	int rc = NO_EVEN;
	*sum = 0;
	for (int i = 0; i < arr_n; i++)
		if (arr[i] % 2 == 0)
		{
			rc = OK;
			*sum += arr[i];
		}
	
	return rc;
}

int main()
{
	setbuf(stdout, NULL);
	
	int arr[MAX_N];
	int arr_numb, sum;
	
	int rc = input_array(arr,&arr_numb);
	
	if (rc == OK)
	{
		if(even_sum(arr,arr_numb,&sum) == OK)
			printf("Sum = %d\n",sum);
		else
			printf("No even numbers.\n");
	}
	else if (rc == N_IO_ERROR)
		printf("Array number incorrect input!");
	else
		printf("Incorrect input!");
	
	return rc;
}