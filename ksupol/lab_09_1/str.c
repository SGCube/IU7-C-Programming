#include <stdio.h>
#include <string.h>
#include "str.h"

int my_strcspn(char *str, char *key)
{
	int i = 0, j = 0;
	int ind = -1;
	while (str[i] != '\0')
	{
		j = 0;
		if (ind == -1)
			while (key[j] != '\0')
			{
				if (str[i] == key[j])
				{
					ind = i;
					break;
				}
				j++;
			}
		else
			break;
		i++;
	}	
	if (ind != -1)
		return ind;
	return i;
}

char *my_strchr(char *str, int sym)
{
	char *res = NULL;
	for (int i = 0; i < my_strlen(str) + 1; i++)
		if (str[i] == sym)
		{
			res = &(str[i]);
			break;
		}
	/*
	do
	{
		if (str[i] == sym)
		{
			res = &(str[i]);
			break;
		}
		i++;
	}
	while (str[i] != '\0');
	*/
	return res;
}

int my_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}