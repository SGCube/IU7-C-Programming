#include <stdio.h>
#include <math.h>

int main()
{
	float a, b, h, p;
	
	setbuf(stdout, NULL);
	printf("Введите основания и высоту трапеции: ");
	scanf("%f%f%f", &a, &b, &h);

	p = a + b;
	
	//Поиск длин боковых сторон
	p += 2 * sqrt(pow((abs(b-a))/2, 2) + pow(h, 2));
	
	printf("Периметр трапеции: %7.5f", p);
	return 0;
}
