#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "mystring.h"
#include "errcode.h"

void test_my_getline(void)
{
	ssize_t n = 0;
	int rc;
	char str0[] = "";
	char str1[] = "\n";
	char str2[] = "1\n";
	char str3[] = "123456\n";
	char str4[] = "1234 56\n";
	char str5[] = "1234 56 \n";
	char str6[] = "1234567890123456789012345678901234567890"
		"1234567890123456789012\n";
	char str7[] = "1234567890123456789012345678901234567890"
		"12345678901234567890123\n";
	char str8[] = "1234567890123456789012345678901234567890"
		"123456789012345678901234123456\n";
	char str9[] = "ok!";
	char *str[] = { str0, str1, str2, str3, str4, str5, str6, str7,
		str8, str9 };
	char *dst = NULL;
	int len[] = { 0, 1, 2, 7, 8, 9, 64, 65, 71, 3 };
	
	printf("getline:\n");
	FILE *fe = fopen("utests/getline_empty.txt", "r");
	assert(fe);
	
	printf("#0 ");
	printf("%s\n", (my_getline(&dst, &n, fe) == -1) ? "PASSED" : "FAILED");
	fclose(fe);
	
	FILE *f = fopen("utests/getline.txt", "r");
	assert(f);
	
	for (int i = 1; i < sizeof(len) / sizeof(int); i++)
	{
		printf("#%d ", i);
		rc = my_getline(&dst, &n, f);
		if (rc == ERR_ALLOC)
			printf("Memory allocation!\n");
		else if (rc == -1)
			printf("Input error!\n");
		else
			printf("%s\n", (my_strcmp(dst, str[i]) == 0) ?
				"PASSED" : "FAILED");
	}
	
	if (dst)
		free(dst);
	fclose(f);
	printf("\n");
}

