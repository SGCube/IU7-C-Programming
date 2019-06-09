/*
Программа, сортирующая целые числа в бинарном файле
Направление сортировки: возрастание
Тип чисел: int
Алгоритм сортировки: сортировка выбором

Допущение: при создании бинарного файла со случайными числами
сами случайные числа лежат в диапазоне от -200 до 200, а
количество чисел варьируется от 1 до 25.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERR_NO_FILE -1
#define ERR_IO -2

//прототип функции, создающая бинарный файл со случайными числами
void bin_create(FILE *f);

//прототип функции, создающая бинарный файл с числами из текстового файла
//(создана для тестирования)
void bin_create_t(FILE *f, FILE *f_txt);

//прототип функции, выводящая числа из файла
int numb_print(FILE *f);

//прототип функции получения числа из файла по позиции
int get_number_by_pos(FILE *f, int *numb, int pos);

//прототип функции записи числа в файл на указанную позицию
int put_number_by_pos(FILE *f, int *numb, int pos);

//прототип функции сортировки последовательности чисел в файле
int numbers_sort(FILE *f);

//основная функция
int main(int argc, char **argv)
{
	FILE *f;
	int rc = SUCCESS; //код ошибки
	
	srand(time(NULL));
	setbuf(stdout, NULL);
	
	if (argc == 1 || argc > 2)
	{
		f = fopen("numbers.bin","wb+");
		if (f)
		{
			printf("File numbers.bin was automatically created.\n");
			if (argc > 2)
			{
				FILE *f_t = fopen(argv[1],"r");
				bin_create_t(f,f_t);
				fclose(f_t);
				fclose(f);
				return 0;
			}
			else
				bin_create(f);
		}
		else
		{
			fprintf(stderr,"Can not create a file!\n");
			rc = ERR_NO_FILE;
		}
	}
	else
	{
		f = fopen(argv[1], "rb+");
		if (f == NULL)
		{
			fprintf(stderr,"Can not open a file!\n");
			rc = ERR_NO_FILE;
		}	
	}
	
	rc = numb_print(f);
	if (rc == SUCCESS)
	{
		rc = numbers_sort(f);
		if (rc == SUCCESS)
			rc = numb_print(f);
		else
			fprintf(stderr,"Input error!\n");
	}
	else
		fprintf(stderr,"Input error!\n");
	
	return rc;
}

//функция, создающая бинарный файл со случайными числами
void bin_create(FILE *f)
{	
	int kol_numb = rand() % 25 + 1;
	int x;

	for(int i = 0; i < kol_numb; i++)
	{
		x = rand() % 401 - 200;
		fwrite(&x,sizeof(int),1,f);
	}
	rewind(f);
}

//функция, создающая бинарный файл с числами из текстового файла
//(создана для тестирования)
void bin_create_t(FILE *f, FILE *f_txt)
{	
	int x;

	while(fscanf(f_txt,"%d",&x) == 1)
		fwrite(&x,sizeof(int),1,f);
	
	rewind(f);
}

//функция получения числа из файла по позиции
int get_number_by_pos(FILE *f, int *numb, int pos)
{
	long int pos_cur = ftell(f);
	fseek(f, sizeof(int)*pos, SEEK_SET);
	if (fread(numb,sizeof(int),1,f) == 1)
	{
		fseek(f, pos_cur, SEEK_SET);
		return SUCCESS;
	}
	else
		return ERR_IO;
}

//функция записи числа в файл на указанную позицию
int put_number_by_pos(FILE *f, int *numb, int pos)
{
	long int pos_cur = ftell(f);
	fseek(f,sizeof(int)*pos,SEEK_SET);
	if (fwrite(numb,sizeof(int),1,f) == 1)
	{
		fseek(f,pos_cur,SEEK_SET);
		return SUCCESS;
	}
	else
		return ERR_IO;
}

//функция, выводящая числа из файла
int numb_print(FILE *f)
{
	int x;
	long int pos_cur = ftell(f);
	rewind(f);
	//вывод
	while(fread(&x, sizeof(int), 1, f) == 1)
		printf("%d ",x);
	if (feof(f) && ftell(f) != pos_cur)
	{
		fseek(f, pos_cur, SEEK_SET);
		printf("\n");
		return SUCCESS;
	}
	return ERR_IO;
}

//функция сортировки последовательности чисел в файле
int numbers_sort(FILE *f)
{
	int x_min, tmp; //минимальное значение, временная переменная
	//начальная позиция, текущая позиция и позиция минимального
	int i_start, i_cur, i_min; 
	
	rewind(f);
	if(fread(&x_min, sizeof(int), 1, f) == 1)
	{
		i_start = i_min = 0;
		i_cur = 1;
		while(1)
		{
			if (get_number_by_pos(f,&x_min,i_start) != SUCCESS)
				break;
			while(1)
			{
				fread(&tmp, sizeof(int), 1, f);
				if (feof(f))
					break;
				if (tmp < x_min)
				{
					i_min = i_cur;
					x_min = tmp;
				}
				i_cur++;
			}
			get_number_by_pos(f,&tmp,i_start);
			put_number_by_pos(f,&x_min,i_start);
			put_number_by_pos(f,&tmp,i_min);
			i_min = i_cur = ++i_start;
			fseek(f, i_start*sizeof(int), SEEK_SET);
		}
		rewind(f);
		return SUCCESS;
	}
	return ERR_IO;
}