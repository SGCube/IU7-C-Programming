/**
 * \file test.c
 * \brief Module auto-tests
 * \details Source code of automatic module tests
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"
#include "arr_io.h"
#include "arr_sort.h"

#define FAILED 0
#define PASSED 1

void errmsg(int rc)
{
	switch (rc)
	{
		case ERR_FILE:
			printf("FILE I/O ERROR!\n");
			break;
		case ERR_EMPTY:
			printf("EMPTY FILE!\n");
			break;
		case ERR_INPUT:
			printf("INVALID DATA!\n");
			break;
		case ERR_MEMORY:
			printf("MEMORY ERROR!\n");
			break;
		case NONE_TO_SORT:
			printf("NO DATA TO SORT!\n");
			break;
		case ERR_ARG:
			printf("ARGUMENT ERROR!\n");
			break;
		case OK:
			break;
		default:
			printf("UNKNOWN ERROR!\n");
	}
}

/**
 * \fn int arr_compare(int *pb, int *pe, int *_pb, int *_pe)
 * \brief Array compare function
 * \details Function, which compares two arrays
 * \param [in] *pb pointer to 1st element in 1st array
 * \param [in] *pe pointer to after last element in 1st array
 * \param [in] *_pb pointer to 1st element in 2nd array
 * \param [in] *_pe pointer to after last element in 2nd array
 * \return ARR_EQUAL/ARR_NOT_EQUAL
**/
int arr_compare(void *pa1, void *pa2, void *pd1, void *pd2)
{
	char *pb1 = (char *) pa1;
	char *pe1 = (char *) pa2;
	char *pb2 = (char *) pd1;
	char *pe2 = (char *) pd2;
	if (pe1 - pb1 != pe2 - pb2)
		return ARR_NOT_EQUAL;
	for (char *pc1 = pb1, *pc2 = pb2; pc1 < pe1; pc1++, pc2++)
		if (*pc1 != *pc2)
			return ARR_NOT_EQUAL;
	return ARR_EQUAL;
}

int test_read_array(int rc, int *arr, int n, FILE *f)
{
	if (!arr || n <= 0 || !f)
		return ERR_ARG;
	
	int rcc = 0;
	int *pa = NULL, *pb = NULL;
	
	rcc = array_len(f);
	if (rc == ERR_EMPTY || rc == ERR_INPUT)
	{
		if (rcc == rc)
			return PASSED;
		else
			return FAILED;
	}
	if (rcc != n)
		return FAILED;
	
	pa = malloc(n * sizeof(int));
	if (!pa)
		return ERR_MEMORY;
		
	rewind(f);
	rcc = read_array(f, pa, &pb, n);
	if (rcc != OK)
	{
		free(pa);
		return rc;
	}
	if (arr_compare(pa, pb, arr, arr + n) == ARR_EQUAL)
		rcc = PASSED;
	else
		rcc = FAILED;
	free(pa);
	return rcc;
}

