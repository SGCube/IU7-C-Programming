#include <stdio.h>
#include <assert.h>
#include "error.h"
#include "matrix.h"

void test_sum(FILE *f1, FILE *f2, FILE *f3)
{
	assert(f1 && f2 && f3);
	matrix_t ma1 = create();
	matrix_t ma2 = create();
	matrix_t ma3 = create();
	matrix_t ma = create();
	
	assert(read(ma1, f1) == OK);
	assert(read(ma2, f2) == OK);
	assert(read(ma3, f3) == OK);
	
	assert(sum(ma1, ma2, ma) == OK);
	if (compare(ma3, ma) == 1)
		printf("OK\n");
	else
		printf("FAILED\n");
	
	destroy(ma1);
	destroy(ma2);
	destroy(ma3);
	destroy(ma);
	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void test_multiply(FILE *f1, FILE *f2, FILE *f3)
{
	assert(f1 && f2 && f3);
	matrix_t ma1 = create();
	matrix_t ma2 = create();
	matrix_t ma3 = create();
	matrix_t ma = create();
	
	assert(read(ma1, f1) == OK);
	assert(read(ma2, f2) == OK);
	assert(read(ma3, f3) == OK);
	
	assert(multiply(ma1, ma2, ma) == OK);
	if (compare(ma3, ma) == 1)
		printf("OK\n");
	else
		printf("FAILED\n");
	
	destroy(ma1);
	destroy(ma2);
	destroy(ma3);
	destroy(ma);
	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void test_sum_call(void)
{
	printf("matrsum:\n");
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#1: ");
		f1 = fopen("tests_a/in_1_0.txt", "r");
		f2 = fopen("tests_a/in_1_1.txt", "r");
		f3 = fopen("tests_a/out_1.txt", "r");
		test_sum(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#2: ");
		f1 = fopen("tests_a/in_2_0.txt", "r");
		f2 = fopen("tests_a/in_2_1.txt", "r");
		f3 = fopen("tests_a/out_2.txt", "r");
		test_sum(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#3: ");
		f1 = fopen("tests_a/in_3_0.txt", "r");
		f2 = fopen("tests_a/in_3_1.txt", "r");
		f3 = fopen("tests_a/out_3.txt", "r");
		test_sum(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#4: ");
		f1 = fopen("tests_a/in_4_0.txt", "r");
		f2 = fopen("tests_a/in_4_1.txt", "r");
		f3 = fopen("tests_a/out_4.txt", "r");
		test_sum(f1, f2, f3);
	}
	printf("\n");
}

void test_mult_call(void)
{
	printf("matrmult:\n");
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#1: ");
		f1 = fopen("tests_m/in_1_0.txt", "r");
		f2 = fopen("tests_m/in_1_1.txt", "r");
		f3 = fopen("tests_m/out_1.txt", "r");
		test_multiply(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#2: ");
		f1 = fopen("tests_m/in_2_0.txt", "r");
		f2 = fopen("tests_m/in_2_1.txt", "r");
		f3 = fopen("tests_m/out_2.txt", "r");
		test_multiply(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#3: ");
		f1 = fopen("tests_m/in_3_0.txt", "r");
		f2 = fopen("tests_m/in_3_1.txt", "r");
		f3 = fopen("tests_m/out_3.txt", "r");
		test_multiply(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#4: ");
		f1 = fopen("tests_m/in_4_0.txt", "r");
		f2 = fopen("tests_m/in_4_1.txt", "r");
		f3 = fopen("tests_m/out_4.txt", "r");
		test_multiply(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#5: ");
		f1 = fopen("tests_m/in_5_0.txt", "r");
		f2 = fopen("tests_m/in_5_1.txt", "r");
		f3 = fopen("tests_m/out_5.txt", "r");
		test_multiply(f1, f2, f3);
	}
	{
		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		printf("#6: ");
		f1 = fopen("tests_m/in_6_0.txt", "r");
		f2 = fopen("tests_m/in_6_1.txt", "r");
		f3 = fopen("tests_m/out_6.txt", "r");
		test_multiply(f1, f2, f3);
	}
	printf("\n");
}

int main(void)
{
	test_sum_call();
	test_mult_call();
	return 0;
}