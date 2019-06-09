/*
Программа, определяющая, какая из двух введённых цифр расположена правее
в введённом числе

Допущение: не предусматриваются числа, большие максимального значения
диапазона значений типа long int
*/

#include <stdio.h>

#define INPUT_ERROR -2 
#define NO_DIGIT -1 
#define OK 0 
#define SAME_DIGIT 1

//функция поиска позиции цифры в числе с его конца
int search_digit(long int numb, int digit)
{
	int c, i = 0;
	while(numb > 0)
	{
		c = numb % 10;
		if (c == digit)
			return i;
		numb /= 10;
		i++;
	}
	return NO_DIGIT;
}

int main(void)
{
	long int number; 	//число
	int a, b;			//цифры
	int a_pos, b_pos;	//позиции цифр в числе
	
	setbuf(stdout,NULL);
	
	printf("Enter number and two digits: ");
	int success = scanf("%ld%d%d", &number, &a, &b);
	if (success != 3 || number <=0 || a < 0 || a > 9 || b < 0 || b > 9)
	{
		printf("Incorrect input!\n");
		return INPUT_ERROR;
	}
	
	if (a == b)
	{
		printf("Digits are same.\n");
		return SAME_DIGIT;
	}
	
	a_pos = search_digit(number, a);
	b_pos = search_digit(number, b);
	
	if (a_pos == NO_DIGIT && b_pos == NO_DIGIT)
		printf("There is no digits %d and %d in number.\n", a, b);
	else if (a_pos == NO_DIGIT)
		printf("There is no digit %d in number.\n", a);
	else if (b_pos == NO_DIGIT)
		printf("There is no digit %d in number.\n", b);
	else if (a_pos < b_pos)
		printf("Digit %d is righter than digit %d.\n", a, b);
	else
		printf("Digit %d is righter than digit %d.\n", b, a);
	
	return OK;
}