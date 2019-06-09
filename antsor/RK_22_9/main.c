#include <stdio.h>
#include "array.h"

#define OK 0
#define CMD_ERR -1
#define NOT_EXIST -2
#define EMPTY_FILE -3
#define AMOUNT_ERR -4
#define IO_ERR -5
#define NOT_ENOUGH -6

#define MAX_SIZE 50

int main(int argc, char **argv)
{
	int rc = OK;
	int x[MAX_SIZE], n;
	
	if (argc < 2)
	{
		printf("No input file!\n");
		return CMD_ERR;
	}
	
	FILE *f = fopen(argv[1],"r");
	if (f == NULL)
	{
		printf("File doesn't exist!\n");
		rc = NOT_EXIST;
	}
	else
	{
		rc = ReadArray(f, x, &n);
		if (rc == EMPTY_FILE)
			printf("File is empty!\n");
		else if (rc == AMOUNT_ERR)
			printf("Amount of elements input error!\n");
		else if (rc == IO_ERR)
			printf("Array elements input error!\n");
		else if (rc == NOT_ENOUGH)
			printf("Not enough array elements!\n");
		else
		{
			printf("Source array:\n");
			PrintArray(x,n);
			SortArray(x,n);
			printf("New array:\n");
			PrintArray(x,n);
		}
	}
	fclose(f);
	
	return rc;
}