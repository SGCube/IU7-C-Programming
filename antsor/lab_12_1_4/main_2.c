/**
 * \file main.c
 * \brief Main function
 * \details Source code of programm main function
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "error.h"
#define ERR_LIB -20

typedef int (__cdecl *fn_len_t)(FILE *f);
typedef int (__cdecl *fn_read_t)(FILE *f, int*, int**, int);
typedef int (__cdecl *fn_print_t)(FILE *f, const int*, const int*);
typedef int (__cdecl *fn_avg_t)(const int*, const int*, float*);
typedef int (__cdecl *fn_key_t)(const int*, const int*,
	int *, int **, float);
typedef void (__cdecl *fn_mysort_t)(void*, size_t, size_t,
	int (*)(const void*, const void*));
typedef int (__cdecl *fn_compar_t)(const void*, const void*);
	
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
	HMODULE hlib;
	fn_len_t array_len;
	fn_read_t read_array;
	fn_print_t print_array;
	fn_avg_t arr_avg;
	fn_key_t key;
	fn_mysort_t mysort;
	fn_compar_t compar_int;
	
	hlib = LoadLibrary("arr.dll");
    if (!hlib)
    {
        printf("Can't open library.\n");
        return ERR_LIB;
    }
	
	array_len = (fn_len_t) GetProcAddress(hlib, "array_len");
	read_array = (fn_read_t) GetProcAddress(hlib, "read_array");
	print_array = (fn_print_t) GetProcAddress(hlib, "print_array");
	arr_avg = (fn_avg_t) GetProcAddress(hlib, "arr_avg");
	key = (fn_key_t) GetProcAddress(hlib, "key");
	mysort = (fn_mysort_t) GetProcAddress(hlib, "mysort");
	compar_int = (fn_compar_t) GetProcAddress(hlib, "compar_int");
	
	if (!array_len || !read_array || !print_array || !arr_avg ||
		!key || !mysort)
	{
        printf("Can't load functions.\n");
		FreeLibrary(hlib);
        return ERR_LIB;
    }
	
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
	FreeLibrary(hlib);
	return rc;
}