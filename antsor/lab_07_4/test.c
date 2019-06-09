/**
 * \file test.c
 * \brief Module auto-tests
 * \details Source code of automatic module tests
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "iofile.h"
#include "sort.h"

#define OK 0
#define ERR_EMPTY -3
#define ERR_INPUT -4
#define ERR_OUTPUT -5
#define ERR_MEMORY -6
#define NONE_TO_SORT -7

#define ARR_EQUAL -10
#define ARR_NOT_EQUAL -11

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

/*int arr_fcompare(float *pb1, float *pe1, float *pb2, float *pe2)
{
	if (pe1 - pb1 != pe2 - pb2)
		return ARR_NOT_EQUAL;
	for (float *pc1 = pb1, *pc2 = pb2; pc1 < pe1; pc1++, pc2++)
		if (*pc1 != *pc2)
			return ARR_NOT_EQUAL;
	return ARR_EQUAL;
}*/

/**
 * \fn void test_read_array(void)
 * \brief Test function for read_array()
**/
void test_read_array(void)
{
	int *pa, *pb;
	FILE *fin;
	printf("func: read_array\n");
	//Invalid data tests
	{
		//empty file
		{
			pa = NULL;
			pb = NULL;
			fin = fopen("tests/in_0.txt", "r");
			assert(fin);
			printf("#0: ");
			if (read_array(fin, &pa, &pb) != ERR_EMPTY)
				printf("FAILED\n");
			else
				printf("OK\n");
			fclose(fin);
			if (pa)
				free(pa);
		}
		//char element
		{
			pa = NULL;
			pb = NULL;
			fin = fopen("tests/in_1.txt", "r");
			assert(fin);
			printf("#1: ");
			if (read_array(fin, &pa, &pb) != ERR_INPUT)
				printf("FAILED\n");
			else
				printf("OK\n");
			if (pa)
				free(pa);
		}
		//float element
		{
			pa = NULL;
			pb = NULL;
			fin = fopen("tests/in_2.txt", "r");
			assert(fin);
			printf("#2: ");
			if (read_array(fin, &pa, &pb) != ERR_INPUT)
				printf("FAILED\n");
			else
				printf("OK\n");
			if (pa)
				free(pa);
		}
	}
	//Valid data tests
	{
		//one number
		{
			pa = NULL;
			pb = NULL;
			int arr[] = { 5 };
			fin = fopen("tests/in_4.txt", "r");
			assert(fin);
			printf("#3: ");
			if (read_array(fin, &pa, &pb) != OK)
				printf("FAILED\n");
			else if (arr_compare(pa, pb, arr, arr + 1) == ARR_EQUAL)
				printf("OK\n");
			else
				printf("FAILED\n");
			if (pa)
				free(pa);
			fclose(fin);
		}
		//several numbers
		{
			pa = NULL;
			pb = NULL;
			int arr[] = { 5, 5, 4, -5, 0, 6, 0, 7, 0, 6 };
			fin = fopen("tests/in_8.txt", "r");
			assert(fin);
			printf("#4: ");
			if (read_array(fin, &pa, &pb) != OK)
				printf("FAILED\n");
			else if (arr_compare(pa, pb, arr, arr + 10) == ARR_EQUAL)
				printf("OK\n");
			else
				printf("FAILED\n");
			if (pa)
				free(pa);
			fclose(fin);
		}
	}
	printf("\n");
}

