#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gshow.h"
#include "gshow_f.h"
#include "list_u.h"
#include "filter.h"
#include "sort.h"
#include "error.h"

void errmsg(int rc)
{
	switch (rc)
	{
		case OK:
			break;
		case ERR_MEMORY:
			printf("Memory allocation error!\n");
			fprintf(stderr, "Memory allocation error!\n");
			break;
		case ERR_CMD:
			fprintf(stderr, "Not enough arguments!\n");
			break;
		case ERR_FILE:
			printf("File open error!\n");
			fprintf(stderr, "File open error!\n");
			break;
		case ERR_EMPTY:
			printf("File is empty!\n");
			fprintf(stderr, "File is empty!\n");
			break;
		case ERR_FORMAT:
			printf("List format error!\n");
			fprintf(stderr, "List format error!\n");
			break;
		case ERR_INPUT:
			printf("Invalid input!\n");
			fprintf(stderr, "Invalid input!\n");
			break;
		default:
			printf("Unknown error!\n");
			fprintf(stderr, "Unknown error!\n");
	}
}

int main(int argc, char **argv)
{
	// проверки файла на вход
	if (argc < 2)
	{
		errmsg(ERR_CMD);
		return ERR_CMD;
	}
	
	// объявление переменных
	int rc = OK;
	int act = 0;
	gshow_t *head = NULL;
	gshow_t sort_list;
    gshow_t filter_list;
	
	do
	{
		setbuf(stdout, NULL);
		// вывод меню
		printf("\n========== MENU =========\n"
			"1 - load list from file\n"
			"2 - print file to screen\n"
			"3 - save list to file\n\n"
			"4 - add new record\n"
			"5 - delete record by name\n"
			"6 - filter list\n"
			"7 - sort list\n"
			"8 - clear list\n\n"
			"other - exit\n"
			"=========================\n"
			"Enter action: ");
		
		// чтение команды
		rc = scanf("%d", &act);
		// выполнение команды меню
		if (act == 1)
		{
			free_list(&head);
			FILE *f = fopen(argv[1], "r");
			if (!f)
				errmsg(ERR_FILE);
			else
			{
				rc = read_list(&head, f);
				if (rc != OK)
				{
					errmsg(rc);
					act = 0;
					free_list(&head);
				}
				fclose(f);
			}
		}
		else if (act == 2)
			print_list(head);
		else if (act == 3)
		{
			FILE *f = NULL;
			// выбор файла на запись в зависимости от кол-ва аргументов
			// 2 - перезапись исходного
			// 3 - запись в новый
			if (argc < 3)
				f = fopen(argv[1], "w");
			else
				f = fopen(argv[2], "w");
			
			if (!f)
				errmsg(ERR_FILE);
			else
			{
				write_list(head, f);
				fclose(f);
			}
		}
		else if (act == 4)
		{
			rc = add_to_list(&head);
			if (rc != OK)
				errmsg(rc);
		}
		else if (act >= 5 && act <= 8 && !head)
			printf("\nList is empty!\n");
		else if (act == 5)
		{
			char *name = NULL;
			printf("Enter the name: ");
			ssize_t size = 0;
			while (act != '\n')
				act = getchar();
			rc = my_getline(&name, &size, stdin);
			if (!name || rc == -1)
				printf("Name input error!\n");
			else
			{
				strtok(name, "\n");
				pop(&head, name);
			}
			act = 5;
		}
		else if (act == 6)
		{
			printf("\n========= FILTER ========\n"
			"0 - by premier year\n"
			"1 - by genre\n"
			"other - cancel\n"
			"=========================\n"
			"Enter index: ");
			while (act != '\n')
				act = getchar();
			rc = scanf("%d", &act);
			if (act == 0)
			{
				int prem_y = 0;
				printf("Enter premier year (min): ");
				rc = scanf("%d", &prem_y);
				if (rc != 1 || prem_y < 0)
					printf("Year input error!\n");
				else
				{
					rc = init_filter(head, &filter_list, 0);
					if (rc)
						errmsg(rc);
					else
					{
						filter_prem(&filter_list, prem_y);
						print_filter(&filter_list, 0);
						clear_filter(&filter_list, 0);
					}
				}
			}
			else if (act == 1)
			{
				char *genre = NULL;
				printf("Enter the genre: ");
				ssize_t size = 0;
				while (act != '\n')
					act = getchar();
				rc = my_getline(&genre, &size, stdin);
				if (!genre || rc == -1)
					printf("Genre input error!\n");
				else
				{
					strtok(genre, "\n");
					rc = init_filter(head, &filter_list, 1);
					if (rc)
						errmsg(rc);
					else
					{
						filter_genre(&filter_list, genre);
						print_filter(&filter_list, 1);
						clear_filter(&filter_list, 1);
					}
				}
			}
			act = 6;
		}
		else if (act == 7)
		{
			printf("\n========== SORT =========\n"
			"0 - by name\n"
			"1 - by name & premier year\n"
			"2 - by name & genre\n"
			"other - cancel\n"
			"=========================\n"
			"Enter index: ");
			
			while (act == '\n')
				act = getchar();
			rc = scanf("%d", &act);
			if (act == 0)
			{
				rc = init_sort(head, &sort_list, 0);
				if (rc)
					errmsg(rc);
				else
				{
					sort_name(&sort_list);
					print_sort(&sort_list, 0);
					clear_sort(&sort_list, 0);
				}
			}
			else if (act == 1)
			{
				rc = init_sort(head, &sort_list, 1);
				if (rc)
					errmsg(rc);
				else
				{
					sort_name_prem(&sort_list);
					print_sort(&sort_list, 1);
				}
				clear_sort(&sort_list, 1);
			}
			else if (act == 2)
			{
				rc = init_sort(head, &sort_list, 2);
				if (rc)
					errmsg(rc);
				else
				{
					sort_name_genre(&sort_list);
					print_sort(&sort_list, 2);
				}
				clear_sort(&sort_list, 2);
			}
			act = 7;
		}
		else if (act == 8)
			free_list(&head);
		else
			act = 0; 
	}
	while (act > 0 && act < 9);
	
	free_list(&head);
	return rc;
}