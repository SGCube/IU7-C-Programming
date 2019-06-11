#include <stdio.h>
#include <math.h>

int main()
{
	int r1, r2, r3;
    float r;
	
    printf("Введите три сопротивления: ");
    scanf("%d%d%d", &r1, &r2, &r3);
	
    r = 1/(1/r1 + 1/r2 + 1/r3);

    printf("Общее сопротивление: %5.5f", r);
	
	return 0;
}