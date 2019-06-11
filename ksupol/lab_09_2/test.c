#include <stdio.h>
#include "str.h"
#include <stdlib.h>

#define MAX_LEN 50

void test_str_replace()
{
	int err_cnt = 0;
	{
		char source[] = "So put your hands up high";
		char search[] = "put";
		char replace[] = "take";
		char res[] = "So take your hands up high";
		char *result = str_replace(source, search, replace);
		if (my_strcmp(result, res) != 0)
			err_cnt++;
		if (result)
			free(result);
	}
	{
		char source[] = "So put your hands up high";
		char search[] = "put";
		char replace[] = "t";
		char res[] = "So t your hands up high";
		char *result = str_replace(source, search, replace);
		if (my_strcmp(result, res) != 0)
			err_cnt++;
		if (result)
			free(result);
	}
	{
		char source[] = "So put your hands up high";
		char search[] = "So put your hands up high";
		char replace[] = "take";
		char res[] = "take";
		char *result = str_replace(source, search, replace);
		if (my_strcmp(result, res) != 0)
			err_cnt++;
		if (result)
			free(result);
	}
	{
		char source[] = "So put your hands up high";
		char search[] = "So put your hands up high";
		char replace[] = "";
		char res[] = "";
		char *result = str_replace(source, search, replace);
		if (my_strcmp(result, res) != 0)
			err_cnt++;
		if (result)
			free(result);
	}
	{
		char source[] = "So put your hands up high";
		char search[] = "So";
		char replace[] = "";
		char res[] = " put your hands up high";
		char *result = str_replace(source, search, replace);
		if (my_strcmp(result, res) != 0)
			err_cnt++;
		if (result)
			free(result);
	}
	{
		char source[] = "So put your hands up high";
		char search[] = "run";
		char replace[] = "take";
		char res[] = "So put your hands up high";
		char *result = str_replace(source, search, replace);
		if (my_strcmp(result, res) != 0)
			err_cnt++;
		if (result)
			free(result);
	}
	printf("\n\ntest_str_replace %s", err_cnt ? "FAILED" : "OK");
}

void test_my_getline()
{
	int err_cnt = 0;
	char *line = NULL;
	{
		FILE *f;
		int n = 0;
		f = fopen("tests/in_0.txt", "r");
		if (!f || my_getline(&line, &n, f) != 0)
			err_cnt++;
		if (f)
			fclose(f);
	}
	{
		FILE *f;
		int n = 0;
		f = fopen("tests/in_1.txt", "r");
		char res[] = "qwerty\n";
		if (!f || my_getline(&line, &n, f) != 7 || my_strcmp(line, res) != 0)
			err_cnt++;
		if (f)
			fclose(f);
	}
	{
		FILE *f;
		int n = 0;
		f = fopen("tests/in_2.txt", "r");
		char res[] = "12 - 45 + 78";
		if (!f || my_getline(&line, &n, f) != 12 || my_strcmp(line, res) != 0)
			err_cnt++;
		if (f)
			fclose(f);
	}
	{
		FILE *f;
		int n = 0;
		f = fopen("tests/in_3.txt", "r");
		char res[] = "Theatre of satire\n";
		if (!f || my_getline(&line, &n, f) != 18 || my_strcmp(line, res) != 0)
			err_cnt++;
		if (f)
			fclose(f);
	}
	{
		FILE *f;
		int n = 0;
		f = fopen("tests/in_4.txt", "r");
		char res[] = "\n";
		if (!f || my_getline(&line, &n, f) != 1 || my_strcmp(line, res) != 0)
			err_cnt++;
		if (f)
			fclose(f);
	}
	if (line)
		free(line);
	printf("\n\ntest_getline %s", err_cnt ? "FAILED" : "OK");
}

void test_my_strlen()
{
	int err_cnt = 0;
	{
		char a[] = "\n";
		if (my_strlen(a) != 1)
			err_cnt++;
	}
	{
		char a[] = "";
		if (my_strlen(a) != 0)
			err_cnt++;
	}
	{
		char a[] = "1";
		if (my_strlen(a) != 1)
			err_cnt++;
	}
	{
		char a[] = "12";
		if (my_strlen(a) != 2)
			err_cnt++;
	}
	{
		char a[] = "1 2\n";
		if (my_strlen(a) != 4)
			err_cnt++;
	}
	printf("\n\ntest_my_strlen %s", err_cnt ? "FAILED" : "OK");
}

void test_my_strcmp()
{
	int err_cnt = 0;
	{
		char a[] = "high";
		char b[] = "high";
		if (my_strcmp(a, b) != 0)
			err_cnt++;
	}
	{
		char a[] = "high";
		char b[] = "hopp";
		if (my_strcmp(a, b) != 'i' - 'o')
			err_cnt++;
	}
	{
		char a[] = "high";
		char b[] = "highe";
		if (my_strcmp(a, b) != -('e'))
			err_cnt++;
	}
	{
		char a[] = "highe";
		char b[] = "high";
		if (my_strcmp(a, b) != 'e')
			err_cnt++;
	}
	{
		char a[] = "";
		char b[] = "";
		if (my_strcmp(a, b) != 0)
			err_cnt++;
	}
	{
		char a[] = "";
		char b[] = "highe";
		if (my_strcmp(a, b) != -('h'))
			err_cnt++;
	}
	printf("\n\ntest_my_strcmp %s", err_cnt ? "FAILED" : "OK");
}

int main()
{
	test_str_replace();
	test_my_getline();
	test_my_strlen();
	test_my_strcmp();
	
	return 0;
}