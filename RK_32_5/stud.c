#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stud.h"
#include "error.h"

int read_stud1(node_t **head, FILE *f)
{
	if (!f || !head)
		return ERR_ARG;
	while (!feof(f))
	{
		stud1_t *stud1 = malloc(sizeof(stud1_t));
		if (!stud1)
			return ERR_MEMORY;
		
		if (fgets(stud1->surname, 70, f) == NULL)
		{
			free(stud1);
			if (!*head)
				return ERR_EMPTY;
			else
				return OK;
		}
		for (int i = 0; i < 4; i++)
		{
			int sc = fscanf(f, "%d", &(stud1->exams[i]));
			if (sc != 1)
			{
				free(stud1);
				if (sc == EOF)
					return ERR_NDATA;
				return ERR_INPUT;
			}
			if (stud1->exams[i] < 1 || stud1->exams[i] > 5)
			{
				free(stud1);
				return ERR_INPUT;
			}
		}
		
		char ch;
		do
			fscanf(f, "%c", &ch);
		while (ch != '\n' && !feof(f));
		
		node_t *node = create_node((void *)stud1);
		if (!node)
		{
			free(stud1);
			return ERR_MEMORY;
		}
		*head = push_back(*head, node);
	}
	return OK;
}

void print_stud1(void *data, void *fout)
{
	if (!data || !fout)
		return;
	FILE *f = (FILE *)fout;
	stud1_t *stud = (stud1_t *) data;
	fprintf(f, "%s", stud->surname);
	for (int i = 0; i < 4; i++)
		fprintf(f, "%d ", stud->exams[i]);
	fprintf(f, "\n");
}

void print_stud2(void *data, void *fout)
{
	if (!data || !fout)
		return;
	FILE *f = (FILE *)fout;
	stud2_t *stud = (stud2_t *) data;
	fprintf(f, "%s%.2f\n", stud->surname, stud->exam_avg);
}

float avg(int *a, int n)
{
	assert(a && n >= 1);
	float sum = 0.0;
	for (int i = 0; i < n; i++)
		sum += a[i];
	return sum / n;
}

int stud1_to_stud2(node_t *head1, node_t **head2)
{
	if (!head2 || *head2)
		return ERR_ARG;
	if (!head1)
	{
		*head2 = NULL;
		return OK;
	}
	node_t *cur1 = head1;
	while (cur1)
	{
		stud1_t *stud1 = (stud1_t *) cur1->data;
		stud2_t *stud2 = malloc(sizeof(stud2_t));
		if (!stud2)
			return ERR_MEMORY;
		
		strcpy(stud2->surname, stud1->surname);
		stud2->exam_avg = avg(stud1->exams, 4);
		
		node_t *node = create_node((void *)stud2);
		if (!node)
		{
			free(stud2);
			return ERR_MEMORY;
		}
		*head2 = push_back(*head2, node);
		cur1 = cur1->next;
	}
	return OK;
}