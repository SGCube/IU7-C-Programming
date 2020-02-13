#ifndef __LISTU__H__
#define __LISTU__H__

#include "gshow.h"

gshow_t *create_node(char *name, unsigned int prem_y, unsigned int end_y,
	char *country, char *genre);
	
gshow_t *push_back(gshow_t *head, gshow_t *node);

void pop(gshow_t **head, char *name);

void pop_nofree(gshow_t **head, char *name);
	
void swap(gshow_t *a, gshow_t *b);

void free_list(gshow_t **head);

void free_list_test(gshow_t **head);

#endif