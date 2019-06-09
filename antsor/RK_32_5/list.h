#ifndef __LIST__H__
#define __LIST__H__

typedef struct node node_t;

struct node
{
	void *data;
	node_t *next;
};

node_t *create_node(void *data);

node_t *push_back(node_t *head, node_t *node);

void print_list(node_t *head, void *f, void (*func)(void *, void *));

void free_list(node_t **head);

#endif