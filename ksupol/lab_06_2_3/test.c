#include <stdio.h>
#include "array.h"
#include "process.h"

#define OK 0
#define ERR_FILE -1
#define ERR_MASS -2
#define TOO_BIG -3
#define EMPTY -4
#define SIZE 100

void test_ReadArray()
{
	int err_cnt = 0;
	FILE *f;	
	
	// корректные данные
	{
		{
			f = fopen("tests_ReadArray/in_1.txt","r");
			int a[SIZE];
			int* const pa = a;
			int *pb = a+SIZE;
			if (ReadArray(f,pa,&pb) != OK || pb != pa + 1 || *pa != 5)
			{
				err_cnt++;
				
			}
			fclose(f);
		}
		{
			f = fopen("tests_ReadArray/in_2.txt","r");
			int a[SIZE], b[] = {12, 15, 62, 84, 12, 123, 20, 45};
			int* const pa = a;
			int *pb = a+SIZE;
			if (ReadArray(f,pa,&pb) != OK || pb != pa + 8)
			{
				for (int *p = pa, *numb = b; p < pb; p++, numb++)
					if (*p != *numb)
					{
						err_cnt++;
						break;
					}
			}
			fclose(f);
		}
		{
			f = fopen("tests_ReadArray/in_3.txt","r");
			int a[SIZE];
			int b[SIZE];
			for (int i = 0; i<SIZE; i++)
				b[i] = i % 10 + 1;
			int* const pa = a;
			int *pb = a+SIZE;
			if (ReadArray(f,pa,&pb) != TOO_BIG || pb != pa + 100)
			{
				for (int *p = pa, *numb = b; p < pb; p++, numb++)
					if (*p != *numb)
					{
						err_cnt++;
						break;
					}
			}
			fclose(f);
		}
	}
	
	// некорректные элементы массива
	
	{

		{
			f = fopen("tests_ReadArray/in_4.txt","r");
			int a[SIZE];
			int* const pa = a;
			int *pb = a+SIZE;
			if (ReadArray(f,pa,&pb) != ERR_MASS)
				err_cnt++;
			fclose(f);
		}
		{
			f = fopen("tests_ReadArray/in_5.txt","r");
			int a[SIZE];
			int* const pa = a;
			int *pb = a+SIZE;
			if (ReadArray(f,pa,&pb) != ERR_MASS)
				err_cnt++;
			fclose(f);
		}
		{
			f = fopen("tests_ReadArray/in_6.txt","r");
			int a[SIZE];
			int* const pa = a;
			int *pb = a+SIZE;
			if (ReadArray(f,pa,&pb) != ERR_MASS)
				err_cnt++;
			fclose(f);
		}
	}
	printf("%s %s\n",__func__,err_cnt?"FAILED":"OK");
}

void test_process()
{
	int err_cnt = 0;
	//один элемент - положительный
	{
		int a[] = {1};
		if (process(a,a+1) != 1)
			err_cnt++;
	}
	//первый элемент - отрицательный
	{
		int a[] = {-5,2,-1};
		if (process(a,a+3) != -5)
			err_cnt++;
	}
	//все положительные
	{
		int a[] = {1,2,3,4,5};
		if (process(a,a+5) != 153)
			err_cnt++;
	}
	//есть отрицательный, но он не первый
	{
		int a[] = {1,2,-3,4,5};
		if (process(a,a+5) != -3)
			err_cnt++;
	}
	
	printf("%s %s\n",__func__,err_cnt?"FAILED":"OK");
}

int main()
{
	test_ReadArray();
	test_process();
	
	return 0;
}