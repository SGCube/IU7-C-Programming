#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "prod.h"

#define OK 0
#define ERR_CAL -1
#define ERR -2
#define ERR_MALLOC -3
#define MAX_LEN 128
#define EMPTY -4

void test_read_from_file()
{
	int err_cnt = 0;
	{
		int rc;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_read_from_file/in_0.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		if (rc != OK)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
	}
	{
		int rc;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_read_from_file/in_1.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		if (rc != ERR_CAL)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
	}
	{
		int rc;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_read_from_file/in_2.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		if (rc != 1)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
	}
	{
		int rc;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_read_from_file/in_3.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		if (rc != 5)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
	}
	{
		int rc;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_read_from_file/in_4.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		if (rc != 105)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
	}
	if (err_cnt != 0)
		printf("test_read_from_file: FAILED\n");
	else
		printf("test_read_from_file: OK\n");
}

void test_create_list()
{
	int err_cnt = 0;
	{
		int rc, sc;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_create_list/in_0.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		sc = create_list(&head, rc, p);
		if (sc != EMPTY)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	{
		int rc, sc;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_create_list/in_1.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		sc = create_list(&head, rc, p);
		if (sc != OK)
			err_cnt++;
		if (((prod_t *)head->data)->cal != 255 ||
			strcmp(((prod_t *)head->data)->name, "chicken") != 0)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	{
		int rc, sc;
		node_t *head = NULL;
		prod_t *p;
		int c[5] = { 45, 12, 255, 36, 74 };
		char n[5][15] = { "apple", "watermelon", "chicken", "potato", "almond" };
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_create_list/in_2.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		sc = create_list(&head, rc, p);
		if (sc != OK)
			err_cnt++;
		node_t *temp = head;
		for (int i = 0; i < 5; i++)
		{
			if (((prod_t *)temp->data)->cal != c[i] ||
				strcmp(((prod_t *)temp->data)->name, n[i]) != 0)
				err_cnt++;
			temp = temp->next;
		}
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	{
		int rc, sc;
		node_t *head = NULL;
		prod_t *p;
		char *d = "apple";
		int c[105];
		for (int i = 0; i < 105; i++)
			c[i] = 45;
		char n[105][15];
		for (int i = 0; i < 105; i++)
			for (int j = 0; j < 15; j++)
				n[i][j] = d[j];
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_create_list/in_3.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		sc = create_list(&head, rc, p);
		if (sc != OK)
			err_cnt++;
		node_t *temp = head;
		for (int i = 0; i < 105; i++)
		{
			if (((prod_t *)temp->data)->cal != c[i] ||
				strcmp(((prod_t *)temp->data)->name, n[i]) != 0)
				err_cnt++;
			temp = temp->next;
		}
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	if (err_cnt != 0)
		printf("test_create_list: FAILED\n");
	else
		printf("test_create_list: OK\n");
}

void test_pop_front()
{
	int err_cnt = 0;
	{
		int rc;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_pop_front/in_0.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		create_list(&head, rc, p);
		void *product = pop_front(&head);
		if (product)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	{
		int rc;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_pop_front/in_1.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		create_list(&head, rc, p);
		void *product = pop_front(&head);
		if (((prod_t *)product)->cal != 45 ||
			strcmp(((prod_t *)product)->name, "chicken") != 0)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	{
		int rc;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		if (!p)
			printf("Memory allocation error!\n");
		FILE *f = fopen("test/test_pop_front/in_2.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		create_list(&head, rc, p);
		void *product = pop_front(&head);
		if (((prod_t *)product)->cal != 45 ||
			strcmp(((prod_t *)product)->name, "apple") != 0)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	if (err_cnt != 0)
		printf("test_pop_front: FAILED\n");
	else
		printf("test_pop_front: OK\n");
}

void test_sort()
{
	int err_cnt = 0;
	{
		int rc = 0;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		FILE *f = fopen("test/test_sort/in_0.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		create_list(&head, rc, p);
		head = sort(head, compar);
		int c = 12;
		char *n = "pepper";
		if (((prod_t *)head->data)->cal != c ||
			strcmp(((prod_t *)head->data)->name, n) != 0)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	{
		int rc = 0;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		FILE *f = fopen("test/test_sort/in_1.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		create_list(&head, rc, p);
		head = sort(head, compar);
		int c1[3] = { 12, 36, 488 };
		char n1[3][150] = { "apple", "watermelon", "chicken" };
		node_t *temp = head;
		for (int i = 0; i < 3; i++)
		{
			if (((prod_t *)temp->data)->cal != c1[i] ||
				strcmp(((prod_t *)temp->data)->name, n1[i]) != 0)
				err_cnt++;
			temp = temp->next;
		}
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	{
		int rc = 0;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		FILE *f = fopen("test/test_sort/in_2.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		create_list(&head, rc, p);
		head = sort(head, compar);
		char *nn1 = "apple";
		char *nn2 = "chicken";
		int c1[40];
		char n1[40][10];
		for (int i = 0; i < 10; i++)
			c1[i] = 15;
		for (int i = 10; i < 40; i++)
			c1[i] = 500;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				n1[i][j] = nn1[j];
		for (int i = 10; i < 40; i++)
			for (int j = 0; j < 10; j++)
				n1[i][j] = nn2[j];
		node_t *temp = head;
		for (int i = 0; i < 40; i++)
		{
			if (((prod_t *)temp->data)->cal != c1[i] ||
				strcmp(((prod_t *)temp->data)->name, n1[i]) != 0)
				err_cnt++;
			temp = temp->next;
		}
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	if (err_cnt != 0)
		printf("test_sort: FAILED\n");
	else
		printf("test_sort: OK\n");
}

void test_reverse()
{
	int err_cnt = 0;
	{
		int rc = 0;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		FILE *f = fopen("test/test_reverse/in_0.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		create_list(&head, rc, p);
		head = reverse(head);
		int c = 12;
		char *n = "pepper";
		if (((prod_t *)head->data)->cal != c ||
			strcmp(((prod_t *)head->data)->name, n) != 0)
			err_cnt++;
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	{
		int rc = 0;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		FILE *f = fopen("test/test_reverse/in_1.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		create_list(&head, rc, p);
		head = reverse(head);
		int c1[3] = { 36, 12, 488 };
		char n1[3][150] = { "watermelon", "apple", "chicken" };
		node_t *temp = head;
		for (int i = 0; i < 3; i++)
		{
			if (((prod_t *)temp->data)->cal != c1[i] ||
				strcmp(((prod_t *)temp->data)->name, n1[i]) != 0)
				err_cnt++;
			temp = temp->next;
		}
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	{
		int rc = 0;
		node_t *head = NULL;
		prod_t *p;
		p = malloc(100 * sizeof(prod_t));
		FILE *f = fopen("test/test_reverse/in_2.txt", "r");
		rc = read_from_file(f, &p);
		fclose(f);
		create_list(&head, rc, p);
		head = reverse(head);
		int c1[5] = { 455, 89, 63, 288, 15 };
		char n1[5][150] = { "chocolate", "becon", "milk", "cheese", "apple" };
		node_t *temp = head;
		for (int i = 0; i < 5; i++)
		{
			if (((prod_t *)temp->data)->cal != c1[i] ||
				strcmp(((prod_t *)temp->data)->name, n1[i]) != 0)
				err_cnt++;
			temp = temp->next;
		}
		for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
		free(p);
		free_list(head);
	}
	if (err_cnt != 0)
		printf("test_reverse: FAILED\n");
	else
		printf("test_reverse: OK\n");
}

int main()
{
	test_read_from_file();
	test_create_list();
	test_pop_front();
	test_sort();
	test_reverse();
	return 0;
}