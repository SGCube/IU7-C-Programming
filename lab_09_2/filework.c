#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "mystring.h"
#include "filework.h"
#include "errcode.h"

int txt_replace(FILE *fin, FILE *fout, char *strs, char *strr)
{
	assert(fin && fout);
	assert(strs && strr);
	char *str1 = malloc(MEMORY_BLOCK * sizeof(char));
	ssize_t n = MEMORY_BLOCK;
	ssize_t rc = OK;
	
	while (!feof(fin) && rc != -1)
	{
		char *str2 = NULL;
		rc = my_getline(&str1, &n, fin);
		if (rc != -1)
		{
			str2 = str_replace(str1, strs, strr);
			if (!str2)
			{
				free(str1);
				return ERR_ALLOC;
			}
			fprintf(fout, "%s", str2);
		}
		if (str2)
			free(str2);
	}
	if (str1)
		free(str1);
	return OK;
}