/**
 * \fn void test_key(void)
 * \brief Test function for key()
**/
void test_key()
{
	int *pb_src = NULL, *pe_src = NULL;
	int *pb_dst = NULL, *pe_dst = NULL;
	printf("func: key\n");
	//NOTHING LEFT AFTER FUNCTION
	{
		//one number
		{
			int arr[] = { 1 };
			pb_src = arr;
			pe_src = arr + 1;
			pb_dst = NULL;
			pe_dst = NULL;
			printf("#0: ");
			if (key(pb_src, pe_src, &pb_dst, &pe_dst) != NONE_TO_SORT)
				printf("FAILED\n");
			else
				printf("OK\n");
			if (pb_dst)
				free(pb_dst);
		}
		//several same number
		{
			int arr[] = { 5, 5, 5, 5, 5, 5 };
			pb_src = arr;
			pe_src = arr + 6;
			pb_dst = NULL;
			pe_dst = NULL;
			printf("#1: ");
			if (key(pb_src, pe_src, &pb_dst, &pe_dst) != NONE_TO_SORT)
				printf("FAILED\n");
			else
				printf("OK\n");
			if (pb_dst)
				free(pb_dst);
		}
		//several various numbers
		{
			int arr[] = { 3, 6, 4, 1, 2, 5 };
			int arr_dst[] = { 6, 4, 5 };
			pb_src = arr;
			pe_src = arr + 6;
			pb_dst = NULL;
			pe_dst = NULL;
			printf("#2: ");
			if (key(pb_src, pe_src, &pb_dst, &pe_dst) != OK)
				printf("FAILED\n");
			else if (arr_compare(pb_dst, pe_dst, arr_dst, arr_dst + 3) == 
						ARR_EQUAL)
				printf("OK\n");
			else
				printf("FAILED\n");
			if (pb_dst)
				free(pb_dst);
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
		printf("#0: ");
		if (compar_int(pa, pb) > 0)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//EQUAL
	{
		a = 5;
		b = 5;
		printf("#1: ");
		if (compar_int(pa, pb) == 0)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//FIRST LARGER
	{
		a = 1;
		b = 5;
		printf("#2: ");
		if (compar_int(pa, pb) < 0)
			printf("OK\n");
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
		printf("#0: ");
		shift((char *)pb, (char *)pe, sizeof(int));
		if (arr_compare(arr, arr + 1, arr_res, arr_res + 1) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//two elements
	{
		int arr[] = { 1, 3 };
		int arr_res[] = { 3, 1 };
		pb = arr;
		pe = pb + 2;
		printf("#1: ");
		shift((char *)pb, (char *)pe, sizeof(int));
		if (arr_compare(arr, arr + 2, arr_res, arr_res + 2) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//several elements
	{
		int arr[] = { 1, 5, 0, 3 };
		int arr_res[] = { 3, 1, 5, 0 };
		pb = arr;
		pe = pb + 4;
		printf("#2: ");
		shift((char *)pb, (char *)pe, sizeof(int));
		if (arr_compare(arr, arr + 4, arr_res, arr_res + 4) == ARR_EQUAL)
			printf("OK\n");
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
		printf("#0: ");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//all equal
	{
		int arr[] = { 1, 1, 1, 1, 1 };
		int arr_res[] = { 1, 1, 1, 1, 1 };
		pb = arr;
		n = 5;
		printf("#1: ");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//sorted already
	{
		int arr[] = { 1, 2, 3, 4, 5 };
		int arr_res[] = { 1, 2, 3, 4, 5 };
		pb = arr;
		n = 5;
		printf("#2: ");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//invert-sorted
	{
		int arr[] = { 5, 4, 3, 2, 1 };
		int arr_res[] = { 1, 2, 3, 4, 5 };
		pb = arr;
		n = 5;
		printf("#3: ");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//some elements are equal
	{
		int arr[] = { 1, 2, 3, 2, 0 };
		int arr_res[] = { 0, 1, 2, 2, 3 };
		pb = arr;
		n = 5;
		printf("#4: ");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//all various
	{
		int arr[] = { 1, 0, -8, 7, 5 };
		int arr_res[] = { -8, 0, 1, 5, 7 };
		pb = arr;
		n = 5;
		printf("#5: ");
		mysort(pb, n, sizeof(int), compar_int);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//float elemetnts
	{
		float arr[] = { 1.2, 0.1, -8.45, 7.8888, 5 };
		float arr_res[] = { -8.45, 0.1, 1.2, 5, 7.8888 };
		float *pbb = arr;
		n = 5;
		printf("#6: ");
		mysort(pbb, n, sizeof(float), compar_float);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
	//char elemetnts
	{
		char arr[] = { 'd', '!', 'c', 'a', 'A' };
		char arr_res[] = { '!', 'A', 'a', 'c', 'd' };
		char *pbb = arr;
		n = 5;
		printf("#7: ");
		mysort(pbb, n, sizeof(char), compar_char);
		if (arr_compare(arr, arr + n, arr_res, arr_res + n) == ARR_EQUAL)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
}

int main()
{
	test_read_array();
	test_key();
	test_compar_int();
	test_shift();
	test_mysort();
	return 0;
}