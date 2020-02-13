#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "error.h"
#include "list.h"
#include "gshow_f.h"
#include "list_u.h"
#include "filter.h"

int init_filter(gshow_t *head, gshow_t *filter_list, int indx)
{
	if (!head)
        return ERR_EMPTY;
	
    INIT_LIST_HEAD(&(filter_list->filter[indx]));
	
	gshow_t *cur = head;
	while (cur)
	{
		gshow_t *node = create_node(cur->name, cur->prem_y, cur->end_y,
			cur->country, cur->genre);
		if (!node)
			return ERR_MEMORY;
		INIT_LIST_HEAD(&(node->filter[indx]));
		
		list_add(&(node->filter[indx]), &(filter_list->filter[indx]));

		cur = cur->next;
	}
	
    return OK;
}

void filter_prem(gshow_t *filter_list, unsigned int prem_y)
{
	gshow_t *node;
    struct list_head *tmp;
    struct list_head *ptr;

    list_for_each_safe(ptr, tmp, &(filter_list->filter[0]))
    {
        node = list_entry(ptr, gshow_t, filter[0]);
        if (node->prem_y < prem_y)
        {
			list_del(ptr);
			if (node)
				free(node);
		}
    }
}

void filter_genre(gshow_t *filter_list, char *genre)
{
	gshow_t *node;
    struct list_head *tmp;
    struct list_head *ptr;

    list_for_each_safe(ptr, tmp, &(filter_list->filter[1]))
    {
        node = list_entry(ptr, gshow_t, filter[1]);
        if (strcmp(node->genre, genre) != 0)
        {
			list_del(ptr);
			if (node)
				free(node);
		}
    }
}

void print_filter(gshow_t *filter_list, int indx)
{
    gshow_t *node;
    struct list_head *tmp;
	
	// шапка таблицы
	printf("\n%-30s %-4s %-4s %-10s %-15s\n", "Name of game show",
		"PREM", "END", "Country", "Genre");
	for (int k = 0; k < 70; k++)
		printf("=");
	printf("\n");
	
	list_for_each(tmp, &(*filter_list).filter[indx])
	{
		node = list_entry(tmp, gshow_t, filter[indx]);
		print_node(node);
	}
	printf("\n");
}

void clear_filter(gshow_t *filter_list, int indx)
{
    gshow_t *node;
    struct list_head *tmp;
    struct list_head *ptr;

	list_for_each_safe(ptr, tmp, &(*filter_list).filter[indx])
	{
		node = list_entry(ptr, gshow_t, filter[indx]);
		list_del(ptr);
		if (node)
			free(node);
	}
}

