/*
Программа, вычисляющая степень числа
*/
#include<stdio.h>

//функция, возводящая число a в степень n
long int power(int a, int n)
{
    long int res = 1;
    for(int i = 0; i < n; i++)
        res *= a;
    return res;
}

int main(void)
{

    //входные данные
    int a, n;
    int success; //количество верно введённых данных

    //выходные данные
    long int result;

    //процесс ввода
    printf("Enter base a and exponent n: ");
    success = scanf("%d%d", &a, &n);
    if (success < 2)
        printf("Incorrect input!");
    else
    {
        if (n < 0)
            printf("Incorrect input!");
        else
        {
            result = power(a,n);
            printf("Result: %ld", result);
        }
    }
    return 0;
}
