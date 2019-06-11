#include <stdio.h>
#include <math.h>

// подсчет функции s(x)
float func_s(float x, float eps)
{
    // ch - множители в числителе, zn - множители в знаменателе
    float s = 1, xi = 1;
    int ch = 1, zn = 2;

    while (fabs(xi) > eps)
    {
        xi *= x*x*ch/zn;
        s += xi;
        ch += 2;
        zn += 2;
    }
    return s;

}
int main()
{
    // diff_abs - абсолютная разница, diff_rel - относит разница
    float x, eps,res;
    double s, f, diff_abs, diff_rel;

    printf("Input x and eps: ");
    res = scanf("%f %f", &x, &eps);
    if (res == 2 && fabs(x) < 1 && eps > 0)
    {
        f = 1/sqrt(1-x*x);
        s = func_s(x,eps);
        diff_abs = fabs(f - s);
        diff_rel = fabs(diff_abs/f);
        printf("S(%.7f) = %.7lf\n", x, s);
        printf("F(%.7f) = %.7lf\n", x, f);
        printf("Absolute difference = %.7lf\n", diff_abs);
        printf("Relative difference = %.7lf\n", diff_rel);
    }
    else
        printf("Error!");

    return 0;
}