/**
 * \fn void test_read_array(void)
 * \brief Test function for read_array()
**/
void test_read_array_call(void)
{
	printf("func: read_array\n");
	{
		int arr[] = { 5 };
		printf("#1\t");
		FILE *f = fopen("tests/in_0.txt", "r");
		if (!f)
			printf("FILE I/O ERROR!\n");
		else
		{
			int rc = test_read_array(ERR_EMPTY,
				arr, sizeof(arr)/sizeof(arr[0]), f);
			if (rc == PASSED)
				printf("PASSED\n");
			else if (rc == FAILED)
				printf("FAILED\n");
			else
				errmsg(rc);
			fclose(f);
		}
	}
	{
		int arr[] = { 5 };
		printf("#2\t");
		FILE *f = fopen("tests/in_1.txt", "r");
		if (!f)
			printf("FILE I/O ERROR!\n");
		else
		{
			int rc = test_read_array(ERR_INPUT,
				arr, sizeof(arr)/sizeof(arr[0]), f);
			if (rc == PASSED)
				printf("PASSED\n");
			else if (rc == FAILED)
				printf("FAILED\n");
			else
				errmsg(rc);
			fclose(f);
		}
	}
	{
		int arr[] = { 5 };
		printf("#3\t");
		FILE *f = fopen("tests/in_2.txt", "r");
		if (!f)
			printf("FILE I/O ERROR!\n");
		else
		{
			int rc = test_read_array(ERR_INPUT,
				arr, sizeof(arr)/sizeof(arr[0]), f);
			if (rc == PASSED)
				printf("PASSED\n");
			else if (rc == FAILED)
				printf("FAILED\n");
			else
				errmsg(rc);
			fclose(f);
		}
	}
	{
		int arr[] = { 5 };
		printf("#4\t");
		FILE *f = fopen("tests/in_4.txt", "r");
		if (!f)
			printf("FILE I/O ERROR!\n");
		else
		{
			int rc = test_read_array(OK,
				arr, sizeof(arr)/sizeof(arr[0]), f);
			if (rc == PASSED)
				printf("PASSED\n");
			else if (rc == FAILED)
				printf("FAILED\n");
			else
				errmsg(rc);
			fclose(f);
		}
	}
	{
		int arr[] = { 5, 5, 4, -5, 0, 6, 0, 7, 0, 6 };
		printf("#5\t");
		FILE *f = fopen("tests/in_8.txt", "r");
		if (!f)
			printf("FILE I/O ERROR!\n");
		else
		{
			int rc = test_read_array(OK,
				arr, sizeof(arr)/sizeof(arr[0]), f);
			if (rc == PASSED)
				printf("PASSED\n");
			else if (rc == FAILED)
				printf("FAILED\n");
			else
				errmsg(rc);
			fclose(f);
		}
	}
	printf("\n");
}

int test_key(int rc, int *arr1, int n1, int *arr2, int n2)
{
	if (!arr1 || !arr2 || n1 <= 0 || n2 < 0)
		return ERR_ARG;
	int *pb_src = arr1, *pe_src = arr1 + n1;
	int *pb_dst = NULL, *pe_dst = NULL;
	float avg;
	int rcc = OK, n = 0;
	
	n = arr_avg(pb_src, pe_src, &avg);
	if (n <= 0)
	{
		rcc = n;
		if (n == 0)
			rcc = NONE_TO_SORT;
		if (rcc != rc)
			return FAILED;
		else
			return PASSED;
	}
	else if (rc != OK)
		return FAILED;
	
	if (n != n2)
		return FAILED;
	
	pb_dst = calloc(n, n * sizeof(int));
	if (!pb_dst)
		return ERR_MEMORY;
	
	rcc = key(pb_src, pe_src, pb_dst, &pe_dst, avg);
	if (rcc == OK)
	{
		if (arr_compare(pb_dst, pe_dst, arr2, arr2 + n2) == ARR_EQUAL)
			rcc = PASSED;
		else
			rcc = FAILED;
	}
	else
		rcc = FAILED;
	free(pb_dst);
	return rcc;
}

/**
 * \fn void test_key(void)
 * \brief Test function for key()
**/
void test_key_call()
{
	printf("func: key\n");
	//NOTHING LEFT AFTER FUNCTION
	{
		//one number
		{
			int arr[] = { 1 };
			printf("#1\t");
			int rc = test_key(NONE_TO_SORT, arr, sizeof(arr)/sizeof(arr[0]),
				arr, 0);
			if (rc == PASSED)
				printf("PASSED\n");
			else if (rc == FAILED)
				printf("FAILED\n");
			else
				errmsg(rc);
		}
		//several same number
		{
			int arr[] = { 5, 5, 5, 5, 5, 5 };
			printf("#2\t");
			int rc = test_key(NONE_TO_SORT, arr, sizeof(arr)/sizeof(arr[0]),
				arr, 0);
			if (rc == PASSED)
				printf("PASSED\n");
			else if (rc == FAILED)
				printf("FAILED\n");
			else
				errmsg(rc);
		}
		//several various numbers
		{
			int arr[] = { 3, 6, 4, 1, 2, 5 };
			int arr_dst[] = { 6, 4, 5 };
			printf("#3\t");
			int rc = test_key(OK, arr, sizeof(arr)/sizeof(arr[0]),
				arr_dst, sizeof(arr_dst)/sizeof(arr_dst[0]));
			if (rc == PASSED)
				printf("PASSED\n");
			else if (rc == FAILED)
				printf("FAILED\n");
			else
				errmsg(rc);
		}
	}
	printf("\n");
}