void test_str_replace(void)
{
	printf("str_replace:\n");
	{
		printf("#1 ");
		char *src = "abcdef";
		char *chk = "abcdef";
		char *search = "g";
		char *replace = "h";
		char *dst = NULL;
		dst = str_replace(src, search, replace);
		if (dst)
		{
			printf("%s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
			free(dst);
		}
		else
			printf("NULL!\n");
	}
	{
		printf("#2 ");
		char *src = "abcdef";
		char *chk = "abhdef";
		char *search = "c";
		char *replace = "h";
		char *dst = NULL;
		dst = str_replace(src, search, replace);
		if (dst)
		{
			printf("%s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
			free(dst);
		}
		else
			printf("NULL!\n");
	}
	{
		printf("#3 ");
		char *src = "abcabc";
		char *chk = "abeabe";
		char *search = "c";
		char *replace = "e";
		char *dst = NULL;
		dst = str_replace(src, search, replace);
		if (dst)
		{
			printf("%s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
			free(dst);
		}
		else
			printf("NULL!\n");
	}
	{
		printf("#4 ");
		char *src = "abcdef";
		char *chk = "!";
		char *search = "abcdef";
		char *replace = "!";
		char *dst = NULL;
		dst = str_replace(src, search, replace);
		if (dst)
		{
			printf("%s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
			free(dst);
		}
		else
			printf("NULL!\n");
	}
	{
		printf("#5 ");
		char *src = "abcdef";
		char *chk = "";
		char *search = "abcdef";
		char *replace = "";
		char *dst = NULL;
		dst = str_replace(src, search, replace);
		if (dst)
		{
			printf("%s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
			free(dst);
		}
		else
			printf("NULL!\n");
	}
	{
		printf("#6 ");
		char *src = "aaa";
		char *chk = "bbbbbb";
		char *search = "a";
		char *replace = "bb";
		char *dst = NULL;
		dst = str_replace(src, search, replace);
		if (dst)
		{
			printf("%s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
			free(dst);
		}
		else
			printf("NULL!\n");
	}
	{
		printf("#7 ");
		char *src = "aaaaaaa";
		char *chk = "bbba";
		char *search = "aa";
		char *replace = "b";
		char *dst = NULL;
		dst = str_replace(src, search, replace);
		if (dst)
		{
			printf("%s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
			free(dst);
		}
		else
			printf("NULL!\n");
	}
	{
		printf("#8 ");
		char *src = "";
		char *chk = "";
		char *search = "";
		char *replace = "abc";
		char *dst = NULL;
		dst = str_replace(src, search, replace);
		if (dst)
		{
			printf("%s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
			free(dst);
		}
		else
			printf("NULL!\n");
	}
	printf("\n");
}

void test_my_strlen(void)
{
	printf("my_strlen:\n");
	{
		char *str = "";
		printf("#1 %s\n", (my_strlen(str) == 0) ? "PASSED" : "FAILED");
	}
	{
		char *str = "\n";
		printf("#2 %s\n", (my_strlen(str) == 1) ? "PASSED" : "FAILED");
	}
	{
		char *str = "a";
		printf("#3 %s\n", (my_strlen(str) == 1) ? "PASSED" : "FAILED");
	}
	{
		char *str = "a\n";
		printf("#4 %s\n", (my_strlen(str) == 2) ? "PASSED" : "FAILED");
	}
	{
		char *str = "ab de\n";
		printf("#5 %s\n", (my_strlen(str) == 6) ? "PASSED" : "FAILED");
	}
	printf("\n");
}

void test_my_strcmp(void)
{
	printf("my_strcmp:\n");
	{
		char *s1 = "";
		char *s2 = "";
		printf("#1 %s\n", (my_strcmp(s1, s2) == 0) ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "0";
		char *s2 = "";
		printf("#2 %s\n", (my_strcmp(s1, s2) == '0') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "a";
		char *s2 = "a";
		printf("#3 %s\n", (my_strcmp(s1, s2) == 0) ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "c";
		char *s2 = "a";
		printf("#4 %s\n",
			(my_strcmp(s1, s2) == 'c' - 'a') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "a";
		char *s2 = "c";
		printf("#5 %s\n",
			(my_strcmp(s1, s2) == 'a' - 'c') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "abc";
		char *s2 = "aec";
		printf("#6 %s\n",
			(my_strcmp(s1, s2) == 'b' - 'e') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "aeb";
		char *s2 = "abc";
		printf("#7 %s\n",
			(my_strcmp(s1, s2) == 'e' - 'b') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "abc";
		char *s2 = "ab";
		printf("#8 %s\n",
			(my_strcmp(s1, s2) == 'c') ? "PASSED" : "FAILED");
	}
	printf("\n");
}

void test_my_strcmpn(void)
{
	printf("my_strcmpn:\n");
	{
		char *s1 = "";
		char *s2 = "";
		printf("#1 %s\n",
			(my_strcmpn(s1, s2, 0) == 0) ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "0";
		char *s2 = "";
		printf("#2 %s\n",
			(my_strcmpn(s1, s2, 1) == '0') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "a";
		char *s2 = "a";
		printf("#3 %s\n",
			(my_strcmpn(s1, s2, 1) == 0) ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "c";
		char *s2 = "a";
		printf("#4 %s\n",
			(my_strcmpn(s1, s2, 1) == 'c' - 'a') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "a";
		char *s2 = "c";
		printf("#5 %s\n",
			(my_strcmpn(s1, s2, 1) == 'a' - 'c') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "abc";
		char *s2 = "aec";
		printf("#6 %s\n",
			(my_strcmpn(s1, s2, 3) == 'b' - 'e') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "aeb";
		char *s2 = "abc";
		printf("#7 %s\n",
			(my_strcmpn(s1, s2, 3) == 'e' - 'b') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "abc";
		char *s2 = "ab";
		printf("#8 %s\n",
			(my_strcmpn(s1, s2, 3) == 'c') ? "PASSED" : "FAILED");
	}
	{
		char *s1 = "abc";
		char *s2 = "ab";
		printf("#9 %s\n",
			(my_strcmpn(s1, s2, 2) == 0) ? "PASSED" : "FAILED");
	}
	printf("\n");
}

void test_my_strcat_s(void)
{
	printf("strcat_s:\n");
	{
		char dst[10] = "";
		char *src = "";
		char chk[10] = "";
		my_strcat_s(dst, 0, src);
		printf("#1 %s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
	}
	{
		char dst[10] = "";
		char *src = "a";
		char chk[10] = "a";
		my_strcat_s(dst, 1, src);
		printf("#2 %s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
	}
	{
		char dst[10] = "a";
		char *src = "";
		char chk[10] = "a";
		my_strcat_s(dst, 0, src);
		printf("#3 %s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
	}
	{
		char dst[10] = "ab";
		char *src = "cd";
		char chk[10] = "abcd";
		my_strcat_s(dst, 2, src);
		printf("#4 %s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
	}
	{
		char dst[10] = "abcde";
		char *src = "fgh";
		char chk[10] = "abcdefg";
		my_strcat_s(dst, 2, src);
		printf("#5 %s\n", (my_strcmp(dst, chk) == 0) ? "PASSED" : "FAILED");
	}
	printf("\n");
}

int main(void)
{
	test_my_getline();
	test_str_replace();
	test_my_strlen();
	test_my_strcmp();
	test_my_strcmpn();
	test_my_strcat_s();
	return 0;
}