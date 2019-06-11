#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "array.h"
#include "array_io.h"

#define OK 0
#define ERR_ARG -1
#define NO_OUTPUT -2
#define ERR_MALLOC -3
#define EMPTY_FILE -4
#define WRONG_ELEMENT -5
#define ERR_PRINT -6
#define ERR_FILE -7
#define NOTHING_AFTER_F -8
#define DIFFERENT -9
#define ERR -10

int compare(int *pa1, int *pb1, int *pa2, int *pb2)
{
	assert(pa1 < pb1);
	assert(pa2 < pb2);
	if (pb1 - pa1 != pb2 - pa2)
		return DIFFERENT;
	for (int *pc1 = pa1, *pc2 = pa2; pc2 < pb2; pc1++, pc2++)
		if (*pc1 != *pc2)
			return DIFFERENT;
	return OK;
}

int compare_char(char *pa1, char *pb1, char *pa2, char *pb2)
{
	assert(pa1 < pb1);
	assert(pa2 < pb2);
	if (pb1 - pa1 != pb2 - pa2)
		return DIFFERENT;
	for (char *pc1 = pa1, *pc2 = pa2; pc2 < pb2; pc1++, pc2++)
		if (*pc1 != *pc2)
			return DIFFERENT;
	return OK;
}

int compare_float(float *pa1, float *pb1, float *pa2, float *pb2)
{
	assert(pa1 < pb1);
	assert(pa2 < pb2);
	if (pb1 - pa1 != pb2 - pa2)
		return DIFFERENT;
	for (float *pc1 = pa1, *pc2 = pa2; pc2 < pb2; pc1++, pc2++)
		if (*pc1 != *pc2)
			return DIFFERENT;
	return OK;
}


int test_readarr(FILE *f, int *pa, int *pb, int *beg, int *end, int code)
{
	int rc = 0;
	rc = readarr(f, &pa, &pb);
	if (rc != code)
		return ERR;
	if (rc == EMPTY_FILE || rc == WRONG_ELEMENT)
		return OK;
	rc = compare(pa, pb, beg, end);
	if (rc != OK)
		return ERR;
	return OK;
}

void testreadarr(void)
{
	int err_cnt = 0; 
	
	// корректные данные
	{
		FILE *f;
		{
			f = fopen("tests/in_5.txt", "r");
			assert(f);
			int *pa = NULL;
			int *pb = NULL;
			int a[] = { -8 };
			if (test_readarr(f, pa, pb, a, a + 1, OK) != OK)
				err_cnt++;
			fclose(f);
			free(pa);
		}
		{
			f = fopen("tests/in_6.txt", "r");
			assert(f);
			int *pa = NULL;
			int *pb = NULL;
			int a[] = { 0, 6, 7, 1, 4, -9, 17, 5 };
			if (test_readarr(f, pa, pb, a, a + 8, OK) != OK)
				err_cnt++;
			fclose(f);
			free(pa);
		}

	}
	
	// некорректные элементы массива
	
	{
		FILE *f;
		{
			f = fopen("tests/in_1.txt", "r");
			assert(f);
			int *pa = NULL;
			int *pb = NULL;
			int a[] = { 8, 3 };
			if (test_readarr(f, pa, pb, a, a + 2, EMPTY_FILE) != OK)
				err_cnt++;
			fclose(f);
		}
		{
			f = fopen("tests/in_2.txt", "r");
			assert(f);
			int *pa = NULL;
			int *pb = NULL;
			int a[] = { 8, 3 };
			if (test_readarr(f, pa, pb, a, a + 2, WRONG_ELEMENT) != OK)
				err_cnt++;
			fclose(f);
		}
		{
			f = fopen("tests/in_3.txt", "r");
			assert(f);
			int *pa = NULL;
			int *pb = NULL;
			int a[] = { 8, 3 };
			if (test_readarr(f, pa, pb, a, a + 2, WRONG_ELEMENT) != OK)
				err_cnt++;
			fclose(f);
		}
	}
	printf("\n\ntestreadarr %s", err_cnt ? "FAILED" : "OK");
}

