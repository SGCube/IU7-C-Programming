#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "filework.h"
#include "errcode.h"

int main(int argc, char **argv)
{
	int rc = OK;
	FILE *fin = NULL, *fout = NULL;
	short int sid = 4, rid = 5;
	char ch;
	
	if (argc < 7)
	{
		fprintf(stderr, "Not enough arguments!\n");
		return ERR_ARG;
	}
	
	if (my_strcmp(argv[3], "-s") == 0)
	{
		sid = 4;
		if (my_strcmp(argv[5], "-r") == 0)
			rid = 6;
		else
		{
			fprintf(stderr, "Flag error!\n");
			return ERR_FLAG;
		}
	}
	else if (my_strcmp(argv[3], "-r") == 0)
	{
		rid = 4;
		if (my_strcmp(argv[5], "-s") == 0)
			sid = 6;
		else
		{
			fprintf(stderr, "Flag error!\n");
			return ERR_FLAG;
		}
	}
	else
	{
		fprintf(stderr, "Flag error!\n");
		return ERR_FLAG;
	}
	
	fin = fopen(argv[1], "r");
	if (!fin)
	{
		fprintf(stderr, "Couldn't open an input file!\n");
		return ERR_FILE;
	}
	
	fout = fopen(argv[2], "w");
	if (!fout)
	{
		fprintf(stderr, "Couldn't open an output file!\n");
		fclose(fin);
		return ERR_FILE;
	}
	
	fscanf(fin, "%c", &ch);
	if (feof(fin))
	{
		fprintf(stderr, "Input file is empty!\n");
		fclose(fin);
		fclose(fout);
		return ERR_EMPTY;
	}
	rewind(fin);
	
	rc = txt_replace(fin, fout, argv[sid], argv[rid]);
	if (rc == ERR_ALLOC)
		fprintf(stderr, "Memory allocation error!\n");
	else if (rc == ERR_INPUT)
		fprintf(stderr, "Input error!\n");
	
	fclose(fin);
	fclose(fout);
	return rc;
}