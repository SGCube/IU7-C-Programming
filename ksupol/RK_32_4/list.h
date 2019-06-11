#ifndef __LIST__H__
#define __LIST__H__

typedef struct list_h list;

struct list_h
{
	char name[70];
	char gr[10];
	list *next;
};

int read_from_file(FILE *f, list **head);
void create_list(list **head, list *t);
void print_list(list *head);
void free_list(list *head);
list *create_elem(char temp1[], char temp2[]);
list *sort(list *head);
list *sorted_merge(list **head_a, list **head_b);
void front_back_split(list *head, list **back);
#endif