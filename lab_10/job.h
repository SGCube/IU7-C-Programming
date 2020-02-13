#ifndef __JOB_H__
#define __JOB_H__

#define N_ALLOC 20
#include "list.h"
#include <stdio.h>
#include <unistd.h>

typedef struct
{
	char *name;
	int salary;
}  job;

ssize_t my_getline(char **lineptr, ssize_t *n, FILE *stream);
int create_job(FILE *f, job *ptr);
void print_job(void *ptr, FILE *stream);
void free_all_jobs(job *ptr, int k);
int jobcmp(const void *ptr1, const void *ptr2);
int jobcmpsal(const void *ptr1, const void *ptr2);
int read_joblist(FILE *f, node_t **head, job **arr, int *k);
int create_joblist(node_t **head, job *arr, int k);
void print_joblist(node_t *head, FILE *stream);
int job_insert(node_t **head, job **arr, int *kjob);

#endif