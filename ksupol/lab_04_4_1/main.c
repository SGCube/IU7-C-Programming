/*
метод сортировки: вставками
по возрастанию
*/
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

int sorting(int am, int arr[])
{
    int temp, k; 
    for (int i = 1; i < am; i++)
    {
        temp = arr[i]; 
        k = i-1; 
        while(k >= 0 && arr[k] > temp) 
        {
            arr[k + 1] = arr[k];
            arr[k] = temp;
            k--;
        }
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
		if (sorting(am,arr) == 0)
		PrintArray(am,arr);
	}	
	return 0;
}