void testcalc_amount()
{
	int err_cnt = 0;
	FILE *f;
	{
		f = fopen("tests/in_5.txt", "r");
		assert(f);
		int am = 0;
		int *pa = NULL;
		int *pb = NULL;
		readarr(f, &pa, &pb);
		am = calc_amount(pa, pb);
		if (am != NOTHING_AFTER_F)
			err_cnt++;
		fclose(f);
	}
	{
		f = fopen("tests/in_6.txt", "r");
		assert(f);
		int am = 0;
		int *pa = NULL;
		int *pb = NULL;
		readarr(f, &pa, &pb);
		am = calc_amount(pa, pb);
		if (am != 5)
			err_cnt++;
		fclose(f);
	}
	{
		f = fopen("tests/in_7.txt", "r");
		assert(f);
		int am = 0;
		int *pa = NULL;
		int *pb = NULL;
		readarr(f, &pa, &pb);
		am = calc_amount(pa, pb);
		if (am != 1)
			err_cnt++;
		fclose(f);
	}
	{
		f = fopen("tests/in_8.txt", "r");
		assert(f);
		int am = 0;
		int *pa = NULL;
		int *pb = NULL;
		readarr(f, &pa, &pb);
		am = calc_amount(pa, pb);
		if (am != 7)
			err_cnt++;
		fclose(f);
	}
	printf("\n\ntestcalc_amount %s", err_cnt ? "FAILED" : "OK");
}

void testkey(void)
{
	int err_cnt = 0;
	FILE *f;
	{
		f = fopen("tests/in_6.txt", "r");
		int a[1] = { -5 };
		int *pa = a, *pb = a + 1;
		int *pa1 = NULL, *pb1 = NULL;
		int am = 0;
		readarr(f, &pa1, &pb1);
		am = calc_amount(pa1, pb1);
		if (key(pa, pb, pa1, &pb1, am) != OK)
			err_cnt++;
		free(pa1);
		fclose(f);
	}
	{
		f = fopen("tests/in_7.txt", "r");
		int a[1] = { 4 };
		int *pa = a, *pb = a + 1;
		int *pa1 = NULL, *pb1 = NULL;
		int am = 0;
		readarr(f, &pa1, &pb1);
		am = calc_amount(pa1, pb1);
		if (key(pa, pb, pa1, &pb1, am) != OK ||
			compare(pa1, pb1, pa, pb) != OK)
			err_cnt++;
		free(pa1);
		fclose(f);
	}
	{
		f = fopen("tests/in_8.txt", "r");
		int a[] = { 7, 1, 0, 6, 1, 2, 6  };
		int *pa = a, *pb = a + 7;
		int *pa1 = NULL, *pb1 = NULL;
		int am = 0;
		readarr(f, &pa1, &pb1);
		am = calc_amount(pa1, pb1);
		if (key(pa, pb, pa1, &pb1, am) != OK ||
			compare(pa1, pb1, pa, pb) != OK)
			err_cnt++;
		free(pa1);
		fclose(f);
	}
	printf("\n\ntestkey %s", err_cnt ? "FAILED" : "OK");
}

