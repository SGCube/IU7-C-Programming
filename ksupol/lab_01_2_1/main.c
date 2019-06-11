#include <stdio.h>
#include <math.h>

int main()
{
    int x1, y1;
    int x2, y2;
    int x3, y3;
    float p;
	
	setbuf(stdout, NULL);
    printf("Введите координаты первой вершины: ");
    scanf("%d%d", &x1, &y1);

    printf("Введите координаты второй вершины: ");
    scanf("%d%d", &x2, &y2);

    printf("Введите координаты третьей вершины: ");
    scanf("%d%d", &x3, &y3);

    p = sqrt(pow((x2-x1),2)+pow((y2-y1),2)) + sqrt(pow((x3-x1),2)+pow((y3-y1),2)) + sqrt(pow((x3-x2),2)+pow((y3-y2),2));
	
    printf("Периметр треугольника: %10.3f", p);
	return 0;
}
