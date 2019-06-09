#include <stdio.h>
#include <assert.h>
#include "array.h"

#define OK 0
#define TOO_MANY 1
#define FILE_ERR -2
#define NO_DATA -3
#define IO_ERR -4

#define MAX_N 100

void Test_ReadArray(void)
{
	int err_cnt = 0;
	//пустой файл
	{
		int arr[MAX_N];
		int * const pa = arr;
		int *pb = arr + MAX_N;
		FILE *f0 = fopen("tests_read/in_0.txt","r");
		assert(f0);
		
		if (ReadArray(f0, pa, &pb) != NO_DATA)
			err_cnt++;
	}
	//некорректные данные
	{
		int arr[MAX_N];
		int * const pa = arr;
		int *pb = arr + MAX_N;
		
		FILE *f1 = fopen("tests_read/in_1.txt","r");
		FILE *f2 = fopen("tests_read/in_2.txt","r");
		
		
		assert(f1 && f2);
		
		if (ReadArray(f1, pa, &pb) != IO_ERR)
			err_cnt++;
		if (ReadArray(f2, pa, &pb) != IO_ERR)
			err_cnt++;
	}
	//корректные данные
	{
		int arr[MAX_N];
		int * const pa = arr;
		int *pb = arr + MAX_N;
		int arr1[] = {1};
		int arr2[] = {1, 2, 3, 4, 5};
		
		FILE *f3 = fopen("tests_read/in_3.txt","r");
		FILE *f4 = fopen("tests_read/in_4.txt","r");
		
		assert(f3 && f4);
		
		//одно число
		if (ReadArray(f3, pa, &pb) != OK || pb != pa + 1)
			err_cnt++;
		else
		{
			for(int *pcur = pa, i = 0; pcur < pb; pcur++, i++)
			{
				if (*pcur != arr1[i])
				{
					err_cnt++;
					break;
				}
			}
		}
		
		//несколько чисел
		pb = arr + MAX_N;
			
		if (ReadArray(f4, pa, &pb) != OK || pb != pa + 5)
			err_cnt++;
		else
		{
			for(int *pcur = pa, i = 0; pcur < pb; pcur++, i++)
			{
				if (*pcur != arr2[i])
				{
					err_cnt++;
					break;
				}
			}
		}
	}
	//больше MAX_N
	{
		int arr[MAX_N];
		int * const pa = arr;
		int *pb = arr + MAX_N;
		int arr5[MAX_N];
		for (int i = 1; i <= MAX_N; i++)
		{
			if (i % 10 == 0)
				arr5[i-1] = -10;
			else
				arr5[i-1] = i % 10;
		}
		
		FILE *f5 = fopen("tests_read/in_5.txt","r");
		
		assert(f5);
		
		if (ReadArray(f5, pa, &pb) != TOO_MANY || pb != pa + 100)
			err_cnt++;
		else
		{
			for(int *pcur = pa, *pcur0 = arr5; pcur < pb; pcur++, pcur0++)
			{
				if (*pcur != *pcur0)
				{
					err_cnt++;
					break;
				}
			}
		}
	}
	
	printf("%s %s\n",__func__,err_cnt?"FAILED":"OK");
}

void Test_DiffNumbSearch(void)
{
	int err_cnt = 0;
	
	{
		int arr[] = {1};
		int * const pa = arr;
		int * const pb = arr + 1;
		int kol;
		DiffNumbSearch(pa, pb, &kol);
		if (kol != 1)
			err_cnt++;
	}
	{
		int arr[] = {1,1,1,1,1,1,1,1,1,1,1};
		int * const pa = arr;
		int * const pb = arr + 11;
		int kol;
		DiffNumbSearch(pa, pb, &kol);
		if (kol != 1)
			err_cnt++;
	}
	{
		int arr[] = {-1,1,-1,1,-1,1,-1,1};
		int * const pa = arr;
		int * const pb = arr + 8;
		int kol;
		DiffNumbSearch(pa, pb, &kol);
		if (kol != 2)
			err_cnt++;
	}
	{
		int arr[] = {1,2,3,4,5,6,7,8,9};
		int * const pa = arr;
		int * const pb = arr + 9;
		int kol;
		DiffNumbSearch(pa, pb, &kol);
		if (kol != 9)
			err_cnt++;
	}
	
	printf("%s %s\n",__func__,err_cnt?"FAILED":"OK");
}


int main()
{
	Test_ReadArray();
	Test_DiffNumbSearch();
	return 0;
}