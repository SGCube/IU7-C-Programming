# include <stdio.h>

# define OK 1
# define ERR_AM 2
# define ERR_MASS 4
# define TOO_MANY 5
# define TOO_SMALL 6
# define SIZE 20

void PrintArray(int am, int arr[])
{
	printf("New massiv: ");
	for (int i = 0; i < am; i++)
		printf("%d ", arr[i]);
}
int fib(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return fib(n - 2) + fib(n - 1);
}

int ReadArray(int *am, int arr[])
{
	int rc = OK;
	
	printf("Enter amount of massiv (not more than 10): ");
	if (scanf("%d", am) == 1)
	{
		if (*am > 10)
			rc = TOO_MANY;
		else if (*am < 1)
			rc = ERR_AM;
		else
		{
			printf("Enter massiv: ");
			for (int i; i < *am; i++)
			{
				if (scanf("%d", &arr[i]) != 1)
				{
						rc = ERR_MASS;
						break;
				}
			}
		}
	}
	else 
		rc = ERR_AM;
	
	return rc;
}

int process(int *am, int arr[])
{
	int i = 0, n = 0;
	while (i < *am)
	{
		if (arr[i]%3 == 0)
		{
			*am += 1;
			for (int j = *am; j >= i + 1; j--)
				arr[j] = arr[j-1];
			arr[i+1] = fib(n);
			i+=1;
			n++;
		}
		i+=1;
	}
			
	return 0;
}

int main()
{
	int am;
	int arr[SIZE];
	
	setbuf(stdout, NULL);
	int check = ReadArray(&am, arr);
	if (check == TOO_MANY)
		printf("Too many elements of massiv!");
	else if (check == ERR_AM)
		printf("Error amount of massiv!");
	else if (check == ERR_MASS)
		printf("Array elements input error!");
	else
	{
		if (process(&am,arr) == 0)
			PrintArray(am,arr);
	}	
	return 0;
}