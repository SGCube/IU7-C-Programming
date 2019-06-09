#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "gshow_f.h"
#include "list_u.h"
#include "error.h"

#define MEMORY_BLOCK 16

ssize_t my_getline(char **lineptr, ssize_t *n, FILE *stream)
{
	if (stream == NULL || lineptr == NULL || n == NULL)
		return -1;
	if (*n == 0 || *lineptr == NULL)
	{
		*lineptr = malloc(MEMORY_BLOCK * sizeof(char));
		*n = MEMORY_BLOCK;
	}
	
	ssize_t len = 0;
	char buff[MEMORY_BLOCK];
	char *ptr = *lineptr;
	char *t;
	ssize_t buff_len = 0;

	do
	{
		if (fgets(buff, MEMORY_BLOCK, stream) == NULL)
			return -1;
		buff_len = strlen(buff);
		if (len + buff_len + 1 > *n)
		{
			t = (char *)realloc(*lineptr,
				(len + MEMORY_BLOCK) * sizeof(char));
			if (!t)
				return -1;
			*lineptr = t;
			*n = len + MEMORY_BLOCK;
		}
		ptr = *lineptr + len;
		len += buff_len;
		for (const char *pc = buff; *pc != '\0'; pc++, ptr++)
			*ptr = *pc;
	}
	while (!feof(stream) && buff[buff_len - 1] != '\n');
	
	if (len == 0)
		return -1;
	(*lineptr)[len] = '\0';
	*n = len + 1;
	return len;
}

int read_list(gshow_t **head, FILE *f)
{
	assert(f && head);
	
	// проверка на пустоту файла
	long int begin = ftell(f);
    fseek(f, 0, SEEK_END);
    if (begin == ftell(f))
        return ERR_EMPTY;
    fseek(f, 0, SEEK_SET);
	
	// объявление переменных для полей
	char *name = NULL, *year = NULL, *country = NULL, *genre = NULL;
	int prem_y = 0, end_y = 0;
	
	// объявление временных переменных для чтения
	char *str = NULL;
	ssize_t size = 0, len = 0;
	unsigned char field = 0;
	
	// чтение файла
	do
	{
		// обнуление временных переменных чтения
		str = NULL;
		size = 0;
		len = 0;
		field = 0;
		
		// чтение строки файла (записи)
		len = my_getline(&str, &size, f);
		if (len == -1)
		{
			if (str)
				free(str);
			return ERR_MEMORY;
		}
		
		// "разделение" записи на поля
		char *pword = strtok(str, "\n;");
		while (pword)
		{
			switch (field)
			{
				// название
				case 0:
					name = malloc(strlen(pword) + 1);
					if (!name)
					{
						free(str);
						return ERR_MEMORY;
					}
					strcpy(name, pword);
					break;
				// год премьеры
				case 1:
					year = malloc(strlen(pword) + 1);
					if (!year)
					{
						free(str);
						free(name);
						return ERR_MEMORY;
					}
					strcpy(year, pword);
					prem_y = atoi(year);
					free(year);
					if (prem_y < 1900)
					{
						free(str);
						free(name);
						return ERR_INPUT;
					}
					break;
				// год последнего сезона
				case 2:
					year = malloc(strlen(pword) + 1);
					if (!year)
					{
						free(str);
						free(name);
						return ERR_MEMORY;
					}
					strcpy(year, pword);
					end_y = atoi(year);
					free(year);
					if (end_y < prem_y)
					{
						free(str);
						free(name);
						return ERR_INPUT;
					}
					break;
				// страна-производитель
				case 3:
					country = malloc(strlen(pword) + 1);
					if (!country)
					{
						free(str);
						free(name);
						return ERR_MEMORY;
					}
					strcpy(country, pword);
					break;
				// жанр
				case 4:
					genre = malloc(strlen(pword) + 1);
					if (!genre)
					{
						free(str);
						free(name);
						free(country);
						return ERR_MEMORY;
					}
					strcpy(genre, pword);
					break;
				// лишнее поле
				default:
					free(str);
					free(name);
					free(country);
					free(genre);
					return ERR_FORMAT;
			}
			
			pword = strtok(NULL, "\n;");
			field++;
		}
		free(str);
		// нехватка полей
		if (field < 5)
		{
			if (name)
				free(name);
			if (country)
				free(country);
			if (genre)
				free(genre);
			return ERR_FORMAT;
		}
		
		// создание новой записи и добавление её в список
		gshow_t *node = create_node(name, prem_y, end_y, country, genre);
		if (!node)
		{
			free(name);
			free(country);
			free(genre);
			return ERR_MEMORY;
		}
		*head = push_back(*head, node);
	}
	while (!feof(f));
	
	return OK;
}

int add_to_list(gshow_t **head)
{
	int rc = OK;
	if (!head)
		return ERR_MEMORY;
	
	char *name = NULL, *genre = NULL, *country = NULL;
	int prem_y = 0, end_y = 0;
	ssize_t size;
	
	printf("Enter the name: ");
	fflush(stdin);
	rc = my_getline(&name, &size, stdin);
	if (!name || rc == -1)
		return ERR_INPUT;
	strtok(name, "\n");
	
	printf("Enter premier and final season years: ");
	rc = scanf("%d%d", &prem_y, &end_y);
	if (rc != 2 || prem_y < 0 || end_y < prem_y)
	{
		free(name);
		return ERR_INPUT;
	}
	
	printf("Enter origin country: ");
	fflush(stdin);
	rc = my_getline(&country, &size, stdin);
	if (!country || rc == -1)
	{
		free(name);
		return ERR_INPUT;
	}
	strtok(country, "\n");
	
	printf("Enter the genre: ");
	fflush(stdin);
	rc = my_getline(&genre, &size, stdin);
	if (!genre || rc == -1)
	{
		free(name);
		free(country);
		return ERR_INPUT;
	}
	strtok(genre, "\n");
	
	// создание новой записи и добавление её в список
	gshow_t *node = create_node(name, prem_y, end_y, country, genre);
	if (!node)
	{
		free(name);
		free(country);
		free(genre);
		return ERR_MEMORY;
	}
	*head = push_back(*head, node);
	if (!head)
		return ERR_MEMORY;
	return OK;
}

void print_node(gshow_t *node)
{
	if (node)
		printf("%-30s %4d %4d %-10s %-15s\n", node->name,
			node->prem_y, node->end_y, node->country, node->genre);
}

void print_list(gshow_t *head)
{
	if (!head)
		printf("\nList is empty\n");
	else
	{
		// шапка таблицы
		printf("\n%-30s %-4s %-4s %-10s %-15s\n", "Name of game show",
			"PREM", "END", "Country", "Genre");
		for (int k = 0; k < 70; k++)
			printf("=");
		printf("\n");
		
		// вывод каждой записи списка
		gshow_t *cur = head;
		while (cur)
		{
			print_node(cur);
			cur = cur->next;
		}
	}
}

void write_node(gshow_t *node, FILE *f)
{
	if (node)
		fprintf(f, "%s;%d;%d;%s;%s\n", node->name,
			node->prem_y, node->end_y, node->country, node->genre);
}

void write_list(gshow_t *head, FILE *f)
{
	assert(f);
	
	gshow_t *cur = head;
	while (cur)
	{
		write_node(cur, f);
		cur = cur->next;
	}
}