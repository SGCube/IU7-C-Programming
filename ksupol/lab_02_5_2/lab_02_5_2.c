#include <stdio.h>
#include <math.h>
#define EPS 1e-12

int coinside(float x1, float y1, float x2, float y2,
                float x3, float y3, float x4, float y4)
{
    int check_1 = x1 == x3 && y1 == y3 && x2 == x4 && y2 == y4;
    int check_2 = x1 == x4 && y1 == y4 && x2 == x3 && y2 == y3;
    return check_1 || check_2;
}
void lines(float x1, float y1, float x2, float y2,
           float x3, float y3, float x4, float y4)
{
    // векторные произведения
    double v1, v2, v3, v4;

    v1 = (x4-x3)*(y1-y3)-(y4-y3)*(x1-x3);
    v2 = (x4-x3)*(y2-y3)-(y4-y3)*(x2-x3);
    v3 = (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
    v4 = (x2-x1)*(y4-y1)-(y2-y1)*(x4-x1);

    // отрезки совпадают
    if (coinside(x1, y1, x2, y2, x3, y3, x4, y4))
        printf("Lines coinside!");
    // отрезки пересекаются
    else if (v1*v2 < -EPS || v3*v4 < -EPS ||
             (fabs(v1) < EPS || fabs(v2) < EPS) ||
             (fabs(v3) < EPS || fabs(v4) < EPS))
        printf("%s","Lines cross");
    else
        printf("%s","Lines do not cross");
}

int main()
{
    float x1, y1, x2, y2, x3, y3, x4, y4;
    float res1, res2;

    printf("Enter coordinates of the first line: ");
    res1 = scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    printf("Enter coordinates of the second line: ");
    res2 = scanf("%f %f %f %f", &x3, &y3, &x4, &y4);

    if (res1 + res2 == 8)
    {   // оба отрезка вырожденны в точки
        int is_point1 = (x1 == x2) && (y1 == y2);
        int is_point2 = (x3 == x4) && (y3 == y4);
        if (is_point1 == 1 && is_point2 == 1)
            printf("Both are points!");
        // один из отрезков вырожден в точку
        else if (is_point1 == 1 || is_point2 == 1)
            printf("One of lines is point!");
        else
            lines(x1, y1, x2, y2, x3, y3, x4, y4);
    }
    else
        printf("Error!");

    return 0;
}
