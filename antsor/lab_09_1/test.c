#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "mystring.h"

void test_my_strspn(void)
{
	printf("my_strspn:\n\n");
	{
		char str1[] = "2018";
		char str2[] = "1234567890";
		size_t s1, s2;
		s1 = my_strspn(str1, str2);
		s2 = strspn(str1, str2);
		printf("str1 = %s\nstr2 = %s\nmy_strspn = %lu, strspn = %lu\t",
			str1, str2, s1, s2);
		printf("%s\n\n", (s1 == s2) ? "PASSED" : "OK");
	}
	{
		char str1[] = "no_numbers";
		char str2[] = "1234567890";
		size_t s1, s2;
		s1 = my_strspn(str1, str2);
		s2 = strspn(str1, str2);
		printf("str1 = %s\nstr2 = %s\nmy_strspn = %lu, strspn = %lu\t",
			str1, str2, s1, s2);
		printf("%s\n\n", (s1 == s2) ? "PASSED" : "OK");
	}
	{
		char str1[] = "2018 year";
		char str2[] = "1234567890";
		size_t s1, s2;
		s1 = my_strspn(str1, str2);
		s2 = strspn(str1, str2);
		printf("str1 = %s\nstr2 = %s\nmy_strspn = %lu, strspn = %lu\t",
			str1, str2, s1, s2);
		printf("%s\n\n", (s1 == s2) ? "PASSED" : "OK");
	}
	{
		char str1[] = "";
		char str2[] = "1234567890";
		size_t s1, s2;
		s1 = my_strspn(str1, str2);
		s2 = strspn(str1, str2);
		printf("str1 = %s\nstr2 = %s\nmy_strspn = %lu, strspn = %lu\t",
			str1, str2, s1, s2);
		printf("%s\n\n", (s1 == s2) ? "PASSED" : "OK");
	}
	{
		char str1[] = "1";
		char str2[] = "1";
		size_t s1, s2;
		s1 = my_strspn(str1, str2);
		s2 = strspn(str1, str2);
		printf("str1 = %s\nstr2 = %s\nmy_strspn = %lu, strspn = %lu\t",
			str1, str2, s1, s2);
		printf("%s\n\n", (s1 == s2) ? "PASSED" : "OK");
	}
	{
		char str1[] = "111111";
		char str2[] = "1";
		size_t s1, s2;
		s1 = my_strspn(str1, str2);
		s2 = strspn(str1, str2);
		printf("str1 = %s\nstr2 = %s\nmy_strspn = %lu, strspn = %lu\t",
			str1, str2, s1, s2);
		printf("%s\n\n", (s1 == s2) ? "PASSED" : "OK");
	}
	{
		char str1[] = "2018 year";
		char str2[] = "";
		size_t s1, s2;
		s1 = my_strspn(str1, str2);
		s2 = strspn(str1, str2);
		printf("str1 = %s\nstr2 = %s\nmy_strspn = %lu, strspn = %lu\t",
			str1, str2, s1, s2);
		printf("%s\n\n", (s1 == s2) ? "PASSED" : "OK");
	}
	printf("\n");
}

void test_my_strrchr(void)
{
	printf("my_strrchr:\n\n");
	{
		char str[] = "OK!";
		int ch = '\0';
		char *c1, *c2;
		c1 = my_strrchr(str, ch);
		c2 = strrchr(str, ch);
		printf("ch = '\\0'\tstr = %s\nmy_strrchr = %ld\nstrrchr = %ld\t",
			str, c1 - str, c2 - str);
		printf("%s\n\n", (c1 == c2) ? "PASSED" : "OK");
	}
	{
		char str[] = "OK!";
		int ch = 'O';
		char *c1, *c2;
		c1 = my_strrchr(str, ch);
		c2 = strrchr(str, ch);
		printf("ch = %c\tstr = %s\nmy_strrchr = %ld\nstrrchr = %ld\t",
			ch, str, c1 - str, c2 - str);
		printf("%s\n\n", (c1 == c2) ? "PASSED" : "OK");
	}
	{
		char str[] = "OK!";
		int ch = '!';
		char *c1, *c2;
		c1 = my_strrchr(str, ch);
		c2 = strrchr(str, ch);
		printf("ch = %c\tstr = %s\nmy_strrchr = %ld\nstrrchr = %ld\t",
			ch, str, c1 - str, c2 - str);
		printf("%s\n\n", (c1 == c2) ? "PASSED" : "OK");
	}
	{
		char str[] = "OK!";
		int ch = 'A';
		char *c1, *c2;
		c1 = my_strrchr(str, ch);
		c2 = strrchr(str, ch);
		printf("ch = %c\tstr = %s\nmy_strrchr = %ld\nstrrchr = %ld (NULL)\t",
			ch, str, c1 - str, c2 - str);
		printf("%s\n\n", (c1 == c2) ? "PASSED" : "OK");
	}
	{
		char str[] = "Hello!";
		int ch = 'o';
		char *c1, *c2;
		c1 = my_strrchr(str, ch);
		c2 = strrchr(str, ch);
		printf("ch = %c\tstr = %s\nmy_strrchr = %ld\nstrrchr = %ld\t",
			ch, str, c1 - str, c2 - str);
		printf("%s\n\n", (c1 == c2) ? "PASSED" : "OK");
	}
	{
		char str[] = "Hello!";
		int ch = 'l';
		char *c1, *c2;
		c1 = my_strrchr(str, ch);
		c2 = strrchr(str, ch);
		printf("ch = %c\tstr = %s\nmy_strrchr = %ld\nstrrchr = %ld\t",
			ch, str, c1 - str, c2 - str);
		printf("%s\n\n", (c1 == c2) ? "PASSED" : "OK");
	}
	printf("\n");
}

int main(void)
{
	fflush(stdout);
	test_my_strspn();
	test_my_strrchr();
	return 0;
}