void testmysort(void)
{
	int err_cnt = 0;
	{
		int a[1] = { 12 };
		int *pa1 = a, *pb1 = a + 1;
		int b[1] = { 12 };
		int *pa2 = b, *pb2 = b + 1;
		int *pa = a;
		mysort(pa, 1, sizeof(int), cmpint);
		if (compare(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	{
		int a[5] = { 1, 2, 5, 15, 28 };
		int *pa1 = a, *pb1 = a + 5;
		int b[5] = { 1, 2, 5, 15, 28 };
		int *pa2 = b, *pb2 = b + 5;
		int *pa = a;
		mysort(pa, 5, sizeof(int), cmpint);
		if (compare(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	{
		int a[5] = { 125, 45, 23, 14, 5 };
		int *pa1 = a, *pb1 = a + 5;
		int b[5] = { 5, 14, 23, 45, 125 };
		int *pa2 = b, *pb2 = b + 5;
		int *pa = a;
		mysort(pa, 5, sizeof(int), cmpint);
		if (compare(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	{
		int a[6] = { 5, -9, 14, -12, 0, 62 };
		int *pa1 = a, *pb1 = a + 6;
		int b[6] = { -12, -9, 0, 5, 14, 62 };
		int *pa2 = b, *pb2 = b + 6;
		int *pa = a;
		mysort(pa, 6, sizeof(int), cmpint);
		if (compare(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	{
		int a[5] = { 4, 4, 4, 4, 4 };
		int *pa1 = a, *pb1 = a + 5;
		int b[5] = { 4, 4, 4, 4, 4 };
		int *pa2 = b, *pb2 = b + 5;
		int *pa = a;
		mysort(pa, 5, sizeof(int), cmpint);
		if (compare(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	
	{
		float a[5] = { 5.6, 8.3, -2.3, -0.36, 1.85 };
		float *pa1 = a, *pb1 = a + 5;
		float b[5] = { -2.3, -0.36, 1.85, 5.6, 8.3 };
		float *pa2 = b, *pb2 = b + 5;
		float *pa = a;
		mysort(pa, 5, sizeof(float), cmpfloat);
		if (compare_float(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	
	{
		char a[5] = { 's', 'b', 'd', 'a', 'i' };
		char *pa1 = a, *pb1 = a + 5;
		char b[5] = { 'a', 'b', 'd', 'i', 's' };
		char *pa2 = b, *pb2 = b + 5;
		char *pa = a;
		mysort(pa, 5, sizeof(char), cmpchar);
		if (compare_char(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	printf("\n\ntestmysort %s", err_cnt ? "FAILED" : "OK");
}

void testcmpint(void)
{
	int err_cnt = 0;
	{
		int a = 5;
		int *pa = &a;
		int b = 10;
		int *pb = &b;
		if (cmpint(pa, pb) >= 0)
			err_cnt++;
	}
	{
		int a = 15;
		int *pa = &a;
		int b = 10;
		int *pb = &b;
		if (cmpint(pa, pb) < 0)
			err_cnt++;
	}
	{
		int a = 5;
		int *pa = &a;
		int b = 5;
		int *pb = &b;
		if (cmpint(pa, pb) != 0)
			err_cnt++;
	}
	printf("\n\ntestcmp %s", err_cnt ? "FAILED" : "OK");
}

void testmovarr(void)
{
	int err_cnt = 0;
	{
		int a[6] = { 1, 2, 3, 4, 5, 6 };
		int b[6] = { 6, 1, 2, 3, 4, 5 };
		int *pa2 = b, *pb2 = b + 6;
		char *pa = (char*) a;
		char *pb = (char*) a + 5 * sizeof(int);
		movarr(pa, pb, sizeof(int));
		int *pa1 = a, *pb1 = a + 6;
		if (compare(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	{
		int a[3] = { 1, 2, 3 };
		int b[3] = { 3, 1, 2 };
		int *pa2 = b, *pb2 = b + 3;
		char *pa = (char*) a;
		char *pb = (char*) a + 2 * sizeof(int);
		movarr(pa, pb, sizeof(int));
		int *pa1 = a, *pb1 = a + 3;
		if (compare(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	{
		int a[2] = { 1, 2 };
		int b[2] = { 2, 1 };
		int *pa2 = b, *pb2 = b + 2;
		char *pa = (char*) a;
		char *pb = (char*) a + 1 * sizeof(int);
		movarr(pa, pb, sizeof(int));
		int *pa1 = a, *pb1 = a + 2;
		if (compare(pa1, pb1, pa2, pb2) != OK)
			err_cnt++;
	}
	{
		float a[3] = { 1.2, 2.3, 3.4 };
		float b[3] = { 3.4, 1.2, 2.3 };
		char *pa = (char*) a;
		char *pb = (char*) a + 2 * sizeof(float);
		movarr(pa, pb, sizeof(float));
		if (a[0] != b[0] && a[1] != b[1] && a[2] != b[2])
			err_cnt++;
	}
	{
		float a[4] = { 'q', 'r', 's', 't' };
		float b[4] = { 't', 'q', 'r', 's' };
		char *pa = (char*) a;
		char *pb = (char*) a + 3 * sizeof(float);
		movarr(pa, pb, sizeof(float));
		if (a[0] != b[0] && a[1] != b[1] &&
			a[2] != b[2] && a[3] != b[3])
			err_cnt++;
	}
	printf("\n\ntestmovarr %s", err_cnt ? "FAILED" : "OK");
}

int main()
{
	testreadarr();
	testcalc_amount();
	testkey();
	testmysort();
	testcmpint();
	testmovarr();
	
	return 0;
}
