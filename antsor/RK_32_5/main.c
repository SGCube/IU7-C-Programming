#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "list.h"
#include "stud.h"

void errmsg(int rc)
{
	switch (rc)
	{
		case OK:
			break;
		case ERR_CMD:
			printf("Command line error!\n");
			break;
		case ERR_FILE:
			printf("File open error!\n");
			break;
		case ERR_EMPTY:
			printf("File is empty!\n");
			break;
		case ERR_NDATA:
			printf("Not enough data!\n");
			break;
		case ERR_MEMORY:
			printf("Memory allocation error!\n");
			break;
		case ERR_INPUT:
			printf("Invalid input!\n");
			break;
		case ERR_ARG:
			printf("Wrong func arguments!\n");
			break;
		default:
			printf("Unknown error!\n");
	}
}

int main(int argc, char **argv)
{
	/// Инициализация переменных
	
	FILE *fin = NULL, *fout = NULL;
	node_t *list1 = NULL, *list2 = NULL;
	int rc = OK;
	
	///************************************************************
	
	/// Проверка аргументов командной строки
	
	if (argc < 3)
	{
		errmsg(ERR_CMD);
		return ERR_CMD;
	}
	
	fin = fopen(argv[1], "r");
	if (!fin)
	{
		errmsg(ERR_FILE);
		return ERR_FILE;
	}
	
	fout = fopen(argv[2], "w");
	if (!fout)
	{
		errmsg(ERR_FILE);
		fclose(fin);
		return ERR_FILE;
	}
	
	///************************************************************
	
	/// Чтение и вывод исхоного списка
	
	rc = read_stud1(&list1, fin);
	fclose(fin);
	if (rc != OK)
	{
		free_list(&list1);
		errmsg(rc);
		return rc;
	}
	print_list(list1, stdout, print_stud1);
	
	///************************************************************
	
	/// Получение и вывод нового списка
	
	rc = stud1_to_stud2(list1, &list2);
	if (rc != OK)
	{
		free_list(&list1);
		free_list(&list2);
		errmsg(rc);
		return rc;
	}
	printf("\n");
	print_list(list2, stdout, print_stud2);
	print_list(list2, fout, print_stud2);
	fclose(fout);
	
	///************************************************************
	
	/// Освобождение памяти из-под списков
	
	free_list(&list1);
	free_list(&list2);
	return OK;
}