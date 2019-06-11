#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "prod.h"

#define OK 0
#define ERR_CAL -1
#define ERR -2
#define ERR_MALLOC -3
#define MAX_LEN 128
#define EMPTY -4

int main(int argc, char **argv)
{
	FILE *fin, *fout;
	int rc = 0, sc = 0;
	node_t *head = NULL;
	prod_t *p;
	p = malloc(100 * sizeof(prod_t));
	if (!p)
	{
		printf("Memory allocation error!\n");
		return ERR;
	}
	
	if (argc < 4)
	{
		printf("Not enough data!\n");
		return ERR;
	}
	if (strcmp(argv[1], "p") != 0 && strcmp(argv[1], "i") != 0 &&
		strcmp(argv[1], "r") != 0 && strcmp(argv[1], "s") != 0)
	{
		printf("Wrong key!\n");
		return ERR;
	}
	fin = fopen(argv[2], "r");
	if (!fin)
	{
		printf("Couldn't open %s file!\n", argv[2]);
		return ERR;
	}
	rc = read_from_file(fin, &p);
	fclose(fin);
	if (rc == ERR_CAL)
	{
		printf("Error amount of calories!\n");
		return ERR;
	}
	if (rc == ERR_MALLOC)
	{
		printf("Memory allocation error!\n");
		return ERR;
	}
	fout = fopen(argv[3], "w");
	if (!fout)
	{
		printf("Couldn't open %s file!\n", argv[3]);
		return ERR;
	}
	sc = create_list(&head, rc, p);
	if (sc == EMPTY)
	{
		printf("List is empty!\n");
		return ERR;
	}
	if (sc == ERR_MALLOC)
	{
		printf("Memory allocation error!\n");
		return ERR;
	}
	if (strcmp(argv[1], "p") == 0)
	{
		fclose(fout);
		void *product = pop_front(&head);
		if (product == NULL)
		{
			printf("List is empty!\n");
			return ERR;
		}
		printf("\nFirst element of list is:\n");
		printf("%d %s", ((prod_t *)product)->cal,
		((prod_t *)product)->name);
	}
	if (strcmp(argv[1], "i") == 0)
	{
		int c = 0;
		char *n = NULL;
		int n_len = 0;
		int ac = 0;
		setbuf(stdout, NULL);
		printf("Enter amount of calories: ");
		sc = scanf("%d", &c);
		if (sc != 1 || c < 0 || c > 1000)
		{
			printf("Wrong amount of calories!\n");
			return ERR;
		}
		setbuf(stdin, NULL);
		printf("Enter name of product: ");
		my_getline(&n, &n_len, stdin);
		if (n[n_len - 2] == '\n')
			n[n_len - 2] = '\0';
		if (rc % 100 == 0)
		{
			void *u = realloc(p, (rc + 1) * sizeof(prod_t));
			if (!u)
			{
				printf("Memory allocation error!\n");
				return ERR_MALLOC;
			}
			p = (prod_t *)u;
		}
		rc++;
		p[rc].cal = c;
		p[rc].name = n;
		node_t *elem = create_elem((void *)&(p[rc]));
		printf("Enter number of element before which you want to insert element: ");
		sc = scanf("%d", &ac);
		if (sc != 1 || ac < 0)
		{
			printf("Error number of element!\n");
			return ERR;
		}
		node_t *before = head;
		int i = 0;
		while (before && i < ac)
		{
			before = before->next;
			i++;
		}
		if (!before)
		{
			printf("Error number of element!\n");
			return ERR;
		}
		insert(&head, elem, before);
		print_list(head);
	}
	if (strcmp(argv[1], "r") == 0)
	{
		head = reverse(head);
		print_list_file(head, fout);
	}
	if (strcmp(argv[1], "s") == 0)
	{
		head = sort(head, compar);
		print_list_file(head, fout);
	}
	for (int i = 0; i < rc; i++)
			free((void *)(p[i]).name);
	free(p);
	free_list(head);
	if (fout)
		fclose(fout);
	return 0;
}