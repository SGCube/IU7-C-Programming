#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

#define OK 0
#define ERR_ALLOC -4
#define ERR_NOWORDS -5

#define MAX_LEN 100
#define PASSED 1
#define FAILED 0

int test_find_words(char *txt, char res[][MAX_LEN], int kol)
{
	char *words = malloc(MAX_LEN * sizeof(char));
	int nw = find_words(txt, &words);
	if (nw != kol)
	{
		if (words)
			free(words);
		return FAILED;
	}
	else
	{
		char *ptr = words;
		for (int i = 0; i < nw; i++)
		{
			if (strcmp(ptr, res[i]) != 0)
			{
				free(words);
				return FAILED;
			}
			ptr += MAX_LEN;
		}
	}
	free(words);
	return PASSED;
}

void test_find_words_run(void)
{
	printf("find_words:\n");
	{
		char txt[] = "  ; , .  ";
		char *words = malloc(MAX_LEN * sizeof(char));
		printf("#1 %s\n",
			(find_words(txt, &words) != 0) ? "PASSED" : "FAILED");
		if (words)
			free(words);
	}
	{
		char txt[] = "aaa";
		char res[][MAX_LEN] = { "aaa" };
		printf("#2 %s\n",
			(test_find_words(txt, res, 1)) ? "PASSED" : "FAILED");
	}
	{
		char txt[] = "  ; aaa, .  ";
		char res[][MAX_LEN] = { "aaa" };
		printf("#3 %s\n",
			(test_find_words(txt, res, 1)) ? "PASSED" : "FAILED");
	}
	{
		char txt[] = "  ; aaa,bbb .c  dd";
		char res[][MAX_LEN] = { "aaa", "bbb", "c", "dd" };
		printf("#4 %s\n",
			(test_find_words(txt, res, 4)) ? "PASSED" : "FAILED");
	}
	{
		char txt[] = "  ; aaa,bbb .c  dd\nbb .aaa.dd cc";
		char res[][MAX_LEN] = { "aaa", "bbb", "c", "dd",
			"bb", "aaa", "dd", "cc" };
		printf("#5 %s\n",
			(test_find_words(txt, res, 8)) ? "PASSED" : "FAILED");
	}
}

int main()
{
	test_find_words_run();
	return 0;
}