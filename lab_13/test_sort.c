#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

#include "gshow.h"
#include "gshow_f.h"
#include "list_u.h"
#include "sort.h"
#include "error.h"

#include "test_sort.h"

int compare(gshow_t *p1, gshow_t *p2)
{
	if (!p1 && !p2)
		return 1;
	if (!p1 || !p2)
		return 0;
	if (strcmp(p1->name, p2->name) != 0)
		return 0;
	if (strcmp(p1->genre, p2->genre) != 0)
		return 0;
	if (strcmp(p1->country, p2->country) != 0)
		return 0;
	if (p1->prem_y != p2->prem_y)
		return 0;
	if (p1->end_y != p2->end_y)
		return 0;
	return 1;
}

int compare_sort_list(gshow_t *head, gshow_t *list, int indx)
{
	if (!head && !list)
		return 1;
	if (!head || !list)
		return 0;
	
	gshow_t *node;
	struct list_head *tmp;
	short int check = 1;
	gshow_t *cur = head;
	
	list_for_each(tmp, &(*list).sort[indx])
	{
		node = list_entry(tmp, gshow_t, sort[indx]);
		if (compare(cur, node) != 1)
			check = 0;
		if (cur)
			cur = cur->next;
	}
	return check;
}

void test_sort_name()
{
	printf("\nsort_name\n"
		"===============================\n");
	{
		gshow_t *head = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(head);
		
		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 0) == OK);
		sort_name(&sort_list);
		
		gshow_t *cur = head;
		
		printf("1 - only one\t%s\n",
			compare_sort_list(cur, &sort_list, 0) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 0);
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "Genre1");
		assert(head);
		head->next = create_node("B_Game", 1998, 2009, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("C_Game", 1999, 2001, "Country3", "Genre3");
		assert(head->next->next);
		
		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 0) == OK);
		sort_name(&sort_list);
			
		gshow_t *cur = head;
			
		printf("2 - sorted\t%s\n",
			compare_sort_list(cur, &sort_list, 0) ? "PASSED" : "FAILED");
			
		clear_sort(&sort_list, 0);
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("C_Game", 1990, 1995, "Country1", "Genre1");
		assert(head);
		head->next = create_node("B_Game", 1998, 2009, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("A_Game", 1999, 2001, "Country3", "Genre3");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 0) == OK);
		sort_name(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1999, 2001, "Country3", "Genre3");
		assert(curh);
		curh->next = create_node("B_Game", 1998, 2009, "Country2", "Genre2");
		assert(curh->next);
		curh->next->next = create_node("C_Game", 1990, 1995, "Country1", "Genre1");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("3 - inverted\t%s\n",
			compare_sort_list(cur, &sort_list, 0) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 0);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "Genre1");
		assert(head);
		head->next = create_node("A_Game", 1998, 2009, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("A_Game", 1999, 2001, "Country3", "Genre3");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 0) == OK);
		sort_name(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1999, 2001, "Country3", "Genre3");
		assert(curh);
		curh->next = create_node("A_Game", 1998, 2009, "Country2", "Genre2");
		assert(curh->next);
		curh->next->next = create_node("A_Game", 1990, 1995, "Country1", "Genre1");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("4 - all same\t%s\n",
			compare_sort_list(cur, &sort_list, 0) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 0);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "Genre1");
		assert(head);
		head->next = create_node("B_Game", 1998, 2009, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("A_Game", 1999, 2001, "Country3", "Genre3");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 0) == OK);
		sort_name(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1999, 2001, "Country3", "Genre3");
		assert(curh);
		curh->next = create_node("A_Game", 1990, 1995, "Country1", "Genre1");
		assert(curh->next);
		curh->next->next = create_node("B_Game", 1998, 2009, "Country2", "Genre2");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("5 - matches\t%s\n",
			compare_sort_list(cur, &sort_list, 0) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 0);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("B_Game", 1990, 1995, "Country1", "Genre1");
		assert(head);
		head->next = create_node("A_Game", 1998, 2009, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("C_Game", 1999, 2001, "Country3", "Genre3");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 0) == OK);
		sort_name(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1998, 2009, "Country2", "Genre2");
		assert(curh);
		curh->next = create_node("B_Game", 1990, 1995, "Country1", "Genre1");
		assert(curh->next);
		curh->next->next = create_node("C_Game", 1999, 2001, "Country3", "Genre3");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("6 - random\t%s\n",
			compare_sort_list(cur, &sort_list, 0) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 0);
		free_list_test(&head);
		free_list_test(&curh);
	}
}

