#include <stdio.h>
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

void test_IsUnique(void)
{
	printf("%s:\n", __func__);
	{
		int a[] = {1};
		int check = (IsUnique(a,0,sizeof(a)/sizeof(a[0])) == TRUE);
		printf("Test#1 %s\n", check ? "OK":"FAILED");
	}
	{
		int a[] = {1, 1};
		int check = (IsUnique(a,1,sizeof(a)/sizeof(a[0])) == FALSE);
		printf("Test#2 %s\n", check ? "OK":"FAILED");
	}
	{
		int a[] = {1, -1, 1};
		int check = (IsUnique(a,2,sizeof(a)/sizeof(a[0])) == FALSE);
		printf("Test#3 %s\n", check ? "OK":"FAILED");
	}
	{
		int a[] = {1, -1, 1};
		int check = (IsUnique(a,1,sizeof(a)/sizeof(a[0])) == TRUE);
		printf("Test#4 %s\n", check ? "OK":"FAILED");
	}
	{
		int a[] = {-1, -2, -3};
		int check = (IsUnique(a,1,sizeof(a)/sizeof(a[0])) == TRUE);
		printf("Test#5 %s\n", check ? "OK":"FAILED");
	}
		
	printf("\n");
}

void test_UniqueIndexes(void)
{
	printf("%s:\n", __func__);
	{
		int check = TRUE;
		int a[] = {1};
		int u[1];
		int uniq[] = {0};
		if (UniqueIndexes(a,u,sizeof(a)/sizeof(a[0])) != 1)
			check = FALSE;
		else
			for(int i = 0; i < 1; i++)
				if (u[i] != uniq[i])
				{
					check = FALSE;
					break;
				}
		
		printf("Test#1 %s\n", check ? "OK":"FAILED");
	}
	{
		int check = TRUE;
		int a[] = {1, 1};
		int u[2];
		if (UniqueIndexes(a,u,sizeof(a)/sizeof(a[0])) != 0)
			check = FALSE;
		
		printf("Test#2 %s\n", check ? "OK":"FAILED");
	}
	{
		int check = TRUE;
		int a[] = {1, 2, 1, 2};
		int u[4];
		if (UniqueIndexes(a,u,sizeof(a)/sizeof(a[0])) != 0)
			check = FALSE;
				
		printf("Test#3 %s\n", check ? "OK":"FAILED");
	}
	{
		int check = TRUE;
		int a[] = {1, -1, -2, 1};
		int u[4];
		int uniq[] = {1, 2};
		if (UniqueIndexes(a,u,sizeof(a)/sizeof(a[0])) != 2)
			check = FALSE;
		else
			for(int i = 0; i < 1; i++)
				if (u[i] != uniq[i])
				{
					check = FALSE;
					break;
				}
		printf("Test#4 %s\n", check ? "OK":"FAILED");
	}
	{
		int check = TRUE;
		int a[] = {-1, -2, -3};
		int u[3];
		int uniq[] = {0, 1, 2};
		if (UniqueIndexes(a,u,sizeof(a)/sizeof(a[0])) != 3)
			check = FALSE;
		else
			for(int i = 0; i < 1; i++)
				if (u[i] != uniq[i])
				{
					check = FALSE;
					break;
				}
				
		printf("Test#5 %s\n", check ? "OK":"FAILED");
	}
		
	printf("\n");
}

void test_SortArray(void)
{
	printf("%s:\n", __func__);
	
	{
		int check = TRUE;
		int a[] = {1};
		int b[] = {1};
		SortArray(a, sizeof(a)/sizeof(a[0]));
		for(int i = 0; i < sizeof(a)/sizeof(a[0]); i++)
			if (a[i] != b[i])
			{
				check = FALSE;
				break;
			}
		
		printf("Test#1 %s\n", check ? "OK":"FAILED");
	}
	{
		int check = TRUE;
		int a[] = {1, 1, 2, 3, 2, 3};
		int b[] = {1, 1, 2, 3, 2, 3};
		SortArray(a, sizeof(a)/sizeof(a[0]));
		for(int i = 0; i < sizeof(a)/sizeof(a[0]); i++)
			if (a[i] != b[i])
			{
				check = FALSE;
				break;
			}
		
		printf("Test#2 %s\n", check ? "OK":"FAILED");
	}
	{
		int check = TRUE;
		int a[] = {1, -1, 1, 2, 3, 2, 3};
		int b[] = {1, -1, 1, 2, 3, 2, 3};
		SortArray(a, sizeof(a)/sizeof(a[0]));
		for(int i = 0; i < sizeof(a)/sizeof(a[0]); i++)
			if (a[i] != b[i])
			{
				check = FALSE;
				break;
			}
		
		printf("Test#3 %s\n", check ? "OK":"FAILED");
	}
	{
		int check = TRUE;
		int a[] = {1, 3, 2, -1, 2, 3};
		int b[] = {-1, 3, 2, 1, 2, 3};
		SortArray(a, sizeof(a)/sizeof(a[0]));
		for(int i = 0; i < sizeof(a)/sizeof(a[0]); i++)
			if (a[i] != b[i])
			{
				check = FALSE;
				break;
			}
		
		printf("Test#4 %s\n", check ? "OK":"FAILED");
	}
	{
		int check = TRUE;
		int a[] = {-1, -3, -2, 1, 0};
		int b[] = {-3, -2, -1, 0, 1};
		SortArray(a, sizeof(a)/sizeof(a[0]));
		for(int i = 0; i < sizeof(a)/sizeof(a[0]); i++)
			if (a[i] != b[i])
			{
				check = FALSE;
				break;
			}
		
		printf("Test#5 %s\n", check ? "OK":"FAILED");
	}
		
	printf("\n");
}

int main()
{
	test_IsUnique();
	test_UniqueIndexes();
	test_SortArray();
	return 0;
}