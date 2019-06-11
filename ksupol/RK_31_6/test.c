#include <stdio.h>
#include "str.h"
#include <string.h>

#define MAX 20

void test_sep_words()
{
	int err_cnt = 0;
	{
		char a[] = "I want to separate words from this line";
		char words[100][MAX];
		char result[8][MAX] = {"I", "want", "to", "separate", "words", 
								"from", "this", "line"};
		int len = 0;
		sep_words(a, words, &len);
		if (len != 8)
			err_cnt++;
		for (int i = 0; i < len; i++)
			if (strcmp(words[i],result[i]) != 0)
				err_cnt++;
	}
	{
		char a[] = "I   want    to    separate";
		char words[100][MAX];
		char result[4][MAX] = {"I", "want", "to", "separate"};
		int len = 0;
		sep_words(a, words, &len);
		if (len != 4)
			err_cnt++;
		for (int i = 0; i < len; i++)
			if (strcmp(words[i],result[i]) != 0)
				err_cnt++;
	}
	{
		char a[] = "   I   ";
		char words[100][MAX];
		char result[1][MAX] = {"I"};
		int len = 0;
		sep_words(a, words, &len);
		if (len != 1)
			err_cnt++;
		for (int i = 0; i < len; i++)
			if (strcmp(words[i],result[i]) != 0)
				err_cnt++;
	}
	{
		char a[] = "   ";
		char words[100][MAX];
		int len = 0;
		sep_words(a, words, &len);
		if (len != 0)
			err_cnt++;
	}
	if (err_cnt == 0)
		printf("test_sep_words: OK\n");
	else
		printf("test_sep_words: FAILED\n");
}

void test_del()
{
	int err_cnt = 0;
	{
		char words[3][MAX] = {"aaa", "aaa", "aaa"};
		int len = 3;
		char res[100][MAX];
		char result[1][MAX] = {"aaa"};
		del(words, &len, res);
		if (len != 1)
			err_cnt++;
		for (int i = 0; i < len; i++)
			if (strcmp(result[i], res[i]) != 0)
				err_cnt++;
	}
	{
		char words[3][MAX] = {"aaa", "abb", "aba"};
		int len = 3;
		char res[100][MAX];
		char result[3][MAX] = {"aaa", "abb", "aba"};
		del(words, &len, res);
		if (len != 3)
			err_cnt++;
		for (int i = 0; i < len; i++)
			if (strcmp(result[i], res[i]) != 0)
				err_cnt++;
	}
	{
		char words[3][MAX] = {"aaa", "abb", "aaa"};
		int len = 3;
		char res[100][MAX];
		char result[2][MAX] = {"aaa", "abb"};
		del(words, &len, res);
		if (len != 2)
			err_cnt++;
		for (int i = 0; i < len; i++)
			if (strcmp(result[i], res[i]) != 0)
				err_cnt++;
	}
	{
		char words[1][MAX] = {"aaa"};
		int len = 1;
		char res[100][MAX];
		char result[1][MAX] = {"aaa"};
		del(words, &len, res);
		if (len != 1)
			err_cnt++;
		for (int i = 0; i < len; i++)
			if (strcmp(result[i], res[i]) != 0)
				err_cnt++;
	}
	if (err_cnt == 0)
		printf("test_del: OK\n");
	else
		printf("test_del: FAILED\n");
}

int main()
{
	test_sep_words();
	test_del();
	return 0;
}