#include <stdlib.h>
#include "array.h"

ARR_DLL void ARR_DECL fibon(int *arr, int am)
{
	if (am == 0 || !arr)
		return;
	if (am == 1)
	{
		arr[0] = 0;
		return;
	}
	arr[0] = 0;
	arr[1] = 1;
	for (int i = 2; i < am; i++)
		arr[i] = arr[i - 1] + arr[i - 2];	
}

ARR_DLL void ARR_DECL first_entry(int *arr, int am, int *arr_2, int *am_2)
{
	int dub = 0;
	*am_2 = 0;
	if (am == 0 || !arr)
		return;
	if (am == 1)
	{
		arr_2[0] = arr[0];
		*am_2 += 1;
		return;
	}
	arr_2[0] = arr[0];
	*am_2 += 1;
	for (int i = 1; i < am; i++)
	{
		dub = 0;
		for (int j = 0; j < *am_2 && !dub; j++)
			if (arr[i] == arr_2[j])
				dub = 1;
		if (!dub)
		{
			arr_2[*am_2] = arr[i];
			*am_2 += 1;
		}
	}
}