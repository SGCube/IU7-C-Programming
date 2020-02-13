#include <stdlib.h>
#include "list.h"

node_t *create_node(void *data)
{
	node_t *node = malloc(sizeof(node_t));
	if (!node)
		return NULL;
	node->data = data;
	node->next = NULL;
	return node;
}

node_t *push_back(node_t *head, node_t *node)
{
	if (!node)
		return head;
	if (!head)
		return node;
	node_t *cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	return head;
}

void print_list(node_t *head, void *f, void (*func)(void *, void *))
{
	if (!head)
		return;
	node_t *cur = head;
	while (cur)
	{
		func(cur->data, f);
		cur = cur->next;
	}
}

void free_list(node_t **head)
{
	if (!head || !*head)
		return;
	node_t *cur = *head;
	while (*head)
	{
		cur = *head;
		*head = (*head)->next;
		if (cur->data)
			free(cur->data);
		free(cur);
	}
	*head = NULL;
}