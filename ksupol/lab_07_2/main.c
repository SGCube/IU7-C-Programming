#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

#define OK 0
#define ERR_ARG -1
#define NO_OUTPUT -2
#define ERR_MALLOC -3
#define EMPTY_FILE -4
#define WRONG_ELEMENT -5
#define ERR_PRINT -6
#define ERR_FILE -7
#define NOTHING_AFTER_F -8

int main(int argc, char **argv)
{
	FILE *f, *g;
	int rc = OK;
	int *pa = NULL, *pb = NULL;
	int *pa_new = NULL, *pb_new = NULL;
	
	if (argc < 2)
	{
		printf("No names of input and output files!\n");
		return ERR_ARG;
	}
	else if (argc < 3)
	{
		printf("No output file name!\n");
		return ERR_ARG;
	}
	if (argc >= 4 && strcmp(argv[3], "f") != 0)
	{
		printf("Error fourth argument!\n");
		return ERR_ARG;
	}
		
	f = fopen(argv[1], "r");
	g = fopen(argv[2], "w");
	if (f == NULL && g != NULL)
	{
		printf("Input file doesn't exist!\n");
		rc = ERR_FILE;
		fclose(g);
	}
	else if (f == NULL && g == NULL)
	{
		printf("Input file doesn't exist and couldn't make output file!\n");
		rc = ERR_FILE;
	}
	else if (f != NULL && g == NULL)
	{
		printf("Couldn't make output file!\n");
		rc = ERR_FILE;
		fclose(f);
	}
	else 
	{
		rc = readarr(f, &pa, &pb);
		if (rc == EMPTY_FILE)
			printf("Input file is empty!\n");
		else if (rc == WRONG_ELEMENT)
			printf("Wrong element of array!\n");
		else if (rc == ERR_MALLOC)
			printf("Memory allocation error!\n");
		else
		{
			if (argc >= 4)
			{
				rc = key(pa, pb, &pa_new, &pb_new);
				if (rc == NOTHING_AFTER_F)
					printf("Empty array after filter!\n");
				else if (rc == ERR_MALLOC)
					printf("Memory allocation error!\n");
				else
				{
					mysort(pa_new, pb_new - pa_new, sizeof(int), cmpint);
					rc = printarr(g, pa_new, pb_new);
					if (rc == ERR_PRINT)
						printf("Couldn't print array in file!\n");
					free(pa_new);
				}
			}
			else
			{
				mysort(pa, pb - pa, sizeof(int), cmpint);
				rc = printarr(g, pa, pb);
				if (rc == ERR_PRINT)
					printf("Couldn't print array in file!\n");
			}
			free(pa);	
		}
		fclose(f);
		fclose(g);		
	}

	return rc;
}