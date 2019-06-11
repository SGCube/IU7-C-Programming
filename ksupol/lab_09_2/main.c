#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "str.h"

#define MAX_LEN 128
#define OK 0
#define ERR -1
#define ERR_FILE -2
#define ERR_MAL -3
#define ERR_G -4

int main(int argc, char **argv)
{
	size_t rc = 0;
	FILE *f, *g;
	int len = 0;
	char *line_p = NULL;
	char *str = NULL;
	char ch;
	
	setbuf(stdout, NULL);
	if (argc < 7)
	{
		printf("Not enough data!\n");
		return ERR;
	}
	f = fopen(argv[1], "r");
	if (!f)
	{
		printf("Couldn't open input file!\n");
		return ERR_FILE;
	}
	g = fopen(argv[2], "w");
	if (!g)
	{
		fclose(f);
		printf("Couldn't open output file!\n");
		return ERR_FILE;
	}
	if (my_strcmp(argv[3], "-s") != 0)
	{
		printf("Wrong key to search!\n");
		rc = ERR;
	}
	else if (my_strcmp(argv[5], "-r") != 0)
	{
		printf("Wrong key to replace!\n");
		rc = ERR;
	}
	else if (fscanf(f, "%c", &ch) == EOF)
	{
		printf("File is empty!\n");
		rc = ERR;
	}	
	else
	{
		rewind(f);
		while (!feof(f) && rc != -1)
		{
			rc = my_getline(&line_p, &len, f);
			if (rc != -1)
			{
				str = str_replace(line_p, argv[4], argv[6]);
				if (!str)
				{
					free(line_p);
					fclose(f);
					fclose(g);
					return ERR_MAL;
				}
				fprintf(g, "%s", str);
				free(str);
			}
		}
		if (line_p != NULL)
			free(line_p);
		rc = OK;
	}
	fclose(f);
	fclose(g);
    return rc;
}