#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define OK 0
#define ERR -1
#define EMPTY_FILE -2
#define ERR_MALLOC -3

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Not enough data!\n");
		return ERR;
	}
	FILE *f = fopen(argv[1], "r");
	if (!f)
	{
		printf("Couldn't open file!\n");
		return ERR;
	}
	int rc = 0;
	int action = -1;
	list *head = NULL;
	setbuf(stdout, NULL);
	while (action != 0)
	{
		fflush(stdin);
		printf("1 - create list\n2 - show list\n3 - group list\n\n");
		printf("Enter your choice: ");
		scanf("%d", &action);
		if (action == 0)
			break;
		else if (action == 1)
		{
			rc = read_from_file(f, &head);
			if (rc == EMPTY_FILE)
			{
				printf("File is empty!\n");
				free_list(head);
				return ERR;
			}
		}
		else if (action == 2)
			print_list(head);
		else if (action == 3)
			head = sort(head);
	}
	free_list(head);
	return 0;
}