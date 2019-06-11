#ifndef __PROD_H__
#define __PROD_H__
#include "list.h"
typedef struct product prod_t;

struct product
{
	char *name;
	int cal;
};

int my_getline(char **line, int *n, FILE *f);
int read_from_file(FILE *f, prod_t **p);
void print_prod_file(prod_t *p, int am, FILE *f);
int create_list(node_t **head, int am, prod_t *p);
void print_list_file(node_t *head, FILE *f);
int compar(const void *a, const void *b);
void print_list(node_t *head);

#endif