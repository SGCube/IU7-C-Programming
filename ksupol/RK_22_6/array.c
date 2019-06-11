#include <stdio.h>
#include <assert.h>
#include "array.h"

#define OK 0
#define ERR_AMOUNT -1
#define ERR_ARRAY -2
#define NO_ARRAY -3
#define ERR_NO_FILE -4
#define ERR_NO_INPUT -5
#define EMPTY -6
#define SIZE 100

int ReadArray(FILE *f, int *am, int a[])
{
	int rc = OK;
	assert(f != NULL && am != NULL && a != NULL);
	
	int check = fscanf(f,"%d",am);
	if (check == 0)
		return ERR_AMOUNT;
	else if (check == EOF)
		return EMPTY;
	else if (*am <= 0 || *am > SIZE)
		return ERR_AMOUNT;
	for (int i = 0; i<*am; i++)
	{
		check = fscanf(f,"%d",&a[i]);
		if (check == 0)
			return ERR_ARRAY;
		else if (check == EOF)
			return NO_ARRAY;
	}
	
	return rc;
}


int PrintArray(int am, int a[])
{
	assert(am >=0 && a != NULL);
	if (am == 0)
		return 0;
	for (int i=0; i<am;i++)
	printf("%d ",a[i]);
	printf("\n");
	
	return 1;
}

void ChangeArray(int *am, int a[], int b[])
{
	b[1] = a[0];
	b[0] = 0;
	for (int i = 2; i < *am; i++)
	{
		b[i] = 0;
	}
	for (int i = 2; i<*am; i++)
	{
		for (int j = i-1; j>-1; j--)
		{
			b[i] += a[j];
		}
	}
	
}
