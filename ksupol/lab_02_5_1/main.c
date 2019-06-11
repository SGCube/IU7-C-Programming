#include<stdio.h>
#include <math.h>

// функция , которая печатает цифры
void num_print(int n)
{
    // kol - кол-во разрядов в числе
    int kol = 0, a = n, p;

    // функция, которая узнает, сколько разрядов в числе
    do
    {
        n /= 10;
        kol += 1;
    }
    while (n > 0);

    printf("Result: ");
    p = pow(10,kol-1);
    for(int i  = kol; i > 0; i--)
    {
        printf("%d", a/p);
        a %= p;
        p /= 10;
    }
}

int main(void)
{
    // n - вводимое число
    int res, n;

    printf("Input n: ");
    res = scanf("%d",&n);

    if(res == 1 && n > 0)
        num_print(n);
    else
        printf("Error!");

    return 0;
}
