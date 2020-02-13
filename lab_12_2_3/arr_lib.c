#include "arr_lib.h"

ARR_DLL int ARR_DECL is_prime(int x)
{
	if (x < 2)
		return 0;
	for (int k = 2; k <= x / 2; k++)
		if (x % k == 0)
			return 0;
	return 1;
}

ARR_DLL void ARR_DECL arr_fill_prime(int *arr, int n)
{
	if (!arr || n <= 0)
		return;
	int x = 2, i = 0;
	while(i < n)
	{
		while(!is_prime(x))
			x++;
		arr[i++] = x++;
	}
}

ARR_DLL void ARR_DECL arr_copy_spec(int *arr1, int *arr2,
	int n1, int *n2, int num)
{
	*n2 = 0;
	if (!arr1 || !arr2 || n1 <= 0)
		return;
	for (int i = 0; i < n1; i++)
	{
		arr2[*n2] = arr1[i];
		*n2 += 1;
		if (arr1[i] % 2 == 0)
		{
			arr2[*n2] = num;
			*n2 += 1;
		}
	}
}