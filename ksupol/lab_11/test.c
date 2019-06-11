#include <stdio.h>
#include <string.h>
#include "pr.h"

int main(void)
{
	printf("test_my_snprintf:\n");
	{
		char b[10];
		char b_test[10]; 
		int c;
		int c_test;
		c = my_snprintf(b, 10, "%s", "n");
		c_test = snprintf(b_test, 10, "%s", "n");
		if (c != c_test)
			printf("1) FAILED\n");
		else if (strcmp(b, b_test) != 0)
			printf("1) FAILED\n");
		else
			printf("1) OK\n");
	}
	{
		char b[50];
		char b_test[50]; 
		int c;
		int c_test;
		c = my_snprintf(b, 50, "%s %s", "n", "k");
		c_test = snprintf(b_test, 50, "%s %s", "n", "k");
		if (c != c_test)
			printf("2) FAILED\n");
		else if (strcmp(b, b_test) != 0)
			printf("2) FAILED\n");
		else
			printf("2) OK\n");
	}
	{
		char b[50];
		char b_test[50]; 
		int c;
		int c_test;
		c = my_snprintf(b, 50, "%s %hd", "n", 120);
		c_test = snprintf(b_test, 50, "%s %hd", "n", 120);
		if (c != c_test)
			printf("3) FAILED\n");
		else if (strcmp(b, b_test) != 0)
			printf("3) FAILED\n");
		else
			printf("3) OK\n");
	}
	{
		char b[50];
		char b_test[50]; 
		int c;
		int c_test;
		c = my_snprintf(b, 50, "%hd %hd", 2999, 32767);
		
		c_test = snprintf(b_test, 50, "%hd %hd", 2999, 32767);
		if (c != c_test)
			printf("4) FAILED\n");
		else if (strcmp(b, b_test) != 0)
			printf("4) FAILED\n");
		else
			printf("4) OK\n");
	}
	{
		char b[20];
		char b_test[20]; 
		int c;
		int c_test;
		c = my_snprintf(b, 50, "%hd %s", -32767, "k");
		c_test = snprintf(b_test, 50, "%hd %s", -32767, "k");
		if (c != c_test)
			printf("5) FAILED\n");
		else if (strcmp(b, b_test) != 0)
			printf("5) FAILED\n");
		else
			printf("5) OK\n");
	}
	{
		char *b = NULL;
		char *b_test = NULL; 
		int c;
		int c_test;
		c = my_snprintf(b, 0, "abc");
		c_test = snprintf(b_test, 0, "abc");
		if (c != c_test)
			printf("6) FAILED\n");
		else
			printf("6) OK\n");
	}
	{
		char b[20];
		char b_test[20]; 
		int c;
		int c_test;
		c = my_snprintf(b, 0, "abc");
		c_test = snprintf(b_test, 0, "abc");
		if (c != c_test)
			printf("7) FAILED\n");
		else
			printf("7) OK\n");
	}
	{
		char b[20];
		char b_test[20]; 
		int c;
		int c_test;
		c = my_snprintf(b, 50, "abc");
		c_test = snprintf(b_test, 50, "abc");
		if (c != c_test)
			printf("8) FAILED\n");
		else if (strcmp(b, b_test) != 0)
			printf("8) FAILED\n");
		else
			printf("8) OK\n");
	}
	return 0;
}