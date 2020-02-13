#include <stdio.h>
#include <stdlib.h>
#include "str.h"

#define OK 0
#define ERR_ARG -1
#define ERR_FILE -2
#define ERR_EMPTY -3
#define ERR_ALLOC -4
#define ERR_NOWORDS -5

#define MAX_LEN 100

int main(int argc, char **argv)
{
	int rc = OK;
	int nw = 0;
	char *words = malloc(MAX_LEN * sizeof(char));
	char *txt = malloc(MAX_LEN * sizeof(char));
	*txt = '\0';
	FILE *fin = NULL, *fout = NULL;
	
	if (argc < 3)
	{
		printf("Not enough arguments!\n");
		return ERR_ARG;
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
		return ERR_FILE;
	}
	
	rc = text_read(fin, &txt);
	if (rc == ERR_EMPTY)
		printf("File is empty!\n");
	else if (rc == ERR_ALLOC)
		printf("Memory allocation error!\n");
	else
	{
		nw = find_words(txt, &words);
		if (nw == ERR_ALLOC)
		{
			printf("Memory allocation error!\n");
			rc = ERR_ALLOC;
		}
		else if (nw == 0)
		{
			printf("There is no words!\n");
			rc = ERR_NOWORDS;
		}
		else
			word_times(words, nw, fout);
	}
	
	if (txt)
		free(txt);
	if (words)
		free(words);
	fclose(fin);
	fclose(fout);
	return OK;
}