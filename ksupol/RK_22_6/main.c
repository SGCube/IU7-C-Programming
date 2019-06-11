#include <stdio.h>
#include "array.h"

#define OK 0
#define ERR_AMOUNT -1
#define ERR_ARRAY -2
#define NO_ARRAY -3
#define ERR_NO_INPUT -5
#define EMPTY -6
#define SIZE 100

int main(int argc, char **argv)
{
	FILE *f;
	int a[SIZE], b[SIZE];
	int am, rc;
	
	if (argc < 2)
	{
		printf("No file name!\n");
		return ERR_NO_INPUT;
	}
	else
	{
		f = fopen(argv[1],"r");
		if (f == NULL)
			printf("No such file!\n");
		else
		{
			rc = ReadArray(f,&am,a);
			if (rc == ERR_AMOUNT)
				printf("Amount of array is incorrect!\n");
			else if (rc == ERR_ARRAY)
				printf("Array is incorrect!\n");
			else if (rc == NO_ARRAY)
				printf("Not enough elements\n");
			else if (rc == EMPTY)
				printf("File is empty!\n");
			else
			{
				printf("Source array:\n");
				PrintArray(am,a);
				ChangeArray(&am, a, b);
				printf("Result array:\n");
				PrintArray(am,b);
			}
		}
	}
	fclose(f);
	return rc;
}