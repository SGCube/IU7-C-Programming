#ifndef __GSHOWF__H__
#define __GSHOWF__H__

#include "gshow.h"

ssize_t my_getline(char **lineptr, ssize_t *n, FILE *stream);

int read_list(gshow_t **head, FILE *f);

int add_to_list(gshow_t **head);

void print_node(gshow_t *node);

void print_list(gshow_t *head);

void write_node(gshow_t *node, FILE *f);

void write_list(gshow_t *node, FILE *f);

#endif