/**
 * \fn void test_compar_int(void)
 * \brief Test function for compar_int()
**/
void test_compar_int()
{
	int a, b;
	int *pa = &a;
	int *pb = &b;
	printf("func: compar_int\n");
	//FIRST LARGER
	{
		a = 5;
		b = 1;
		printf("#0\t");
		if (compar_int(pa, pb) > 0)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//EQUAL
	{
		a = 5;
		b = 5;
		printf("#1\t");
		if (compar_int(pa, pb) == 0)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//FIRST LARGER
	{
		a = 1;
		b = 5;
		printf("#2\t");
		if (compar_int(pa, pb) < 0)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	printf("\n");
}

/**
 * \fn void test_shift(void)
 * \brief Test function for shift()
**/
void test_shift()
{
	int *pb = NULL, *pe = NULL;
	printf("func: shift\n");
	//none to shift
	{
		int arr[] = { 1 };
		int arr_res[] = { 1 };
		pb = arr;
		pe = pb + 1;
		printf("#0\t");
		shift((char *)pb, (char *)pe, sizeof(int));
		if (arr_compare(arr, arr + 1, arr_res, arr_res + 1) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//two elements
	{
		int arr[] = { 1, 3 };
		int arr_res[] = { 3, 1 };
		pb = arr;
		pe = pb + 2;
		printf("#1\t");
		shift((char *)pb, (char *)pe, sizeof(int));
		if (arr_compare(arr, arr + 2, arr_res, arr_res + 2) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//several elements
	{
		int arr[] = { 1, 5, 0, 3 };
		int arr_res[] = { 3, 1, 5, 0 };
		pb = arr;
		pe = pb + 4;
		printf("#2\t");
		shift((char *)pb, (char *)pe, sizeof(int));
		if (arr_compare(arr, arr + 4, arr_res, arr_res + 4) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	printf("\n");
}

/**
 * \fn void test_mysort(void)
 * \brief Test function for mysort()
**/
void test_mysort()
{
	int *pb = NULL;
	int n = 0;
	printf("func: mysort\n");
	//one element
	{
		int arr[] = { 1 };
		int arr_res[] = { 1 };
		pb = arr;
		n = 1;
		printf("#0\t");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//all equal
	{
		int arr[] = { 1, 1, 1, 1, 1 };
		int arr_res[] = { 1, 1, 1, 1, 1 };
		pb = arr;
		n = 5;
		printf("#1\t");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//sorted already
	{
		int arr[] = { 1, 2, 3, 4, 5 };
		int arr_res[] = { 1, 2, 3, 4, 5 };
		pb = arr;
		n = 5;
		printf("#2\t");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//invert-sorted
	{
		int arr[] = { 5, 4, 3, 2, 1 };
		int arr_res[] = { 1, 2, 3, 4, 5 };
		pb = arr;
		n = 5;
		printf("#3\t");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//some elements are equal
	{
		int arr[] = { 1, 2, 3, 2, 0 };
		int arr_res[] = { 0, 1, 2, 2, 3 };
		pb = arr;
		n = 5;
		printf("#4\t");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//all various
	{
		int arr[] = { 1, 0, -8, 7, 5 };
		int arr_res[] = { -8, 0, 1, 5, 7 };
		pb = arr;
		n = 5;
		printf("#5\t");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//float elemetnts
	{
		float arr[] = { 1.2, 0.1, -8.45, 7.8888, 5 };
		float arr_res[] = { -8.45, 0.1, 1.2, 5, 7.8888 };
		float *pbb = arr;
		n = 5;
		printf("#6\t");
		mysort(pbb, n, sizeof(float), compar_float);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	//char elemetnts
	{
		char arr[] = { 'd', '!', 'c', 'a', 'A' };
		char arr_res[] = { '!', 'A', 'a', 'c', 'd' };
		char *pbb = arr;
		n = 5;
		printf("#7\t");
		mysort(pbb, n, sizeof(char), compar_char);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
}

int main()
{
	test_read_array_call();
	test_key_call();
	test_compar_int();
	test_shift();
	test_mysort();
	return 0;
}