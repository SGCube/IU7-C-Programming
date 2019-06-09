#include <stdio.h>
#include <assert.h>
#include "array.h"

#define OK 0
#define CMD_ERR -1
#define NOT_EXIST -2
#define EMPTY_FILE -3
#define AMOUNT_ERR -4
#define IO_ERR -5
#define NOT_ENOUGH -6

#define TRUE 1
#define FALSE 0

#define MAX_SIZE 50

int ReadArray(FILE *f, int arr[], int *arr_n)
{
	int scan = fscanf(f, "%d", arr_n);
	if (scan == EOF)
		return EMPTY_FILE;
	if (scan != 1)
		return AMOUNT_ERR;
	if (*arr_n <= 0 || *arr_n > MAX_SIZE)
		return AMOUNT_ERR;
	
	assert(*arr_n > 0 && *arr_n <= MAX_SIZE);
	
	for(int i = 0; i < *arr_n; i++)
	{
		scan = fscanf(f, "%d", &arr[i]);
		if (scan == EOF)
			return NOT_ENOUGH;
		if (scan != 1)
			return IO_ERR;
	}
	
	return OK;
}

void PrintArray(int arr[], int arr_n)
{
	assert(arr != NULL && arr_n > 0);
	for(int i = 0; i < arr_n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int IsUnique(int arr[], int index, int arr_n)
{
	assert(arr != NULL && arr_n > 0 && index >= 0 && index < arr_n);
	
	for(int i = 0; i < arr_n; i++)
		if (i != index && arr[i] == arr[index])
			return FALSE;
		
	return TRUE;
}

int UniqueIndexes(int arr[], int uniq[], int arr_n)
{
	int uniq_n = 0;
	for (int i = 0; i < arr_n; i++)
		if (IsUnique(arr,i,arr_n))
		{
			uniq[uniq_n] = i;
			uniq_n++;
		}
	
	return uniq_n;
}

void SortArray(int arr[], int arr_n)
{
	assert(arr != NULL && arr_n > 0);
	
	int uniq_i[arr_n], uniq_n = 0;
	uniq_n = UniqueIndexes(arr,uniq_i,arr_n);
	
	if (arr_n > 1 && uniq_n > 1)
	{
		short int sorted = TRUE;
		const int *const uend = uniq_i + uniq_n;
		for(int *ui = uniq_i; ui < uend; ui++)
		{
			sorted = TRUE;
			for(int *uj = uniq_i + 1; uj < uend - (ui - uniq_i); uj++)
			{
				if(arr[*uj] < arr[*(uj-1)])
				{
					int temp = arr[*(uj-1)];
					arr[*(uj-1)] = arr[*uj];
					arr[*uj] = temp;
					sorted = FALSE;
				}
			}
			if (sorted)
				break;
		}
	}
}