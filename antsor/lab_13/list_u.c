#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list_u.h"

gshow_t *create_node(char *name, unsigned int prem_y, unsigned int end_y,
	char *country, char *genre)
{
	gshow_t *node = malloc(sizeof(gshow_t));
	if (!node)
		return NULL;
	node->name = name;
	node->prem_y = prem_y;
	node->end_y = end_y;
	node->country = country;
	node->genre = genre;
	node->next = NULL;
	return node;
}
	
gshow_t *push_back(gshow_t *head, gshow_t *node)
{
	if (!head)
		return node;
	
	gshow_t *cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	return head;
}

void pop(gshow_t **head, char *name)
{
	if (!head)
		return;
	if (!*head || !name)
		return;
	
	gshow_t *cur = *head, *prev = NULL;
	while (cur->next && strcmp(name, cur->name) != 0)
	{
		prev = cur;
		cur = cur->next;
	}
	
	if (strcmp(name, cur->name) == 0)
	{
		if (!prev)
		{
			if (cur->next)
				*head = cur->next;
			else
				*head = NULL;
		}
		else
			prev->next = cur->next;
		free(cur->name);
		free(cur->country);
		free(cur->genre);
		free(cur);
	}
}

void pop_nofree(gshow_t **head, char *name)
{
	if (!head)
		return;
	if (!*head || !name)
		return;
	
	gshow_t *cur = *head, *prev = NULL;
	while (cur->next && strcmp(name, cur->name) != 0)
	{
		prev = cur;
		cur = cur->next;
	}
	
	if (strcmp(name, cur->name) == 0)
	{
		if (!prev)
		{
			if (cur->next)
				*head = cur->next;
			else
				*head = NULL;
		}
		else
			prev->next = cur->next;
		free(cur);
	}
}

void swap(gshow_t *a, gshow_t *b)
{
	char *tmp = a->name;
	a->name = b->name;
	b->name = tmp;
	
	tmp = a->country;
	a->country = b->country;
	b->country = tmp;
	
	tmp = a->genre;
	a->genre = b->genre;
	b->genre = tmp;
	
	int t = a->prem_y;
	a->prem_y = b->prem_y;
	b->prem_y = t;
	
	t = a->end_y;
	a->end_y = b->end_y;
	b->end_y = t;
}

void free_list(gshow_t **head)
{
	if (!head || !*head)
		return;
	
	gshow_t *cur = *head;
	while (*head)
	{
		cur = *head;
		*head = (*head)->next;
		free(cur->name);
		free(cur->country);
		free(cur->genre);
		free(cur);
	}
	*head = NULL;
}

void free_list_test(gshow_t **head)
{
	if (!head || !*head)
		return;
	
	gshow_t *cur = *head;
	while (*head)
	{
		cur = *head;
		*head = (*head)->next;
		free(cur);
	}
	*head = NULL;
}
