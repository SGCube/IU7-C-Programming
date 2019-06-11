#ifndef __LIST_H__
#define __LIST_H__

typedef struct node node_t;

struct node
{
	void *data;
	node_t *next;
};

node_t *create_elem(void *data);
void *pop_front(node_t **head);
void insert(node_t **head, node_t *elem, node_t *before);
void append(node_t **head_a, node_t **head_b);
int copy(node_t *head, node_t **new_head);
node_t *reverse(node_t *list);
void front_back_split(node_t *head, node_t **back);
node_t *sorted_merge(node_t **head_a, node_t **head_b,
	int (*comparator)(const void *, const void *));
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
void free_list(node_t *head);

#endif