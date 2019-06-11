#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define OK 0
#define EMPTY_FILE -2
#define ERR_MALLOC -3

int read_from_file(FILE *f, list **head)
{
	int rc = 0;
	char temp1[70];
	char temp2[10];
	
	rc = fscanf(f, "%s", temp1);
	if (rc == EOF)
		return EMPTY_FILE;
	rewind(f);
	do
	{
		fscanf(f, "%s", temp1);
		fscanf(f, "%s", temp2);
		list *t = create_elem(temp1, temp2);
		create_list(head, t);
	}
	while (!feof(f));
	return OK;
}

void create_list(list **head, list *t)
{
	if (*head == NULL)
	{
		*head = t;
		return;
	}
	list *temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = t;
}

void print_list(list *head)
{
	list *temp = head;
	printf("\n");
	while (temp)
	{
		printf("%s - %s\n", temp->name, temp->gr);
		temp = temp->next;
	}
	printf("\n");
}

void free_list(list *head)
{
	int len = 0;
	list *t = head;
	while (t)
	{
		t = t->next;
		len++;
	}
	int a = len;
	for (int j = 0; j < len; j++)
	{
		t = head;
		for (int i = 0; i < a; i++)
			t = t->next;
		free(t);
		a--;
	}
	free(head);
}

list *create_elem(char temp1[], char temp2[])
{
	list *t = malloc(sizeof(list));
	if (!t)
		return NULL;
	t->next = NULL;
	for (int i = 0; i < 70; i++)
		t->name[i] = temp1[i];
	for (int i = 0; i < 10; i++)
		t->gr[i] = temp2[i];
	return t;
}

list *sort(list *head)
{
	if (!head)
		return NULL;
	if (!head->next)
		return head;
	list *head_1 = head;
	list *head_2 = NULL;
	front_back_split(head_1, &head_2);
	head_1 = sort(head_1);
	head_2 = sort(head_2);
	return sorted_merge(&head_1, &head_2);
}

list *sorted_merge(list **head_a, list **head_b)
{
	if (!head_a || !head_b)
		return NULL;
	list *head = NULL;
	list *temp = NULL;
	
	while (*head_a && *head_b)
	{
		list *t = NULL;
		if (strcmp((*head_a)->gr, (*head_b)->gr) > 0)
		{
			t = *head_b;
			*head_b = (*head_b)->next;
		}
		else
		{
			t = *head_a;
			*head_a = (*head_a)->next;
		}
		if (!head)
		{
			head = t;
			temp = head;
		}
		else
		{
			temp->next = t;
			temp = temp->next;
		}
	}
	while (*head_a)
	{
		list *t = NULL;
		t = *head_a;
		*head_a = (*head_a)->next;
		if (!head)
		{
			head = t;
			temp = head;
		}
		else
		{
			temp->next = t;
			temp = temp->next;
		}
	}
	while (*head_b)
	{
		list *t = NULL;
		t = *head_b;
		*head_b = (*head_b)->next;
		if (!head)
		{
			head = t;
			temp = head;
		}
		else
		{
			temp->next = t;
			temp = temp->next;
		}
	}
	return head;
}

void front_back_split(list *head, list **back)
{
	int len = 0;
	
	if (!head)
		return;
	if (!back)
		return;
	if (*back)
		return;
	list *temp = head;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	if (len == 1)
		return;
	list *t = head;
	if (len == 2)
	{
		*back = t->next;
		t->next = NULL;
		return;
	}
	for (int i = 0; i < (len / 2 + len % 2) - 1; i++)
		t = t->next;
	*back = t->next;
	t->next = NULL;
}