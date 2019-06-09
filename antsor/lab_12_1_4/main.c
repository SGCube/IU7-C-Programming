/**
 * \file main.c
 * \brief Main function
 * \details Source code of programm main function
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "arr_io.h"
#include "arr_sort.h"

void errmsg(int rc)
{
	switch (rc)
	{
		case ERR_CMD:
			printf("Not enough arguments!\n");
			break;
		case ERR_FILE:
			printf("Couldn't open a file!\n");
			break;
		case ERR_EMPTY:
			printf("File is empty!\n");
			break;
		case ERR_INPUT:
			printf("Incorrect data!\n");
			break;
		case ERR_OUTPUT:
			printf("Couldn't write data!\n");
			break;
		case ERR_MEMORY:
			printf("Memory allocation error!\n");
			break;
		case NONE_TO_SORT:
			printf("No data left for sorting!\n");
			break;
		case ERR_FLAG:
			printf("Wrong flag argument!\n");
			break;
		case ERR_ARG:
			printf("Argument error!\n");
			break;
		case OK:
			break;
		default:
			printf("Unknown error!\n");
	}
}

int main(int argc, char **argv)
{
	FILE *fin = NULL, *fout = NULL;
	int *pb = NULL, *pe = NULL;
	int *pfb = NULL, *pfe = NULL;
	int rc = OK, n = 0;
	
	if (argc < 3)
	{
		errmsg(ERR_CMD);
		return ERR_CMD;
	}
	if (argc >= 4 && strcmp(argv[3], "f") != 0)
	{
		errmsg(ERR_FLAG);
		return ERR_FLAG;
	}
	
	fin = fopen(argv[1], "r");
	if (!fin)
	{
		errmsg(ERR_FILE);
		return ERR_FILE;
	}
	fout = fopen(argv[2], "w");
	if (!fout)
	{
		errmsg(ERR_FILE);
		fclose(fin);
		return ERR_FILE;
	}
	
	rc = array_len(fin);
	if (rc <= 0)
	{
		errmsg(rc);
		fclose(fin);
		fclose(fout);
		return rc;
	}
	
	n = rc;
	pb = malloc(n * sizeof(int));
	if (!pb)
	{
		errmsg(ERR_MEMORY);
		fclose(fin);
		fclose(fout);
		return ERR_MEMORY;
	}
		
	rewind(fin);
	rc = read_array(fin, pb, &pe, n);
	if (rc < 0)
	{
		errmsg(rc);
		fclose(fin);
		fclose(fout);
		if (pb)
			free(pb);
		return rc;
	}
	
	if (argc > 3 && argv[3][0] == 'f')
	{
		float avg;
		n = arr_avg(pb, pe, &avg);
		if (n <= 0)
		{
			rc = n;
			if (rc == 0)
				rc = NONE_TO_SORT;
			errmsg(rc);
			fclose(fin);
			fclose(fout);
			free(pb);
			return rc;
		}
		
		pfb = calloc(n, n * sizeof(int));
		if (!pfb)
		{
			errmsg(ERR_MEMORY);
			fclose(fin);
			fclose(fout);
			free(pb);
			return ERR_MEMORY;
		}
		
		rc = key(pb, pe, pfb, &pfe, avg);
		if (rc == OK)
		{
			mysort(pfb, pfe - pfb, sizeof(int), compar_int);
			rc = print_array(fout, pfb, pfe);
		}
		free(pfb);
	}
	else
	{
		mysort(pb, pe - pb, sizeof(int), compar_int);
		rc = print_array(fout, pb, pe);
	}
	errmsg(rc);
	free(pb);
	fclose(fin);
	fclose(fout);
	return rc;
}