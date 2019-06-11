#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define OK 0
#define ERR_ARG -1
#define NO_OUTPUT -2
#define ERR_MALLOC -3
#define EMPTY_FILE -4
#define WRONG_ELEMENT -5
#define ERR_PRINT -6
#define ERR_FILE -7
#define NOTHING_AFTER_F -8
#define ERR -9
#define ERR_LIB -10
#define ERR_FUN -11

typedef int (__cdecl *fn_readarr_t)(FILE *, int **, int **);
typedef int (__cdecl *fn_printarr_t)(FILE *, const int *, const int *);
typedef int (__cdecl *fn_calc_amount_t)(const int *, const int *);
typedef int (__cdecl *fn_key_t)(const int *, const int *, int *, int **, int );
typedef void (__cdecl *fn_mysort_t)(void *, size_t , size_t ,
	int (*)(const void *, const void *));
typedef int (__cdecl *fn_cmpint_t)(const void *, const void *);

int main(int argc, char **argv)
{
	HMODULE hlib;
    fn_readarr_t readarr;
    fn_printarr_t printarr;
	fn_calc_amount_t calc_amount;
	fn_key_t key;
	fn_mysort_t mysort;
	fn_cmpint_t cmpint;
	
	FILE *f, *g;
	int rc = OK;
	int *pa = NULL, *pb = NULL;
	int *pa_new = NULL, *pb_new = NULL;
	int am;
	
	hlib = LoadLibrary("arr.dll");
    if (!hlib)
    {
        printf("Cannot open library.\n");
        return ERR_LIB;
    }
	readarr = (fn_readarr_t) GetProcAddress(hlib, "readarr");
	printarr = (fn_printarr_t) GetProcAddress(hlib, "printarr");
	calc_amount = (fn_calc_amount_t) GetProcAddress (hlib, "calc_amount");
	key = (fn_key_t) GetProcAddress (hlib, "key");
	mysort = (fn_mysort_t) GetProcAddress (hlib, "mysort");
	cmpint = (fn_cmpint_t) GetProcAddress (hlib, "cmpint");
	
	if (!readarr || !printarr || !calc_amount || !key || !mysort)
	{
		printf("Cannot load function!\n");
		return ERR_FUN;
	}
  
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
				am = calc_amount(pa, pb);
				if (am == NOTHING_AFTER_F)
					printf("Empty array after filter!\n");
				else
				{
					pa_new = calloc(am, am * sizeof(int));
					if (!pa_new)
					{
						printf("Memory allocation error!\n");
						return ERR;
					}
					rc = key(pa, pb, pa_new, &pb_new, am);
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