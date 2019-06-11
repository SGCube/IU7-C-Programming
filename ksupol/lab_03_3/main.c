/*
тип чисел: int
метод: пузырёк
направление сортировки: возрастание
*/
#include <stdio.h>
#include <stdlib.h>	
#include <time.h> 
#define OK 0
#define ERR_CMD 1
#define ERR_IO 2

void sorting(FILE *);
// функция получения числа из файла по позиции
int get_number_by_pos(FILE *f,int pos, int *num)
{
	int rc= OK;
	long int posit = ftell(f);
	fseek(f,sizeof(int)*pos,SEEK_SET);
	if (fread(num,sizeof(int),1,f) == 1)
		fseek(f,posit,SEEK_SET);
	else
		rc = ERR_IO;
	return rc;
}

int put_number_by_pos(FILE *f,int pos, int *num)
{
	int rc = OK;
	long int posit = ftell(f);
	fseek(f,sizeof(int)*pos,SEEK_SET);
	if (fwrite(num,sizeof(int),1,f) == 1)
		fseek(f,posit,SEEK_SET);
	else
		rc = ERR_IO;
	return rc;
}

// функция, которая выводит числа из бинарного файла на экран
int print_bin(FILE *f)
{
	rewind(f);
	int num;
	while (fread(&num, sizeof(int), 1, f) == 1)
		printf("%d ", num);
	if (feof(f))
	{
		printf("\n");
		return OK;
	}
	else
		return ERR_IO;
}
// функция, создающая бинарные файлы со случайными числами
void create_file(FILE *f)
{
	int n = rand() % 20 + 1;
	int num;
	for (int i = 0; i<n; i++)
	{
		num = rand() % 1001 - 500;
		fwrite(&num,sizeof(num),1,f);
	}
}

int main(int argc, char **argv)
{
	FILE *f = NULL;
	int rc = OK;
	srand(time(NULL));
	setbuf(stdout, NULL);
	
	if (argc != 2)
	{
		f = fopen("main.bin", "wb");
		create_file(f);
		printf("New file main.bin was created\n");
		fclose(f);
		f = fopen("main.bin", "rb+");
	}
	else
	{
		f = fopen(argv[1],"rb+");
		if (f == NULL)
		{
			rc = ERR_CMD;
			printf("No such file!");
			fclose(f);
			return rc;
		}
	}
	if (print_bin(f) == ERR_IO)
		printf("Input error!");
	else
	{
		sorting(f);
		print_bin(f);
	}
	fclose(f);
	
	return 0;
}

void sorting(FILE *f)
{
	int i, num_1, num_2, flag = 0;
	while (1)
	{
		i = 1;
		flag = 0;
		while (1)
		{
			if (get_number_by_pos(f, i, &num_2) != OK)
				break;
			get_number_by_pos(f,i-1,&num_1);
			if (num_1 > num_2)
			{
				put_number_by_pos(f,i-1,&num_2);
				put_number_by_pos(f,i,&num_1);
				flag = 1;
			}
			i++;
		}
		if (flag == 0)
			break;
	}
}