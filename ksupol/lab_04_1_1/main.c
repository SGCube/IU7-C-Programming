# include <stdio.h>

# define OK 1
# define ERR_AMOUNT 2
# define ERR_MASS 4
# define NO 3
# define TOO_MANY 5
# define TOO_SMALL 6
# define SIZE 10

int ReadArray(int *am, int arr[])
{
	int rc = OK;
	
	printf("Enter amount of elements in massiv: ");
	if (scanf("%d", am) == 1)
	{
		if (*am > 10)
			rc = TOO_MANY;
		else if (*am < 1)
			rc = TOO_SMALL;
		else
		{
			printf("Enter elements of massiv: ");
			for (int i = 0; i < *am; i++)
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
		rc = ERR_AMOUNT;
	
	return rc;
}

int process(int arr[], int *prod, int *am)
{
	int rc = OK;
	int kol = 0;
	
	for (int i = 0; i < *am; i++)
	{
		if(arr[i] % 2 != 0)
		{
			*prod *= arr[i];
			kol += 1;
		}
	}
	if (kol == 0)
		rc = NO;
	
	return rc;
}
int main()
{
	int arr[SIZE];
	int prod = 1, am, check;
	
	setbuf(stdout, NULL);
	check = ReadArray(&am, arr);
	if (check == ERR_AMOUNT || check == TOO_SMALL)
		printf("Incorrect amount!");
	else if (check == TOO_MANY)
		printf("Too many elements in massiv!");
	else if (check == ERR_MASS)
		printf("Incorrect elements!");
	else 
	{
		if (process(arr,&prod, &am) == NO)
			printf("No unpaired numbers!");
		else
			printf("The production of unpaired numbers is %d ", prod);
	}
		
		
	return 0;
}