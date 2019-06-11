#include <stdio.h>
#include <math.h>

int main()
{
	int sec;
    int h, m, s;
	
    printf("Введите время в секундах: ");
    scanf("%d", &sec);
	
    h = sec / 3600;
    if (h < 0){
        h = 0;
    }
    sec = sec - h*3600;
    m = sec / 60;
    if (m < 0){
        m = 0;
    }
    s = sec - m * 60;

    printf("%d часов %d минут %d секунд", h, m, s);

}
