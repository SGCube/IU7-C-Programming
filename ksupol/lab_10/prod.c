#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prod.h"
#include "list.h"

#define OK 0
#define ERR_CAL -1
#define ERR -2
#define ERR_MALLOC -3
#define MAX_LEN 128
#define EMPTY -4

int my_getline(char **line, int *n, FILE *f)
{
	if (!f || !n || !line)
		return ERR;
	int len = 0;
	char buffer[MAX_LEN];
	int end_line = 0;
	char *point = NULL;
	char *t;
	
	do
	{
		end_line = 0;
		if (fgets(buffer, MAX_LEN, f) == NULL)
			return ERR;
		if (strlen(buffer) + 1 > *n)
		{
			t = realloc(*line, (len + MAX_LEN) * sizeof(char));
			if (!t)
				return ERR;
			*line = t;
			*n = len + MAX_LEN;
		}
		point = *line + len;
		len += strlen(buffer);
		for (char *pc = buffer; *pc != '\0'; pc++, point++)
		{
			if (*pc == '\n')
				end_line = 1;
			*point = *pc;
		}
	}
	while (!feof(f) && !end_line);
	
	if (len == 0)
		return ERR;
	(*line)[len] = '\0';
	
	*n = len + 1;
	return len;
}

int read_from_file(FILE *f, prod_t **p)
{
	int rc = 0;
	int c = 0;
	int len = 100;
	int i = 0;
	
	rc = fscanf(f, "%d ", &c);
	if (rc == EOF)
		return 0;
	rewind(f);
	
	do
	{
		if (i % 100 == 0)
		{
			void *t = realloc(*p, (i + 100) * sizeof(prod_t));
			if (!t)
				return ERR_MALLOC;
			*p = (prod_t *)t;
		}
		rc = fscanf(f, "%d ", &c);
		if (rc != 1 || c < 0 || c > 1000)
			return ERR_CAL;
		(*p + i)->name = malloc(100 * sizeof(char));
		if (!(*p + i)->name)
			return ERR_MALLOC;
		rc = my_getline(&((*p + i)->name), &len, f);
		if ((*p + i)->name[len - 2] == '\n')
			(*p + i)->name[len - 2] = '\0';
		(*p + i)->cal = c;
		i++;
	}
	while (!feof(f));
	
	return i;
}

void print_prod_file(prod_t *p, int am, FILE *f)
{
	int i = 0;
	for (i = 0; i < am ; i++)
		fprintf(f, "%d %s\n", p[i].cal, p[i].name);
}

int create_list(node_t **head, int am, prod_t *p)
{
	if (am == 0)
		return EMPTY;
	*head = create_elem((void *)&(p[0]));
	if (*head == NULL)
		return ERR_MALLOC;
	(*head)->next = NULL;
	if (am > 1)
	{
		node_t *temp = *head;
		for (int i = 1; i < am; i++)
		{
			temp->next = create_elem((void *)&(p[i]));
			if (temp->next == NULL)
				return ERR_MALLOC;
			temp = temp->next;
			temp->next = NULL;
		}
	}
	return OK;
}

void print_list_file(node_t *head, FILE *f)
{
	node_t *temp = head;
	while (temp)
	{
		fprintf(f, "%d %s\n", ((prod_t *)(temp->data))->cal,
			((prod_t *)(temp->data))->name);
		temp = temp->next;
	}
}

void print_list(node_t *head)
{
	node_t *temp = head;
	int i = 0;
	while (temp)
	{
		i++;
		printf("%d %s\n", ((prod_t *)temp->data)->cal,
			((prod_t *)temp->data)->name);
		temp = temp->next;
	}
}

int compar(const void *a, const void *b)
{
	return ((prod_t *)a)->cal - ((prod_t *)b)->cal;
}