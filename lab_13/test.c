#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

#include "gshow.h"
#include "gshow_f.h"
#include "list_u.h"
#include "filter.h"
#include "sort.h"
#include "error.h"

#include "test_sort.h"

void test_push_back()
{
	printf("push_back\n"
		"===============================\n");
	/// 1 - add to empty list
	{
		gshow_t *head = NULL;
		gshow_t *node = create_node("Game1", 1995, 1996, "Country1",
			"Genre1");
		if (!node)
		{
			printf("1 - empty\tMEMERR\n");
			free_list(&head);
			return;
		}
		
		head = push_back(head, node);
		if (!head || head != node)
			printf("1 - empty\tFAILED\n");
		else
			printf("1 - empty\tPASSED\n");
		free_list_test(&head);
	}
	setbuf(stdout, NULL);
	/// 2 - add to list with one record
	{
		gshow_t *head = create_node("Game1", 1995, 1996, "Country1",
			"Genre1");
		if (!head)
		{
			printf("2 - only head\tMEMERR\n");
			free_list(&head);
			return;
		}
		
		gshow_t *node = create_node("Game2", 1997, 1998, "Country2",
			"Genre2");
		if (!node)
		{
			printf("2 - only head\tMEMERR\n");
			free_list(&head);
			return;
		}
		
		head = push_back(head, node);
		if (!head || head->next != node)
			printf("2 - only head\tFAILED\n");
		else
			printf("2 - only head\tPASSED\n");
		free_list_test(&head);
	}
	setbuf(stdout, NULL);
	/// 3 - add to list with several records
	{
		gshow_t *head = create_node("Game1", 1995, 1996, "Country1",
			"Genre1");
		if (!head)
		{
			printf("3 - list\tMEMERR\n");
			free_list(&head);
			return;
		}
		
		gshow_t *last = create_node("Game2", 1997, 1998, "Country2",
			"Genre2");
		if (!last)
		{
			printf("3 - list\tMEMERR\n");
			free_list(&head);
			return;
		}
		head->next = last;
		
		gshow_t *node = create_node("Game3", 1999, 2000, "Country3",
			"Genre3");
		if (!node)
		{
			printf("3 - list\tMEMERR\n");
			free_list(&head);
			return;
		}
		
		head = push_back(head, node);
		if (!head || head->next != last || last->next != node)
			printf("3 - list\tFAILED\n");
		else
			printf("3 - list\tPASSED\n");
		free_list_test(&head);
	}
}

