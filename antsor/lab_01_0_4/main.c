#include <stdio.h>

#define BOTTLE_COST 45
#define BOTTLE_SELL 20

int main()
{
	int s;
	int kol = 0;
	
	setbuf(stdout, NULL);
	printf("Введите сумму денег в копейках: ");
	scanf("%d", &s);
	
	while (s >= BOTTLE_COST)
	{
		int k_buy = s / BOTTLE_COST;
		s -= k_buy * BOTTLE_COST;
		kol += k_buy;
		s += k_buy * BOTTLE_SELL;
	}
	
	printf("На эту сумму можно купить %d бутылок", kol);
	
	return 0;
}