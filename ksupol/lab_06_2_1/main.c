#include <stdio.h>

#define OK 0
#define ERR_FILE -1
#define ERR_MASS -2
#define TOO_BIG -3
#define EMPTY -4
#define SIZE 100

int ReadArray(FILE *, int *const , int **);
void PrintArray(const int *const , const int *const);
int process(const int *, const int *const);

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