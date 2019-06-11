#include <stdio.h>
#include "str.h"
#include <stdlib.h>

#define MAX 20
#define OK 0
#define ERR -1
#define ERR_INPUT -2
#define ERR_FILE -3
#define EMPTY -4

int main(int argc, char **argv)
{
	int rc = 0;
	int check = 0;
	
	FILE *fin, *fout;
	
	char *line = NULL;
	char words[100][MAX];
	char result[100][MAX];
	int len_arr = 0;
	if (argc < 3)
	{
		printf("Not enough data!\n");
		return ERR_INPUT;
	}
	fin = fopen(argv[1], "r");
	if (!fin)
	{
		printf("Couldn't open input file!\n");
		return ERR_FILE;
	}
	fout = fopen(argv[2], "w");
	if (!fout)
	{
		printf("Couldn't open output file!\n");
		fclose(fin);
		return ERR_FILE;
	}
	char temp;
	check = fscanf(fin, "%c", &temp);
	if (check == EOF)
	{
		printf("File is empty!\n");
		fclose(fin);
		fclose(fout);
		return EMPTY;
	}
	rewind(fin);
	do
	{
		line = malloc(100 * sizeof(char));
		fgets(line, 100, fin);
		sep_words(line, words, &len_arr);
		del(words, &len_arr, result);
		print_to_file(result, len_arr, fout);
		free(line);
	}
	while (!feof(fin));
	fclose(fin);
	fclose(fout);
	return rc;
}