#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "macalc.h"

#define EPS 1e-12

#define OK 0
#define SINGULAR_M -22

void matrsum(double **ma1, double **ma2, double **ma, int n, int m)
{
	assert(ma1 && ma2 && ma);
	assert(n > 0 && m > 0);
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ma[i][j] = ma1[i][j] + ma2[i][j];
}

void matrmult(double **ma1, double **ma2, double **ma,
	int n1, int m1, int n2, int m2)
{
	assert(ma1 && ma2 && ma);
	assert(n1 > 0 && m1 > 0 && n2 > 0 && m2 > 0);
	assert(m1 == n2);
	
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m2; j++)
		{
			ma[i][j] = 0;
			for (int k = 0; k < m1; k++)
				ma[i][j] += ma1[i][k] * ma2[k][j];
		}
}

int matrrev(double **ma, double **mar, int n)
{
	assert(ma && mar);
	assert(n > 0);
	
	double koeff = ma[0][0];
	short int swapped = 0;
	
	for (int j = 0; j < n; j++)
	{
		koeff = ma[j][j];
		if (fabs(koeff) < EPS)
		{
			swapped = 0;
			for (int k = j + 1; k < n && !(swapped); k++)
				if (fabs(ma[k][j]) > EPS)
				{
					double *temp = ma[k];
					ma[k] = ma[j];
					ma[j] = temp;
					swapped = 1;
				}
			if (!swapped)
				return SINGULAR_M;
		}
		for (int k = 0; k < n; k++)
		{
			ma[j][k] /= koeff;
			mar[j][k] /= koeff;
		}
		for (int i = 0; i < n; i++)
		{
			if (i != j)
			{
				koeff = ma[i][j];
				if (koeff != 0)
				{
					for (int k = 0; k < n; k++)
					{
						ma[i][k] -= ma[j][k] * koeff;
						mar[i][k] -= mar[j][k] * koeff;
					}
				}
			}
		}
	}
	return OK;
}