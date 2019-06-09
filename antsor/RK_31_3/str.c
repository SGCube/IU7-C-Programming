#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "str.h"

#define OK 0
#define ERR_ARG -1
#define ERR_FILE -2
#define ERR_EMPTY -3
#define ERR_ALLOC -4

#define MAX_LEN 100

int text_read(FILE *f, char **txt)
{
	assert(f);
	char str[MAX_LEN];
	while(fgets(str, MAX_LEN, f))
	{
		char *t = realloc(*txt, (strlen(*txt) + strlen(str)) * sizeof(char));
		if (!t)
			return ERR_ALLOC;
		*txt = t;
		strcat(*txt, str);
	}
	if (**txt == '\0')
		return ERR_EMPTY;
	return OK;
}

int find_words(char *txt, char **words)
{
	assert(txt);
	char str[MAX_LEN];
	if (!*words)
		*words = malloc(MAX_LEN * sizeof(char));
	int nw = 0;
	int i = 0, j = 0;
	do
	{
		if ((txt[i] != ' ' && txt[i] != ',' && txt[i] != '.' &&
			txt[i] != ';' && txt[i] != '\n' && txt[i] != '\0'))
			str[j++] = txt[i];
		else if (j != 0)
		{
			str[j] = '\0';
			strcpy(*words + nw * MAX_LEN, str);
			nw++;
			char *t = realloc(*words, (nw + 1) * MAX_LEN * sizeof(char));
			if (!t)
				return ERR_ALLOC;
			*words = t;
			j = 0;
		}	
	}
	while (txt[i++] != '\0');
	
	return nw;
}

void word_times(char *words, int nw, FILE *f)
{
	assert(f);
	assert(words);
	assert(nw > 0);
	int i = 0, k = 0;
	char *pw = words;
	char *pcmp = words;
	char *pend = words + nw * MAX_LEN;
	while (i < nw)
	{
		pw = words + i * MAX_LEN;
		if (strlen(pw) > 0)
		{
			fprintf(f, "%s", pw);
			pcmp = pw + MAX_LEN;
			k = 1;
			while (pcmp < pend)
			{
				if (strcmp(pw, pcmp) == 0)
				{
					k++;
					*pcmp = '\0';
				}
				pcmp += MAX_LEN;
			}
			fprintf(f, "\t%d\n", k);
		}
		i++;
	}
}