void test_sort_name_genre()
{
	printf("\nsort_name_genre\n"
		"===============================\n");
	{
		gshow_t *head = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(head);
		
		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 2) == OK);
		sort_name_genre(&sort_list);
		
		gshow_t *cur = head;
		
		printf("1 - only one\t\t\t%s\n",
			compare_sort_list(cur, &sort_list, 2) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 2);
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "Genre");
		assert(head);
		head->next = create_node("B_Game", 1998, 2009, "Country2", "Genre");
		assert(head->next);
		head->next->next = create_node("C_Game", 1999, 2001, "Country3", "Genre");
		assert(head->next->next);
		
		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 2) == OK);
		sort_name_genre(&sort_list);
			
		gshow_t *cur = head;
			
		printf("2 - sorted, same genre\t\t%s\n",
			compare_sort_list(cur, &sort_list, 2) ? "PASSED" : "FAILED");
			
		clear_sort(&sort_list, 2);
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "GenreA");
		assert(head);
		head->next = create_node("A_Game", 1998, 2009, "Country2", "GenreB");
		assert(head->next);
		head->next->next = create_node("A_Game", 1999, 2001, "Country3", "GenreC");
		assert(head->next->next);
		
		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 2) == OK);
		sort_name_genre(&sort_list);
			
		gshow_t *cur = head;
			
		printf("3 - sorted, same name\t\t%s\n",
			compare_sort_list(cur, &sort_list, 2) ? "PASSED" : "FAILED");
			
		clear_sort(&sort_list, 2);
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("C_Game", 1990, 1995, "Country1", "Genre");
		assert(head);
		head->next = create_node("B_Game", 1998, 2009, "Country2", "Genre");
		assert(head->next);
		head->next->next = create_node("A_Game", 1999, 2001, "Country3", "Genre");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 2) == OK);
		sort_name_genre(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1999, 2001, "Country3", "Genre");
		assert(curh);
		curh->next = create_node("B_Game", 1998, 2009, "Country2", "Genre");
		assert(curh->next);
		curh->next->next = create_node("C_Game", 1990, 1995, "Country1", "Genre");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("4 - inverted, same genre\t%s\n",
			compare_sort_list(cur, &sort_list, 2) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 2);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "GenreC");
		assert(head);
		head->next = create_node("A_Game", 1998, 2009, "Country2", "GenreB");
		assert(head->next);
		head->next->next = create_node("A_Game", 1999, 2001, "Country3", "GenreA");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 2) == OK);
		sort_name_genre(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1999, 2001, "Country3", "GenreA");
		assert(curh);
		curh->next = create_node("A_Game", 1998, 2009, "Country2", "GenreB");
		assert(curh->next);
		curh->next->next = create_node("A_Game", 1990, 1995, "Country1", "GenreC");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("5 - inverted, same name\t\t%s\n",
			compare_sort_list(cur, &sort_list, 2) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 2);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "Genre");
		assert(head);
		head->next = create_node("A_Game", 1998, 2009, "Country2", "Genre");
		assert(head->next);
		head->next->next = create_node("A_Game", 1999, 2001, "Country3", "Genre");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 2) == OK);
		sort_name_genre(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1999, 2001, "Country3", "Genre");
		assert(curh);
		curh->next = create_node("A_Game", 1998, 2009, "Country2", "Genre");
		assert(curh->next);
		curh->next->next = create_node("A_Game", 1990, 1995, "Country1", "Genre");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("6 - all same\t\t\t%s\n",
			compare_sort_list(cur, &sort_list, 2) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 2);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "Genre2");
		assert(head);
		head->next = create_node("B_Game", 1998, 2009, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("A_Game", 1999, 2001, "Country3", "Genre1");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 2) == OK);
		sort_name_genre(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1999, 2001, "Country3", "Genre1");
		assert(curh);
		curh->next = create_node("A_Game", 1990, 1995, "Country1", "Genre2");
		assert(curh->next);
		curh->next->next = create_node("B_Game", 1998, 2009, "Country2", "Genre2");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("7 - matches name & genre\t%s\n",
			compare_sort_list(cur, &sort_list, 2) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 2);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "Genre2");
		assert(head);
		head->next = create_node("C_Game", 1998, 2009, "Country2", "Genre1");
		assert(head->next);
		head->next->next = create_node("B_Game", 1999, 2001, "Country3", "Genre3");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 2) == OK);
		sort_name_genre(&sort_list);
		
		gshow_t *curh = create_node("C_Game", 1998, 2009, "Country2", "Genre1");
		assert(curh);
		curh->next = create_node("A_Game", 1990, 1995, "Country1", "Genre2");
		assert(curh->next);
		curh->next->next = create_node("B_Game", 1999, 2001, "Country3", "Genre3");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("8 - all diff\t\t\t%s\n",
			compare_sort_list(cur, &sort_list, 2) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 2);
		free_list_test(&head);
		free_list_test(&curh);
	}
}

