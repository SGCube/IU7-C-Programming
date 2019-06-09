#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "error.h"
#include "list.h"
#include "stud.h"

#define EPS 1e-6

void test_avg()
{
	printf("avg:\n");
	{
		int arr[] = { 1 };
		if (fabs(avg(arr, sizeof(arr)/sizeof(arr[0])) - 1.0) < EPS)
			printf("1: PASSED\n");
		else
			printf("1: FAILED\n");
	}
	{
		int arr[] = { 1, 1, 1 };
		if (fabs(avg(arr, sizeof(arr)/sizeof(arr[0])) - 1.0) < EPS)
			printf("2: PASSED\n");
		else
			printf("2: FAILED\n");
	}
	{
		int arr[] = { 1, 2, 3, 4, 5 };
		if (fabs(avg(arr, sizeof(arr)/sizeof(arr[0])) - 3.0) < EPS)
			printf("3: PASSED\n");
		else
			printf("3: FAILED\n");
	}
	{
		int arr[] = { 2, 2, 4, 4 };
		if (fabs(avg(arr, sizeof(arr)/sizeof(arr[0])) - 3.0) < EPS)
			printf("4: PASSED\n");
		else
			printf("4: FAILED\n");
	}
	{
		int arr[] = { 0, 0, 0 };
		if (fabs(avg(arr, sizeof(arr)/sizeof(arr[0])) - 0.0) < EPS)
			printf("5: PASSED\n");
		else
			printf("5: FAILED\n");
	}
	{
		int arr[] = { -1, 1 };
		if (fabs(avg(arr, sizeof(arr)/sizeof(arr[0])) - 0.0) < EPS)
			printf("6: PASSED\n");
		else
			printf("6: FAILED\n");
	}
	printf("\n");
}

void test_push_back()
{
	printf("push_back:\n");
	{
		node_t *head = NULL;
		stud1_t elem = { "Ivanov", { 3, 4, 5, 5 } };
		node_t node = { (void *)&elem, NULL };
		head = push_back(head, &node);
		if (head == &node)
			printf("1: PASSED\n");
		else
			printf("1: FAILED\n");	
	}
	{
		stud1_t elem1 = { "Ivanov", { 3, 4, 5, 5 } };
		stud1_t elem2 = { "Sidorov", { 2, 2, 2, 2 } };
		node_t head_elem = { (void *)&elem1, NULL };
		node_t *head = &head_elem;
		node_t node = { (void *)&elem2, NULL };
		head = push_back(head, &node);
		if (head->next == &node)
			printf("2: PASSED\n");
		else
			printf("2: FAILED\n");
	}
	{
		stud1_t elem[] = {
			{ "Polyakova", { 5, 5, 5, 5 } },
			{ "Sorokin", { 5, 4, 5, 5 } },
			{ "Ryazanov", { 5, 5, 5, 5 } }
			};
		node_t tail = { (void *)&elem[1], NULL };
		node_t head_elem = { (void *)&elem[0], &tail };
		node_t *head = &head_elem;
		node_t node = { (void *)&elem[2], NULL };
		head = push_back(head, &node);
		if (head->next == &tail && tail.next == &node)
			printf("3: PASSED\n");
		else
			printf("3: FAILED\n");
	}
	printf("\n");
}

int main()
{
	test_avg();
	test_push_back();
	return 0;
}