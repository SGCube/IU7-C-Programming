/**
 * \file main.c
 * \brief Main function
 * \details Source code of programm main function
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iofile.h"
#include "sort.h"

#define OK 0
#define ERR_CMD -1
#define ERR_FILE -2
#define ERR_EMPTY -3
#define ERR_INPUT -4
#define ERR_OUTPUT -5
#define ERR_MEMORY -6
#define NONE_TO_SORT -7
#define ERR_FLAG -8
#define ERR_ARG -9

int main(int argc, char **argv)
{
	FILE *fin = NULL, *fout = NULL;
	int *pb = NULL, *pe = NULL;
	int *pfb = NULL, *pfe = NULL;
	int rc = OK;
	
	if (argc < 3)
	{
		printf("Not enough arguments!\n");
		return ERR_CMD;
	}
	if (argc >= 4 && strcmp(argv[3], "f") != 0)
	{
		printf("Wrong flag argument!\n");
		return ERR_CMD;
	}
	
	fin = fopen(argv[1], "r");
	if (!fin)
	{
		printf("Couldn't open an input file!\n");
		return ERR_FILE;
	}
	fout = fopen(argv[2], "w");
	if (!fout)
	{
		printf("Couldn't open an output file!\n");
		fclose(fout);
		return ERR_FILE;
	}
	
	rc = read_array(fin, &pb, &pe);
	if (rc == ERR_EMPTY)
		printf("File is empty!\n");
	else if (rc == ERR_INPUT)
		printf("Incorrect data!\n");
	else if (rc == ERR_MEMORY)
		printf("Memory allocation error!\n");
	else
	{
		if (argc > 3 && argv[3][0] == 'f')
		{
			rc = key(pb, pe, &pfb, &pfe);
			if (rc == ERR_MEMORY)
				printf("Memory allocation error!\n");
			else if (rc == NONE_TO_SORT)
				printf("No data left for sorting!\n");
			else
			{
				mysort(pfb, pfe - pfb, sizeof(int), compar_int);
				rc = print_array(fout, pfb, pfe);
				if (rc == ERR_OUTPUT)
					printf("Couldn't write data!\n");
				free(pfb);
			}
		}
		else
		{
			mysort(pb, pe - pb, sizeof(int), compar_int);
			rc = print_array(fout, pb, pe);
			if (rc == ERR_OUTPUT)
				printf("Couldn't write data!\n");
		}
		free(pb);
	}
	fclose(fin);
	fclose(fout);
	return rc;
}