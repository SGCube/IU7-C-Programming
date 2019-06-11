#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define OK 0
#define ERR -1
#define EMPTY_FILE -2
#define ERR_MALLOC -3

void test_read_from_file()
{
	printf("test_read_from_file:\n");
	{
		FILE *f = fopen("tests/in_0.txt", "r");
		int rc = 0;
		if (!f)
			return;
		list *head = NULL;
		rc = read_from_file(f, &head);
		if (rc != EMPTY_FILE)
			printf("1) FAILED\n");
		else
			printf("1) OK\n");
	}
	{
		FILE *f = fopen("tests/in_1.txt", "r");
		int rc = 0;
		if (!f)
			return;
		list *head = NULL;
		rc = read_from_file(f, &head);
		if (rc != EMPTY_FILE)
			printf("1) FAILED\n");
		else
			printf("1) OK\n");
	}
	{
		FILE *f = fopen("tests/in_0.txt", "r");
		int rc = 0;
		if (!f)
			return;
		list *head = NULL;
		rc = read_from_file(f, &head);
		if (rc != EMPTY_FILE)
			printf("1) FAILED\n");
		else
			printf("1) OK\n");
	}
}

int main()
{
	test_read_from_file();
	return 0;
}