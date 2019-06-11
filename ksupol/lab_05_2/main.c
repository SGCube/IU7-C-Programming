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

void PrintArray(const int *const pa, const int *const pb)
{
	int const *num = pa;
	while (num < pb)
	{
		printf("%d ",*num);
		num++;
	}
}

int main(int argc, char **argv)
{
	FILE *f;
	int arr[SIZE];
	int* const pa = arr;
	int *pb = arr+SIZE, rc = OK;
	if (argc < 2)
		printf("No file name!");
	else
	{
		f = fopen(argv[1],"r");
		if (f == NULL)
			printf("This file doesn't exist!");
		else
		{
			rc = ReadArray(f,pa,&pb);
			if (rc == EMPTY)
				printf("File is empty!");
			else if (rc == ERR_MASS)
				printf("Incorrect input!");
			else
			{
				if (rc == TOO_BIG)
					printf("Array contains more than 100 elements!\n");
				PrintArray(pa,pb);
				printf("\nResult %d ", process(pa,pb));
			}	
		}
	}
	return 0;
}