void test_sort_name_prem()
{
	printf("\nsort_name_prem\n"
		"===============================\n");
	{
		gshow_t *head = create_node("Game", 1990, 1995, "Country", "Genre");
		assert(head);
		
		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 1) == OK);
		sort_name_prem(&sort_list);
		
		gshow_t *cur = head;
		
		printf("1 - only one\t\t\t%s\n",
			compare_sort_list(cur, &sort_list, 1) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 1);
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "Genre");
		assert(head);
		head->next = create_node("B_Game", 1990, 2009, "Country2", "Genre");
		assert(head->next);
		head->next->next = create_node("C_Game", 1990, 2001, "Country3", "Genre");
		assert(head->next->next);
		
		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 1) == OK);
		sort_name_prem(&sort_list);
			
		gshow_t *cur = head;
			
		printf("2 - sorted, same prem year\t%s\n",
			compare_sort_list(cur, &sort_list, 1) ? "PASSED" : "FAILED");
			
		clear_sort(&sort_list, 1);
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "GenreA");
		assert(head);
		head->next = create_node("A_Game", 1998, 2009, "Country2", "GenreB");
		assert(head->next);
		head->next->next = create_node("A_Game", 1999, 2001, "Country3", "GenreC");
		assert(head->next->next);
		
		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 1) == OK);
		sort_name_prem(&sort_list);
			
		gshow_t *cur = head;
			
		printf("3 - sorted, same name\t\t%s\n",
			compare_sort_list(cur, &sort_list, 1) ? "PASSED" : "FAILED");
			
		clear_sort(&sort_list, 1);
		free_list_test(&head);
	}
	{
		gshow_t *head = create_node("C_Game", 1990, 1995, "Country1", "Genre");
		assert(head);
		head->next = create_node("B_Game", 1990, 2009, "Country2", "Genre");
		assert(head->next);
		head->next->next = create_node("A_Game", 1990, 2001, "Country3", "Genre");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 1) == OK);
		sort_name_prem(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1990, 2001, "Country3", "Genre");
		assert(curh);
		curh->next = create_node("B_Game", 1990, 2009, "Country2", "Genre");
		assert(curh->next);
		curh->next->next = create_node("C_Game", 1990, 1995, "Country1", "Genre");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("4 - inverted, same prem year\t%s\n",
			compare_sort_list(cur, &sort_list, 1) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 1);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1999, 2000, "Country1", "GenreC");
		assert(head);
		head->next = create_node("A_Game", 1998, 2009, "Country2", "GenreB");
		assert(head->next);
		head->next->next = create_node("A_Game", 1990, 2001, "Country3", "GenreA");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 1) == OK);
		sort_name_prem(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1990, 2001, "Country3", "GenreA");
		assert(curh);
		curh->next = create_node("A_Game", 1998, 2009, "Country2", "GenreB");
		assert(curh->next);
		curh->next->next = create_node("A_Game", 1999, 2000, "Country1", "GenreC");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("5 - inverted, same name\t\t%s\n",
			compare_sort_list(cur, &sort_list, 1) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 1);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1990, 1995, "Country1", "Genre");
		assert(head);
		head->next = create_node("A_Game", 1990, 2009, "Country2", "Genre");
		assert(head->next);
		head->next->next = create_node("A_Game", 1990, 2001, "Country3", "Genre");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 1) == OK);
		sort_name_prem(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1990, 2001, "Country3", "Genre");
		assert(curh);
		curh->next = create_node("A_Game", 1990, 2009, "Country2", "Genre");
		assert(curh->next);
		curh->next->next = create_node("A_Game", 1990, 1995, "Country1", "Genre");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("6 - all same\t\t\t%s\n",
			compare_sort_list(cur, &sort_list, 1) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 1);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1998, 2000, "Country1", "Genre2");
		assert(head);
		head->next = create_node("B_Game", 1998, 2009, "Country2", "Genre2");
		assert(head->next);
		head->next->next = create_node("A_Game", 1990, 2001, "Country3", "Genre1");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 1) == OK);
		sort_name_prem(&sort_list);
		
		gshow_t *curh = create_node("A_Game", 1990, 2001, "Country3", "Genre1");
		assert(curh);
		curh->next = create_node("A_Game", 1998, 2000, "Country1", "Genre2");
		assert(curh->next);
		curh->next->next = create_node("B_Game", 1998, 2009, "Country2", "Genre2");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("7 - matches name & prem year\t%s\n",
			compare_sort_list(cur, &sort_list, 1) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 1);
		free_list_test(&head);
		free_list_test(&curh);
	}
	{
		gshow_t *head = create_node("A_Game", 1995, 1995, "Country1", "Genre2");
		assert(head);
		head->next = create_node("C_Game", 1990, 2009, "Country2", "Genre1");
		assert(head->next);
		head->next->next = create_node("B_Game", 1999, 2001, "Country3", "Genre3");
		assert(head->next->next);

		gshow_t sort_list;
		assert(init_sort(head, &sort_list, 1) == OK);
		sort_name_prem(&sort_list);
		
		gshow_t *curh = create_node("C_Game", 1990, 2009, "Country2", "Genre1");
		assert(curh);
		curh->next = create_node("A_Game", 1995, 1995, "Country1", "Genre2");
		assert(curh->next);
		curh->next->next = create_node("B_Game", 1999, 2001, "Country3", "Genre3");
		assert(curh->next->next);
		
		gshow_t *cur = curh;
		
		printf("8 - all diff\t\t\t%s\n",
			compare_sort_list(cur, &sort_list, 1) ? "PASSED" : "FAILED");
		
		clear_sort(&sort_list, 1);
		free_list_test(&head);
		free_list_test(&curh);
	}
}