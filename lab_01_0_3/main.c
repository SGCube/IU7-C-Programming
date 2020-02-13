#include <stdio.h>

int main()
{
	float h, t, m;
	float normal_weight, mass_index;
	
	setbuf(stdout, NULL);
    printf("Введите рост и длину окружности грудной клетки в см,\n");
	printf("а также вес в кг: ");
	scanf("%f%f%f", &h, &t, &m);
	
	normal_weight = h * t / 240;
	mass_index = m / (0.0001 * h * h);
	
	printf("Нормальный вес: %7.5f\nИндекс массы: %7.5f", normal_weight, mass_index);
	
	return 0;
}