void test_pop(void)
{
	printf("\npop\n"
		"===============================\n");
	/// 1 - delete from empty list
	{
		gshow_t *head = NULL;
		pop_nofree(&head, "Name");
		if (head)
			printf("1 - empty\tFAILED\n");
		else
			printf("1 - empty\tPASSED\n");
		free_list_test(&head);
	}
	setbuf(stdout, NULL);
	/// 2 - delete head of list with only head
	{
		char *name = "Game";
		char *country = "Country";
		char *genre = "Genre";
		gshow_t *head = create_node(name, 1999, 2000, country,
			genre);
		pop_nofree(&head, "Game");
		if (head)
			printf("2 - only head\tFAILED\n");
		else
			printf("2 - only head\tPASSED\n");
		free_list_test(&head);
	}
	setbuf(stdout, NULL);
	/// 3 - delete head of list with several nodes
	{
		char *name = "Game";
		char *country = "Country";
		char *genre = "Genre";
		char *name2 = "Game2";
		char *country2 = "Country";
		char *genre2 = "Genre";
		gshow_t *head = create_node(name, 1999, 2000, country,
			genre);
		if (!head)
		{
			printf("3 - delete head\tMEMERR\n");
			free_list(&head);
			return;
		}
		head->next = create_node(name2, 1999, 2000, country2,
			genre2);
		if (!head->next)
		{
			printf("3 - delete head\tMEMERR\n");
			free_list(&head);
			return;
		}
		gshow_t *new_head = head->next;
		pop_nofree(&head, "Game");
		if (head != new_head)
			printf("3 - delete head\tFAILED\n");
		else
			printf("3 - delete head\tPASSED\n");
		free_list_test(&head);
	}
	setbuf(stdout, NULL);
	/// 4 - delete last
	{
		char *name = "Game";
		char *country = "Country";
		char *genre = "Genre";
		char *name2 = "Game2";
		char *country2 = "Country";
		char *genre2 = "Genre";
		char *name3 = "Game3";
		char *country3 = "Country";
		char *genre3 = "Genre";
		gshow_t *head = create_node(name, 1999, 2000, country,
			genre);
		if (!head)
		{
			printf("4 - delete head\tMEMERR\n");
			free_list(&head);
			return;
		}
		head->next = create_node(name2, 1999, 2000, country2,
			genre2);
		if (!head->next)
		{
			printf("4 - delete head\tMEMERR\n");
			free_list(&head);
			return;
		}
		head->next->next = create_node(name3, 1999, 2000, country3,
			genre3);
		if (!head->next->next)
		{
			printf("4 - delete head\tMEMERR\n");
			free_list(&head);
			return;
		};
		pop_nofree(&head, "Game3");
		if (!head || head->next->next)
			printf("4 - delete head\tFAILED\n");
		else
			printf("4 - delete head\tPASSED\n");
		free_list_test(&head);
	}
	setbuf(stdout, NULL);
	/// 5 - delete with several matches
	{
		char *name = "Game";
		char *country = "Country";
		char *genre = "Genre";
		char *name2 = "Game2";
		char *country2 = "Country3";
		char *genre2 = "Genre3";
		char *name3 = "Game2";
		char *country3 = "Country3";
		char *genre3 = "Genre3";
		gshow_t *head = create_node(name, 1999, 2000, country,
			genre);
		if (!head)
		{
			printf("5 - matches\tMEMERR\n");
			free_list(&head);
			return;
		}
		head->next = create_node(name2, 1999, 2000, country2,
			genre2);
		if (!head->next)
		{
			printf("5 - matches\tMEMERR\n");
			free_list(&head);
			return;
		}
		head->next->next = create_node(name3, 1999, 2000, country3,
			genre3);
		if (!head->next->next)
		{
			printf("5 - matches\tMEMERR\n");
			free_list(&head);
			return;
		};
		gshow_t *del_next = head->next->next;
		pop_nofree(&head, "Game2");
		if (!head || head->next != del_next)
			printf("5 - matches\tFAILED\n");
		else
			printf("5 - matches\tPASSED\n");
		free_list_test(&head);
	}
}

void test_swap()
{
	printf("\nswap\n"
		"===============================\n");
	{
		gshow_t *game1 = create_node("Game1", 1991, 1992, "Country1", "Genre1");
		gshow_t *game2 = create_node("Game1", 1991, 1992, "Country1", "Genre1");
		assert(game1 && game2);
		swap(game1, game2);
		if (strcmp("Game1", game1->name) != 0 || 
			strcmp("Country1", game1->country) != 0 || 
			strcmp("Genre1", game1->genre) != 0 || 
			game1->prem_y != 1991 || game1->end_y != 1992)
			printf("1 - same\tFAILED\n");
		else if (strcmp("Game1", game2->name) != 0 || 
			strcmp("Country1", game2->country) != 0 || 
			strcmp("Genre1", game2->genre) != 0 || 
			game2->prem_y != 1991 || game2->end_y != 1992)
			printf("1 - same\tFAILED\n");
		else
			printf("1 - same\tPASSED\n");
		free(game1);
		free(game2);
	}
	{
		gshow_t *game1 = create_node("Game1", 1991, 1992, "Country1", "Genre1");
		gshow_t *game2 = create_node("Game1", 1993, 1994, "Country1", "Genre2");
		assert(game1 && game2);
		swap(game1, game2);
		if (strcmp("Game1", game1->name) != 0 || 
			strcmp("Country1", game1->country) != 0 || 
			strcmp("Genre2", game1->genre) != 0 || 
			game1->prem_y != 1993 || game1->end_y != 1994)
			printf("2 - diff notes\tFAILED\n");
		else if (strcmp("Game1", game2->name) != 0 || 
			strcmp("Country1", game2->country) != 0 || 
			strcmp("Genre1", game2->genre) != 0 || 
			game2->prem_y != 1991 || game2->end_y != 1992)
			printf("2 - diff notes\tFAILED\n");
		else
			printf("2 - diff notes\tPASSED\n");
		free(game1);
		free(game2);
	}
	{
		gshow_t *game1 = create_node("Game1", 1991, 1992, "Country1", "Genre1");
		gshow_t *game2 = create_node("Game2", 1993, 1994, "Country2", "Genre2");
		assert(game1 && game2);
		swap(game1, game2);
		if (strcmp("Game2", game1->name) != 0 || 
			strcmp("Country2", game1->country) != 0 || 
			strcmp("Genre2", game1->genre) != 0 || 
			game1->prem_y != 1993 || game1->end_y != 1994)
			printf("3 - diff all\tFAILED\n");
		else if (strcmp("Game1", game2->name) != 0 || 
			strcmp("Country1", game2->country) != 0 || 
			strcmp("Genre1", game2->genre) != 0 || 
			game2->prem_y != 1991 || game2->end_y != 1992)
			printf("3 - diff all\tFAILED\n");
		else
			printf("3 - diff all\tPASSED\n");
		free(game1);
		free(game2);
	}
}

