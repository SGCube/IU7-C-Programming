/*
Программа, считающая количество локальных максимумов последовательности
чисел
*/

#include <stdio.h>

#define SUCCESS 0
#define NO_INPUT -1
#define INPUT_ERROR -2

//функция, считающая количество локальных максимумов
int process(FILE *f, int *max_k);

//основная функция
int main(int argc, char **argv)
{
	FILE *f;
	int max_kol = 0; //количество локальных максимумов
	
	setbuf(stdout, NULL);
	
	if (argc < 2)
	{
		//если нет на входе имени файла с входными данными,
		//то он создаётся
		f = fopen("in.txt","w");
		if (f)
		{
			printf("Input numbers: ");
			int x;	//входное число
			while(fscanf(stdin,"%d",&x) == 1)
			{
				fprintf(f,"%d ",x);
			};
			fclose(f);
			f = fopen("in.txt","r");
		}
		else
		{
			fprintf(stderr, "Can not create a file!");
			fclose(f);
			return NO_INPUT;
		}
	}
	else
	{
		f = fopen(argv[1],"r");
		if (f == NULL)
		{
			fprintf(stderr, "File doesn't exists!");
			fclose(f);
			return NO_INPUT;
		}
	}
	
	if (process(f, &max_kol) == SUCCESS)
		printf("Number of local maximums: %d", max_kol);
	else
	{
		fprintf(stderr, "Data read error!");
		fclose(f);
		return INPUT_ERROR;
	}
	fclose(f);
	return SUCCESS;
}

int process(FILE *f, int *max_k)
{
	int x_prev, x_cur, x_next; //предыдущий, текущий и следующий элементы
	*max_k = 0;
	if (fscanf(f, "%d", &x_prev) == 1)
	{
		if (fscanf(f, "%d", &x_cur) == 1)
		{
			while (fscanf(f, "%d", &x_next) == 1)
			{
				if (x_prev < x_cur && x_cur > x_next)
					*max_k += 1;
				x_prev = x_cur;
				x_cur = x_next;
			}
		}
		return SUCCESS;
	}
	return INPUT_ERROR;
}