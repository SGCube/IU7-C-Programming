#include <stdio.h>
#include "array.h"

#define SIZE 100

void test_ChangeArray()
{
	{
		int err_cnt = 1;
		int a[] = {1,2,3,4}, b[] = {0,1,3,6,10}, c[SIZE];
		int am = 4;
		ChangeArray(&am,a,c);
		for (int i=0; i<4; i++)
		{
			if (c[i] != b[i])
				err_cnt++;
		}
		printf("test_1: %s\n", err_cnt?"OK":"FAILED");
	}
	{
		int err_cnt = 1;
		int a[] = {0,0,0,0}, b[] = {0,0,0,0}, c[SIZE];
		int am = 4;
		ChangeArray(&am,a,c);
		for (int i=0; i<4; i++)
		{
			if (c[i] != b[i])
				err_cnt++;
		}
		printf("test_2: %s\n", err_cnt?"OK":"FAILED");
	}
	{
		int err_cnt = 1;
		int a[] = {1}, b[] = {0}, c[SIZE];
		int am = 1;
		ChangeArray(&am,a,c);
		for (int i=0; i<1; i++)
		{
			if (c[i] != b[i])
				err_cnt++;
		}
		printf("test_3: %s\n", err_cnt?"OK":"FAILED");
	}
	{
		int err_cnt = 1;
		int a[] = {-5,5}, b[] = {0,0}, c[SIZE];
		int am = 1;
		ChangeArray(&am,a,c);
		for (int i=0; i<1; i++)
		{
			if (c[i] != b[i])
				err_cnt++;
		}
		printf("test_4: %s\n", err_cnt?"OK":"FAILED");
	}
	{
		int err_cnt = 1;
		int a[] = {1,-5,-2}, b[] = {0,1,-4}, c[SIZE];
		int am = 3;
		ChangeArray(&am,a,c);
		for (int i=0; i<3; i++)
		{
			if (c[i] != b[i])
				err_cnt++;
		}
		printf("test_5: %s\n", err_cnt?"OK":"FAILED");
	}
	printf("\n");
}
int main()
{
	test_ChangeArray();
	return 0;
}