void test_filter_genre()
{
	printf("\nfilter_genre\n"
		"===============================\n");
	// LIST OF ONE NODE
	{
		gshow_t *head = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(head);
		
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 1) == OK);
			filter_genre(&filter_list, "Genre");
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *cur = head;
			short int check = 1;
			
			list_for_each(tmp, &(filter_list).filter[1])
			{
				node = list_entry(tmp, gshow_t, filter[1]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("1 - only head, check\t%s\n", check ? "PASSED" : "FAILED");
			
			clear_filter(&filter_list, 1);
		}
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 1) == OK);
			filter_genre(&filter_list, "Genre2");
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *cur = NULL;
			short int check = 1;
			
			list_for_each(tmp, &(filter_list).filter[1])
			{
				node = list_entry(tmp, gshow_t, filter[1]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("2 - only head, no\t%s\n", check ? "PASSED" : "FAILED");
			
			clear_filter(&filter_list, 1);
		}
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(head);
		head->next = create_node("Game2", 1990, 1995, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("Game3", 1990, 1995, "Country3", "Genre2");
		assert(head->next->next);
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 1) == OK);
			filter_genre(&filter_list, "Genre3");
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *cur = NULL;
			short int check = 1;
			
			list_for_each(tmp, &(filter_list).filter[1])
			{
				node = list_entry(tmp, gshow_t, filter[1]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("3 - empty filter_list\t%s\n", check ? "PASSED" : "FAILED");
			
			clear_filter(&filter_list, 1);
		}
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 1) == OK);
			filter_genre(&filter_list, "Genre");
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *curh = create_node("Game", 1990, 1995, "Country", "Genre");
			assert(curh);
			short int check = 1;
			gshow_t *cur = curh;
			list_for_each(tmp, &(filter_list).filter[1])
			{
				node = list_entry(tmp, gshow_t, filter[1]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("4 - one in filter\t%s\n", check ? "PASSED" : "FAILED");
			free_list_test(&curh);
			clear_filter(&filter_list, 1);
		}
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 1) == OK);
			filter_genre(&filter_list, "Genre2");
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *curh = create_node("Game3", 1990, 1995, "Country3", "Genre2");
			assert(curh);
			curh->next = create_node("Game2", 1990, 1995, "Country2", "Genre2");
			assert(curh->next);
			short int check = 1;
			gshow_t *cur = curh;
			list_for_each(tmp, &(filter_list).filter[1])
			{
				node = list_entry(tmp, gshow_t, filter[1]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("5 - more in filter\t%s\n", check ? "PASSED" : "FAILED");
			free_list_test(&curh);
			clear_filter(&filter_list, 1);
		}
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(head);
		head->next = create_node("Game2", 1990, 1995, "Country2", "Genre");
		assert(head->next);
		head->next->next = create_node("Game3", 1990, 1995, "Country3", "Genre");
		assert(head->next->next);
		
		gshow_t filter_list;
		assert(init_filter(head, &filter_list, 1) == OK);
		filter_genre(&filter_list, "Genre");
		
		gshow_t *node;
		struct list_head *tmp;
		
		gshow_t *curh = create_node("Game3", 1990, 1995, "Country3", "Genre");
		assert(curh);
		curh->next = create_node("Game2", 1990, 1995, "Country2", "Genre");
		assert(curh->next);
		curh->next->next = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(curh->next->next);
		gshow_t *cur = curh;
		
		
		short int check = 1;
		
		list_for_each(tmp, &(filter_list).filter[1])
		{
			node = list_entry(tmp, gshow_t, filter[1]);
			if (compare(cur, node) != 1)
				check = 0;
			if (cur)
				cur = cur->next;
		}
		
		printf("6 - all in filter\t%s\n", check ? "PASSED" : "FAILED");
		
		clear_filter(&filter_list, 1);
		free_list_test(&head);
		free_list_test(&curh);
	}
}

