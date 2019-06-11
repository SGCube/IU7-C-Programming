# include <stdio.h>

# define OK 1
# define ERR_AMOUNT 2
# define ERR_MASS 4
# define NO 3
# define TOO_MANY 5
#define TOO_SMALL 6
# define SIZE 10

// функция, которая считывает элементы массива 
int ReadArray(int *am, int arr[])
{
	int rc = OK;
	
	printf("Enter amount of elements in massiv: ");
	if (scanf("%d", am) == 1) // если кол-во чисел - число
	{
		if (*am > 10) // если кол-во чисел в массиве больше 10
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

//функция, которая преобразует новый массив 
int CreateArray(int *am, int *ind, int arr[], int arr_new[])
{
	int kol = 0;
	
	for (int i = 0; i < *am; i++)
	{
		for (int j = 1; j <= (arr[i]/2); j++) // проверяем делится ли число ...
		{
			if (arr[i] % j == 0) // .. на все до половины исходного числа
				kol++;
				
		}
		if (kol == 1)
		{
			arr_new[*ind] = arr[i];
			*ind += 1;
		}
		kol = 0;
	}
	
	return 0;
}


int main()
{
	int ind = 0;
	int am;
	int arr[SIZE];
	int arr_new[SIZE];
	
	setbuf(stdout, NULL);
	int check = ReadArray(&am,arr);
	if (check == ERR_AMOUNT || check == TOO_SMALL)
		printf("Wrong amount of massiv!");
	else if (check == TOO_MANY)
		printf("The amount of massiv is too big!");
	else if (check == ERR_MASS)
		printf("Wrong element of massiv!");
	else
	{		
		if (CreateArray(&am, &ind, arr, arr_new) == 0) // выводим массив
		{
			printf("New massiv: ");
			for (int i = 0; i < ind; i++)
				printf("%d ",arr_new[i]);
		}
	}
	return 0;
}