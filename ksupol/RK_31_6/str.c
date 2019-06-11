#include <stdio.h>
#include "str.h"
#include <string.h>

#define MAX 20
#define MAX_LEN 128
#define ERR -1

int my_strlen(char *str)
{
	int len = 0;
	for(char *pc = str; *pc != '\0'; pc++)
		len++;
	return len;
}

void sep_words(char *line, char words[][MAX], int *len_arr)
{
	char temp[MAX];
	int j = 0, k = 0;
	int n = 0;
	int i = -1;
	
	do
	{
		i++;
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
		{
			temp[j] = line[i];
			j++;
			n = 1;
		}
		else if (line[i] == ' ' || line[i] == '\0')
		{
			if (n == 1)
			{
				for (int u = 0; u < j; u++)
					words[k][u] = temp[u];
				words[k][j] = '\0';
				k++;
				n = 0;
				j = 0;
			}
		}
	}
	while (line[i] != '\0');
	*len_arr = k;
}

void print_to_file(char words[][MAX], int len_arr, FILE *f)
{
	for (int i = 0; i < len_arr; i++)
		fprintf(f, "%s ", words[i]);
	fprintf(f, "\n");
}

void del(char words[][MAX], int *len_arr, char result[][MAX])
{
	int flag = 0;
	int k = 0;
	
	for (int i = 0; i < *len_arr; i++)
	{
		flag = 0;
		for (int j = 0; j < i; j++)
			if (strcmp(words[i], words[j]) == 0)
				flag = 1;
		if (flag == 0)
			strcpy(result[k++], words[i]);
	}
	*len_arr = k;
}