void test_filter_prem()
{
	printf("\nfilter_prem\n"
		"===============================\n");
	/// ONE NODE
	{
		gshow_t *head = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(head);
		
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 0) == OK);
			filter_prem(&filter_list, 1990);
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *cur = head;
			short int check = 1;
			
			list_for_each(tmp, &(filter_list).filter[0])
			{
				node = list_entry(tmp, gshow_t, filter[0]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("1 - only head, check\t%s\n", check ? "PASSED" : "FAILED");
			
			clear_filter(&filter_list, 0);
		}
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 0) == OK);
			filter_prem(&filter_list, 1992);
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *cur = NULL;
			short int check = 1;
			
			list_for_each(tmp, &(filter_list).filter[0])
			{
				node = list_entry(tmp, gshow_t, filter[0]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("2 - only head, no\t%s\n", check ? "PASSED" : "FAILED");
			
			clear_filter(&filter_list, 0);
		}
		free_list_test(&head);
	}
	/// SEVERAL NODES
	{
		gshow_t *head = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(head);
		head->next = create_node("Game2", 1992, 1996, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("Game3", 1995, 1997, "Country3", "Genre2");
		assert(head->next->next);
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 0) == OK);
			filter_prem(&filter_list, 1996);
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *cur = NULL;
			short int check = 1;
			
			list_for_each(tmp, &(filter_list).filter[0])
			{
				node = list_entry(tmp, gshow_t, filter[0]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("3 - empty filter_list\t%s\n", check ? "PASSED" : "FAILED");
			
			clear_filter(&filter_list, 0);
		}
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 0) == OK);
			filter_prem(&filter_list, 1994);
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *curh = create_node("Game3", 1995, 1997, "Country3", "Genre2");
			assert(curh);
			short int check = 1;
			gshow_t *cur = curh;
			list_for_each(tmp, &(filter_list).filter[0])
			{
				node = list_entry(tmp, gshow_t, filter[0]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("4 - one in filter\t%s\n", check ? "PASSED" : "FAILED");
			free_list_test(&curh);
			clear_filter(&filter_list, 0);
		}
		{
			gshow_t filter_list;
			assert(init_filter(head, &filter_list, 0) == OK);
			filter_prem(&filter_list, 1991);
			
			gshow_t *node;
			struct list_head *tmp;
			gshow_t *curh = create_node("Game3", 1995, 1997, "Country3", "Genre2");
			assert(curh);
			curh->next = create_node("Game2", 1992, 1996, "Country2", "Genre2");
			assert(curh->next);
			short int check = 1;
			gshow_t *cur = curh;
			list_for_each(tmp, &(filter_list).filter[0])
			{
				node = list_entry(tmp, gshow_t, filter[0]);
				if (compare(cur, node) != 1)
					check = 0;
				if (cur)
					cur = cur->next;
			}
			
			printf("5 - more in filter\t%s\n", check ? "PASSED" : "FAILED");
			free_list_test(&curh);
			clear_filter(&filter_list, 0);
		}
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(head);
		head->next = create_node("Game2", 1992, 1996, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("Game3", 1995, 1997, "Country3", "Genre2");
		assert(head->next->next);
		
		gshow_t filter_list;
		assert(init_filter(head, &filter_list, 0) == OK);
		filter_prem(&filter_list, 1990);
		
		gshow_t *node;
		struct list_head *tmp;
		
		gshow_t *curh = create_node("Game3", 1995, 1997, "Country3", "Genre2");
		assert(curh);
		curh->next = create_node("Game2", 1992, 1996, "Country2", "Genre2");
		assert(curh->next);
		curh->next->next = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(curh->next->next);
		gshow_t *cur = curh;
		
		
		short int check = 1;
		
		list_for_each(tmp, &(filter_list).filter[0])
		{
			node = list_entry(tmp, gshow_t, filter[0]);
			if (compare(cur, node) != 1)
				check = 0;
			if (cur)
				cur = cur->next;
		}
		
		printf("6 - all in filter\t%s\n", check ? "PASSED" : "FAILED");
		
		clear_filter(&filter_list, 0);
		free_list_test(&head);
		free_list_test(&curh);
	}
}

int main()
{
	setbuf(stdout, NULL);
	test_push_back();
	test_pop();
	test_swap();
	test_filter_genre();
	test_filter_prem();
	test_sort_name();
	test_sort_name_genre();
	test_sort_name_prem();
	return 0;
}