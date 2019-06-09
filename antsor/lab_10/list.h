#ifndef __LIST_H__
#define __LIST_H__

typedef struct node node_t;

struct node
{
	void *data;
	node_t *next;
};

int create_node(node_t **node, void *data);
int listlen(node_t *head);
node_t *add_node(node_t *head, node_t *node);
node_t *get_node(node_t *head, int i);
void delete_all(node_t **head);
void *pop_back(node_t **head);
void insert(node_t **head, node_t *elem, node_t *before);
void remove_duplicates(node_t **head,
	int (*comparator)(const void *, const void *));
void front_back_split(node_t *head, node_t **back);
node_t *sorted_merge(node_t **head_a, node_t **head_b,
	int (*comparator)(const void *, const void *));
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif