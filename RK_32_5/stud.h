#ifndef __STUD__H__
#define __STUD__H__

#include "list.h"

typedef struct stud1 stud1_t;

struct stud1
{
	char surname[70];
	int exams[4];
};

typedef struct stud2 stud2_t;

struct stud2
{
	char surname[70];
	float exam_avg;
};

int read_stud1(node_t **head, FILE *f);

void print_stud1(void *data, void *f);

void print_stud2(void *data, void *f);

float avg(int *a, int n);

int stud1_to_stud2(node_t *head1, node_t **head2);

#endif