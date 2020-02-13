#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "job.h"
#include "error.h"

#define STR_SIZE 30
#define READ_END -10

ssize_t my_getline(char **lineptr, ssize_t *n, FILE *stream)
{
	if (stream == NULL || lineptr == NULL || n == NULL)
		return -1;
	if (*n == 0 || *lineptr == NULL)
	{
		*lineptr = malloc(STR_SIZE * sizeof(char));
		*n = STR_SIZE;
	}
	
	ssize_t len = 0;
	char buff[STR_SIZE];
	char *ptr = *lineptr;
	char *t;
	ssize_t buff_len = 0;

	do
	{
		if (fgets(buff, STR_SIZE, stream) == NULL)
			return -1;
		buff_len = strlen(buff);
		if (len + buff_len + 1 > *n)
		{
			t = (char *)realloc(*lineptr,
				(len + STR_SIZE) * sizeof(char));
			if (!t)
				return -1;
			*lineptr = t;
			*n = len + STR_SIZE;
		}
		ptr = *lineptr + len;
		len += buff_len;
		for (const char *pc = buff; *pc != '\0'; pc++, ptr++)
			*ptr = *pc;
	}
	while (!feof(stream) && buff[buff_len - 1] != '\n');
	if ((*lineptr)[len - 1] == '\n')
		len--;
	if (len == 0)
		return -1;
	(*lineptr)[len] = '\0';
	*n = len + 1;
	return len;
}

int create_job(FILE *f, job *ptr)
{
	fflush(stdin);
	if (!f)
		return ERR_FILE;
	if (f == stdin)
		printf("Enter salary: ");
	int rc = fscanf(f, "%d", &(ptr->salary));
	if (rc == EOF)
		return READ_END;
	if (rc != 1 || ptr->salary < 0)
		return ERR_INPUT;
	ptr->name = malloc(STR_SIZE);
	if (!ptr->name)
		return ERR_ALLOC;
	ssize_t n = STR_SIZE;
	if (f == stdin)
		printf("Enter job: ");
	fflush(stdin);
	if (my_getline(&(ptr->name), &n, f) == -1)
	{
		if (ptr->name)
			free(ptr->name);
		return ERR_ALLOC;
	}
	return OK;
}

void print_job(void *ptr, FILE *stream)
{
	job *data = (job *) ptr;
	fprintf(stream, "%d %s\n", data->salary, data->name);
}

void free_all_jobs(job *ptr, int k)
{
	for (int i = 0; i < k; i++)
		free((ptr + i)->name);
	free(ptr);
}

int jobcmp(const void *ptr1, const void *ptr2)
{
	if (!ptr1 || !ptr2)
		return 1;
	job *job1 = (job *) ptr1, *job2 = (job *) ptr2;
	if (job1->salary == job2->salary && !strcmp(job1->name, job2->name))
		return 0;
	return 1;
}

int jobcmpsal(const void *ptr1, const void *ptr2)
{
	if (!ptr1 || !ptr2)
		return 1;
	job *job1 = (job *) ptr1, *job2 = (job *) ptr2;
	return job1->salary - job2->salary;
}

int read_joblist(FILE *f, node_t **head, job **arr, int *k)
{
	int rc = OK;
	if (!f)
		return ERR_FILE;
	*head = NULL;
	job *ptr = *arr;
	*k = 0;
	while(!feof(f))
	{
		if (k + 1 % N_ALLOC == 0)
		{
			job *t = (job *) realloc(*arr, (*k + N_ALLOC) * sizeof(job));
			if (!t)
				return ERR_ALLOC;
			*arr = t;
		}
		rc = create_job(f, ptr);
		if (rc == READ_END)
			return OK;
		if (rc != OK)
			return rc;
		node_t *node = NULL;
		rc = create_node(&node, (void *)ptr);
		if (rc != OK)
			return rc;
		*head = add_node(*head, node);
		if (!head)
			return ERR_INPUT;
		ptr++;
		*k += 1;
	}
	return rc;
}

int create_joblist(node_t **head, job *arr, int k)
{
	int rc = OK;
	if (!arr)
		return ERR_INPUT;
	*head = NULL;
	job *ptr = arr;
	for (int i = 0; i < k; i++)
	{
		node_t *node = NULL;
		rc = create_node(&node, (void *)ptr);
		if (rc != OK)
			return rc;
		*head = add_node(*head, node);
		if (!head)
			return ERR_INPUT;
		ptr++;
	}
	return OK;
}

void print_joblist(node_t *head, FILE *stream)
{
	node_t *h = head;
	if (!h && stream == stdout)
		printf("List is empty!\n");
	while(h)
	{
		print_job(h->data, stream);
		h = h->next;
	}
}

int job_insert(node_t **head, job **arr, int *kjob)
{
	int rc = OK;
	int ind = 0, len = listlen(*head);
	fflush(stdin);
	printf("Enter no of node to insert before: ");
	if (scanf("%d", &ind) != 1 || ind < 1 || (len > 0 && ind > len) ||
		(len == 0 && ind > 1))
		return ERR_INDEX;
	if (*kjob + 1 % N_ALLOC == 0)
	{
		job *t = (job *) realloc(*arr, (*kjob  + 1) * sizeof(job));
		if (!t)
			return ERR_ALLOC;
		*arr = t;
	}
	*kjob += 1;
	rc = create_job(stdin, *arr + *kjob - 1);
	if (rc != OK)
		return rc;
	
	node_t *node = NULL;
	rc = create_node(&node, (void *)(*arr + *kjob - 1));
	if (rc != OK)
		return rc;
	if (!node)
		rc = ERR_ALLOC;
	else
	{
		node_t *before = get_node(*head, ind);
		insert(head, node, before);
	}
	return OK;
}