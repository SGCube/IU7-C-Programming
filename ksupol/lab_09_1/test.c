#include <stdio.h>
#include <string.h>
#include "str.h"

void test_my_srtcspn()
{
	int err_cnt = 0;
	{
		char str[] = "what a wonderful day!";
		char key[] = "whatever";
		if (my_strcspn(str, key) != strcspn(str, key))
			err_cnt++;
	}
	{
		char str[] = "what a wonderful day!";
		char key[] = "r";
		if (my_strcspn(str, key) != strcspn(str, key))
			err_cnt++;
	}
	{
		char str[] = "what a wonderful day!";
		char key[] = "w";
		if (my_strcspn(str, key) != strcspn(str, key))
			err_cnt++;
	}
	{
		char str[] = "what a wonderful day!";
		char key[] = "B";
		if (my_strcspn(str, key) != strcspn(str, key))
			err_cnt++;
	}
	{
		char str[] = "what a wonderful day!";
		char key[] = "!";
		if (my_strcspn(str, key) != strcspn(str, key))
			err_cnt++;
	}
	{
		char str[] = "W";
		char key[] = "Bobby and Robby";
		if (my_strcspn(str, key) != strcspn(str, key))
			err_cnt++;
	}
	{
		char str[] = "Bobby and Robby";
		char key[] = "Bobby and Robby";
		if (my_strcspn(str, key) != strcspn(str, key))
			err_cnt++;
	}
	printf("\n\ntest_my_strcspn %s", err_cnt ? "FAILED" : "OK");
}

void test_my_strchr()
{
	int err_cnt = 0;
	{
		char str[] = "I’ve been searching for an answer";
		char sym = 'I';
		if (my_strchr(str, sym) != strchr(str, sym))
			err_cnt++;
	}
	{
		char str[] = "I’ve been searching for an answer";
		char sym = 'a';
		if (my_strchr(str, sym) != strchr(str, sym))
			err_cnt++;
	}
	{
		char str[] = "I’ve been searching for an answer";
		char sym = '\0';
		if (my_strchr(str, sym) != strchr(str, sym))
			err_cnt++;
	}
	printf("\n\ntest_my_strcspn %s", err_cnt ? "FAILED" : "OK");
}

int main()
{
	test_my_srtcspn();
	test_my_strchr();
	return 0;
}