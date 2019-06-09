/*
Программа, считающая среднее арифметическое чисел, расположенных между
минимумом и максимумом
*/

#include <stdio.h>

#define NO_INPUT -3
#define FILE_ERROR -2
#define INCORRECT_INPUT -1
#define SUCCESS 0
#define NO_BETWEEN 1

//прототип функции поиска максимума и минимума
int min_max_search(FILE *, int *, int *);

int average(FILE *, int, int, double *);

//основная функция
int main(int argc, char **argv)
{
    FILE *fin, *fout;
	int i_min, i_max;
	double avg;
	
    if (argc < 2)
    {
        fprintf(stderr, "No input files!\n");
        return NO_INPUT;
    }

    fin = fopen(argv[1],"r");
	
	if (argc < 3)
	{
		printf("Results would be in out.txt!\n");
		fout = fopen("out.txt","w");	
		
	}
    else
        fout = fopen(argv[2],"w");
	
    if (fin == NULL || fout == NULL)
	{
        fprintf(stderr, "Open file error!\n");
		fclose(fout);
        return FILE_ERROR;
    }

	int func_res = min_max_search(fin,&i_min,&i_max);
    if (func_res == SUCCESS)
	{
		if (i_min > i_max)
		{
			int tmp = i_min;
			i_min = i_max;
			i_max = tmp;
		}
		rewind(fin);
		func_res = average(fin,i_min,i_max,&avg);
		if (func_res == SUCCESS)
			fprintf(fout, "%lf\n", avg);
		else
			fprintf(fout, "none");
	}
	else
		fprintf(fout, "Incorrect input!");

    fclose(fin);
    fclose(fout);

    return 0;
}

//функция поиска максимума и минимума
int min_max_search(FILE *fin, int *i_min, int *i_max)
{
    double x_min, x_max, x;
    int i = 0;

    if (fscanf(fin, "%lf", &x_max) == 1)
    {
        x_min = x_max;
        *i_min = 0;
		*i_max = 0;
        while(1)
        {
            fscanf(fin, "%lf", &x);
			if (feof(fin))
				break;
			i++;
            if (x < x_min)
            {
                x_min = x;
                *i_min = i;
            }
            else if (x > x_max)
            {
                x_max = x;
                *i_max = i;
            }
        }
        return SUCCESS;
    }
    return INCORRECT_INPUT;
}

//функция, считающая среднее арифметическое между числами
int average(FILE *fin, int i_a, int i_b, double *avg)
{
    double x;
    int i = 0;
    int kol = 0;
    double sum = 0;
	
	if (i_a == i_b || i_a + 1 == i_b)
		return NO_BETWEEN;
	
    //цикл суммирования элементов между максимумом и минимумом
    while(i < i_b)
    {
		fscanf(fin, "%lf", &x);
		if (feof(fin))
			break;
		if (i_a < i && i < i_b)
        {
            sum += x;
            kol++;
        }
		i++;
    }
	
	*avg = sum / kol;
	return SUCCESS;
}
