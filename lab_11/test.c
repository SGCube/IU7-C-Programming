#include <stdio.h>
#include <string.h>
#include "mystdio.h"

int main(void)
{
	{
		printf("#1: s != NULL, n = 0\n");
		char str1[20], str2[20];
		int rc1 = my_snprintf(str1, 0, "TEST1");
		int rc2 = snprintf(str2, 0, "TEST1");
		printf("return: %d %d\n", rc1, rc2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#2: s = NULL, n = 0\n");
		char *str1 = NULL, *str2 = NULL;
		int rc1 = my_snprintf(str1, 0, "TEST2");
		int rc2 = snprintf(str2, 0, "TEST2");
		printf("return: %d %d\n", rc1, rc2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#3: no %%s, n = strlen(format) + 1\n");
		char str1[20], str2[20];
		int rc1 = my_snprintf(str1, 6, "TEST3");
		int rc2 = snprintf(str2, 6, "TEST3");
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#4: %%s, n = strlen(arg) + 1\n");
		char str1[20], str2[20];
		int rc1 = my_snprintf(str1, 6, "%s", "TEST4");
		int rc2 = snprintf(str2, 6, "%s", "TEST4");
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#5: %%s!, n = strlen(arg) + 2\n");
		char str1[20], str2[20];
		int rc1 = my_snprintf(str1, 7, "%s!", "TEST5");
		int rc2 = snprintf(str2, 7, "%s!", "TEST5");
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#6: %%s%%s%%s\n");
		char str1[20], str2[20];
		int rc1 = my_snprintf(str1, 7, "%s%s%s", "AB", "C", "XYZ");
		int rc2 = snprintf(str2, 7, "%s%s%s", "AB", "C", "XYZ");
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	/*{
		printf("#7: %%s%%%%\n");
		char str1[20], str2[20];
		const char *s = "%%s%%";
		int rc1 = my_snprintf(str1, 7, s);
		int rc2 = snprintf(str2, 7, s);
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}*/
	{
		printf("#8: %%lld, number = 0\n");
		char str1[20], str2[20];
		long long num = 0;
		int rc1 = my_snprintf(str1, 10, "%lld", num);
		int rc2 = snprintf(str2, 10, "%lld", num);
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#9: %%lld, number < 0\n");
		char str1[20], str2[20];
		long long num = -10;
		int rc1 = my_snprintf(str1, 10, "%lld", num);
		int rc2 = snprintf(str2, 10, "%lld", num);
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#10: %%lld, number > 0\n");
		char str1[20], str2[20];
		long long num = 10;
		int rc1 = my_snprintf(str1, 10, "%lld", num);
		int rc2 = snprintf(str2, 10, "%lld", num);
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#11: %%lld, number = +MAX\n");
		char str1[50], str2[50];
		long long num = 9223372036854775807;
		int rc1 = my_snprintf(str1, 50, "%lld", num);
		int rc2 = snprintf(str2, 50, "%lld", num);
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#12: %%lld, number = -MAX\n");
		char str1[50], str2[50];
		long long int num = -9223372036854775807;
		int rc1 = my_snprintf(str1, 50, "%lld", num);
		int rc2 = snprintf(str2, 50, "%lld", num);
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#13: %%s %%lld\n");
		char str1[50], str2[50];
		long long num = 1000000000000;
		int rc1 = my_snprintf(str1, 50, "%s = %lld", "Trillion", num);
		int rc2 = snprintf(str2, 50, "%s = %lld", "Trillion", num);
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	{
		printf("#14: %%lld %%s\n");
		char str1[50], str2[50];
		long long num = 1000000000000;
		int rc1 = my_snprintf(str1, 50, "%lld is %s", num, "Trillion");
		int rc2 = snprintf(str2, 50, "%lld is %s", num, "Trillion");
		printf("return: %d %d\n", rc1, rc2);
		printf("output: %s %s\n", str1, str2);
		if (rc1 != rc2)
			printf("result: FAILED\n\n");
		else if (strcmp(str1, str2))
			printf("result: FAILED\n\n");
		else
			printf("result: PASSED\n\n");
	}
	return 0;
}