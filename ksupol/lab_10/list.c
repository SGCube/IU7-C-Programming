#include <stdlib.h>
#include "list.h"

#define OK 0
#define ERR -1
#define ERR_MALLOC -2

void *pop_front(node_t **head)
{
	if (!head)
		return NULL;
	if (!*head)
		return NULL;
	void *temp = (*head)->data;
	node_t *t = *head;
	(*head) = (*head)->next;
	free(t);
	return temp;
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
		elem->next = NULL;
		return;
	}
	if (!before)
		return;
	if (*head == before)
	{
		*head = elem;
		elem->next = before;
		return;
	}
	node_t *tmp = *head;
	while (tmp->next && tmp->next != before)
		tmp = tmp->next;
	if (!tmp->next)
		return;
	tmp->next = elem;
	elem->next = before;
}

void append(node_t **head_a, node_t **head_b)
{
	if (!head_a)
		return;
	if (!head_b)
		return;
	if (!*head_a && !*head_b)
		return;
	if (*head_a && !*head_b)
		return;
	if (!*head_a && *head_b)
	{
		*head_a = *head_b;
		*head_b = NULL;
		return;
	}
	node_t *temp = *head_a;
	while (temp->next)
		temp = temp->next;
	temp->next = *head_b;
	*head_b = NULL;
}

node_t *create_elem(void *data)
{
	node_t *t = malloc(sizeof(node_t));
	if (!t)
		return NULL;
	t->next = NULL;
	t->data = data;
	return t;
}

int copy(node_t *head, node_t **new_head)
{
	if (!head)
		return ERR;
	if (!new_head)
		return ERR;
	if (*new_head)
		return ERR;
	node_t *temp = head;
	node_t *temp2 = NULL;
	while (temp)
	{
		node_t *t = create_elem(temp->data);
		if (!temp2)
		{
			temp2 = t;
			*new_head = temp2;
		}
		else
		{
			temp2->next = t;
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return OK;
}

node_t *reverse(node_t *head)
{
	node_t *p, *list = NULL;
	
	if (!head)
		return NULL;
	while (head)
	{
		p = head;
		head = head->next;
		p->next = list;
		list = p;
	}

	return list;
}

void front_back_split(node_t *head, node_t **back)
{
	int len = 0;
	
	if (!head)
		return;
	if (!back)
		return;
	if (*back)
		return;
	node_t *temp = head;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	if (len == 1)
		return;
	node_t *t = head;
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

node_t *sorted_merge(node_t **head_a, node_t **head_b,
	int (*comparator)(const void *, const void *))
{
	if (!head_a || !head_b)
		return NULL;
	if (!comparator)
		return NULL;
	node_t *head = NULL;
	node_t *temp = NULL;
	
	while (*head_a && *head_b)
	{
		node_t *t = NULL;
		if (comparator((*head_a)->data, (*head_b)->data) > 0)
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
		node_t *t = NULL;
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
		node_t *t = NULL;
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

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
	if (!head)
		return NULL;
	if (!comparator)
		return NULL;
	if (!head->next)
		return head;
	node_t *head_1 = head;
	node_t *head_2 = NULL;
	front_back_split(head_1, &head_2);
	head_1 = sort(head_1, comparator);
	head_2 = sort(head_2, comparator);
	return sorted_merge(&head_1, &head_2, comparator);
}

void free_list(node_t *head)
{
	node_t *t = head;
	int len = 0;
	while (t)
	{
		t = t->next;
		len++;
	}
	int l = len;
	for (int j = 0; j < len; j++)
	{
		t = head;
		for (int i = 0; i < l; i++)
			t = t->next;
		free(t);
		l--;
	}
	free(head);
}