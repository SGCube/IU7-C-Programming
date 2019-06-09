/*
Программа, определяющая тип треугольника (характеристика углов)
по координатам
*/
#include <stdio.h>
#include <math.h>

#define EPS 1e-06

//вычисление скалярного произведения векторов по координатам
float skal_multiply(float x1, float y1, float x2, float y2)
{
	return x1*x2 + y1*y2;
}

int main(void)
{	
	float x1, y1, x2, y2, x3, y3; //координаты точек 1, 2 и 3
	float xa, ya, xb, yb, xc, yc; //координат векторов a, b и c
    //скалярные произведения между векторами a и b, b и c, c и a соответственно
    float sk_ab, sk_bc, sk_ca;

    printf("Enter 3 pairs of coordinates for 3 points: ");
    int success = scanf("%f%f%f%f%f%f", &x1, &y1, &x2, &y2, &x3, &y3);

    if (success < 6)
    {
        printf("Incorrect input!");
    }
    else
    {
        //Координаты векторов-сторон треугольника
        xa = x2 - x1;
		ya = y2 - y1;
		xb = x3 - x1;
		yb = y3 - y1;
		xc = x3 - x2;
		yc = y3 - y2;
		
        //Первые 2 условия - проверка на существование треугольника
        if (fabs(xa) < EPS && fabs(ya) < EPS &&
            fabs(xb) < EPS && fabs(yb) < EPS &&
            fabs(xc) < EPS && fabs(yc) < EPS)
			printf("Triangle doesn't exist (point)");
        else if (fabs(xa * yb - xb * ya) < EPS)
			printf("Triangle doesn't exist (line)");
		else
		{
            //Поиск скалярных произведений между векторами
            sk_ab = skal_multiply(xa, ya, xb, yb);
            sk_bc = skal_multiply(-xb, -yb, -xc, -yc);
            sk_ca = skal_multiply(-xa, -ya, xc, yc);

            // модуль < EPS <=> сравнение с 0
            if (fabs(sk_ab) < EPS || fabs(sk_bc) < EPS || fabs(sk_ca) < EPS)
				printf("Right triangle");
            else if (sk_ab < 0 || sk_bc < 0 || sk_ca < 0)
				printf("Obtuse triangle");
			else
				printf("Acute triangle");
		}
    }

    return 0;
}
