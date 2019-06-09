/*
Программа, сравнивающая точное и приближённое значения экспоненты
*/
#include <stdio.h>
#include <math.h>

//вычисление значения функции s(x)
double s_func(float x, float eps)
{
    float x_cur = 1; //текущий член последовательности
    int i = 1; //счётчик итераций
    float res = 1; //значение функции

    //последовательное вычисление слагаемого и добавление его в сумму
    do
    {
        x_cur *= x/i;
        res += x_cur;
        i++;
    }
    while(fabs(x_cur) > eps);

    return res;
}

int main(void)
{
    float x, eps; //входные данные
    double s, f; //значения функций
    double abs_diff, rel_diff; //абсолютная и относительная погрешности

    printf("Enter x and eps: ");
    int success = scanf("%f%f", &x, &eps); //ввод и проверка входных данных
    if (success < 2 || eps <= 0)
        printf("Incorrect input!");
    else
    {
        //вычисление значений функций
        s = s_func(x,eps);
        f = exp(x);

        //вычисление погрешностей
        abs_diff = fabs(f - s);
        rel_diff = fabs(abs_diff/f);

        printf("s(%f) = %.7lf\nf(%f) = %.7lf\n", x, s, x, f);
        printf("Absolute difference: %.7lf\n", abs_diff);
        printf("Relative difference: %.7lf\n", rel_diff);
    }

    return 0;
}
