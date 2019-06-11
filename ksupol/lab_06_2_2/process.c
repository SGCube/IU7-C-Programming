#include "process.h"

int process(const int *pa, const int *const pb)
{
	long long int res = 1; 
	long long int sum = 0;
	
	while (pa < pb && *(pa) >= 0)
	{
		res *= (*pa);
		sum += res;
		pa += 1;
	}
	if (*pa < 0)
		sum = *pa;
	return sum;
}