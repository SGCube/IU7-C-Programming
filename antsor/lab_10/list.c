#include <stdlib.h>
#include "list.h"
#include "error.h"

int create_node(node_t **node, void *data)
{
	*node = malloc(sizeof(node_t));
	if (!*node)
		return ERR_ALLOC;
	(*node)->data = data;
	(*node)->next = NULL;
	return OK;
}

int listlen(node_t *head)
{
	node_t *cur = head;
	int len = 0;
	while(cur)
	{
		cur = cur->next;
		len++;
	}
	return len;
}

node_t *add_node(node_t *head, node_t *node)
{
	if (!head)
		return node;
	else
	{
		node_t *cur = head;
		while(cur->next)
			cur = cur->next;
		cur->next = node;
		return head;
	}
}

node_t *get_node(node_t *head, int i)
{
	if (!head)
		return NULL;
	if (i < 1)
		return NULL;
	node_t *cur = head;
	int j = 1;
	for (; cur && j < i; j++, cur = cur->next);
	if (!cur)
		return NULL;
	return cur;
}

void delete_all(node_t **head)
{
	if (!head)
		return;
	if (!*head)
		return;
	node_t *cur = *head;
	while(*head)
	{
		*head = cur->next;
		free(cur);
		cur = *head;
	}
	*head = NULL;
}

void *pop_back(node_t **head)
{
	if (!head)
		return NULL;
	if (!*head)
		return NULL;
	
	void *data = NULL;
	node_t *cur = *head, *prev = NULL;
	while (cur->next)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!prev)
	{
		data = (*head)->data;
		free(*head);
		*head = NULL;
	}
	else
	{
		data = cur->data;
		free(cur);
		prev->next = NULL;
	}
	return data;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
	if (!head)
		return;
	if (!elem)
		return;
	if (!*head)
	{
		*head = elem;
		(*head)->next = NULL;
		return;
	}
	if (!before)
		return;
	
	if (*head == before)
	{
		elem->next = *head;
		*head = elem;
	}
	else
	{
		node_t *cur = *head;
		while (cur->next != before && cur->next)
			cur = cur->next;
		if (cur->next)
		{
			elem->next = before;
			cur->next = elem;
		}
	}
}

void remove_duplicates(node_t **head,
	int (*comparator)(const void *, const void *))
{
	if (!*head)
		return;
	node_t *cmp = *head;
	while (cmp)
	{
		node_t *prev = cmp;
		while (prev->next)
		{
			if (comparator(prev->next->data, cmp->data) == 0)
			{
				node_t *cur = prev->next;
				prev->next = cur->next;
				free(cur);
			}
			else
				prev = prev->next;
		}
		cmp = cmp->next;
	}
}

void front_back_split(node_t *head, node_t **back)
{
	if (!back)
		return;
	*back = NULL;
	if (!head)
		return;
	
	if (head->next)
	{
		int len = listlen(head);
		int medium = len / 2 + len % 2 - 1;
		node_t *tmp = head;
		for (int i = 0; i < medium; i++)
			tmp = tmp->next;
		*back = tmp->next;
		tmp->next = NULL;
	}
}

node_t *sorted_merge(node_t **head_a, node_t **head_b,
	int (*comparator)(const void *, const void *))
{
	if (!head_a || !head_b)
		return NULL;
	if (!comparator)
		return NULL;
	
	node_t *head = NULL, *tmp = NULL, *cur = NULL;
	while (*head_a && *head_b)
	{
		if (comparator((*head_a)->data, (*head_b)->data) <= 0)
		{
			tmp = *head_a;
			*head_a = (*head_a)->next;
		}
		else
		{
			tmp = *head_b;
			*head_b = (*head_b)->next;
		}
		tmp->next = NULL;
		if (!head)
		{
			head = tmp;
			cur = head;
		}
		else
		{
			cur->next = tmp;
			cur = cur->next;
		}
	}
	while (*head_a)
	{
		tmp = *head_a;
		*head_a = (*head_a)->next;
		tmp->next = NULL;
		if (!head)
		{
			head = tmp;
			cur = head;
		}
		else
		{
			cur->next = tmp;
			cur = cur->next;
		}
	}
	while (*head_b)
	{
		tmp = *head_b;
		*head_b = (*head_b)->next;
		tmp->next = NULL;
		if (!head)
		{
			head = tmp;
			cur = head;
		}
		else
		{
			cur->next = tmp;
			cur = cur->next;
		}
	}
	return head;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
	if (!head)
		return NULL;
	if (!comparator)
		return NULL;
	
	if (!head->next)
		return head;
	
	node_t *head_a = head;
	node_t *head_b = NULL;
	front_back_split(head_a, &head_b);
	head_a = sort(head_a, comparator);
	head_b = sort(head_b, comparator);
	return sorted_merge(&head_a, &head_b, comparator);
}