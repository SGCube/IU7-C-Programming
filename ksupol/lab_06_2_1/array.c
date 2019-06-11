#include <stdio.h>

#define OK 0
#define ERR_FILE -1
#define ERR_MASS -2
#define TOO_BIG -3
#define EMPTY -4
#define SIZE 100

int ReadArray(FILE *f, int *const pa, int **pb)
{
	int *num = pa;
	int check;
	while (num < *pb)
	{
		check = fscanf(f,"%d", num);
		if (check == EOF)
		{
			if (num == pa)
				return EMPTY;
			break;
		}
		else if (check != 1)
			return ERR_MASS;
		else
		{
			num += 1;
		}
	}
	if (num == *pb)
		return TOO_BIG;
	*pb = num;
	return OK;
}

void PrintArray(const int *const pa, const int *const pb)
{
	int const *num = pa;
	while (num < pb)
	{
		printf("%d ",*num);
		num++;
	}
}