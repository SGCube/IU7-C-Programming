#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "error.h"
#include "list.h"
#include "gshow_f.h"
#include "list_u.h"
#include "sort.h"

int init_sort(gshow_t *head, gshow_t *sort_list, int indx)
{
	if (!head)
        return ERR_EMPTY;
	
    INIT_LIST_HEAD(&(sort_list->sort[indx]));
	
	gshow_t *cur = head;
	while (cur)
	{
		gshow_t *node = create_node(cur->name, cur->prem_y, cur->end_y,
			cur->country, cur->genre);
		if (!node)
			return ERR_MEMORY;
		INIT_LIST_HEAD(&(node->sort[indx]));
		
		list_add(&(node->sort[indx]), &(sort_list->sort[indx]));

		cur = cur->next;
	}
	
    return OK;
}

void sort_name(gshow_t *sort_list)
{
    gshow_t *node, *cur, *min;
    struct list_head *tmp;
    struct list_head *tmp_min;
    int count = 0, check;
	
    list_for_each(tmp, &(sort_list->sort[0]))
    {
		node = list_entry(tmp, gshow_t, sort[0]);
        min = node;
        check = 0;
        list_for_each(tmp_min, &(sort_list->sort[0]))
        {
            cur = list_entry(tmp_min, gshow_t, sort[0]);
            if (strcmp(cur->name, min->name) < 0 && check > count)
                min = cur;
            check++;
        }
        count++;
        swap(node, min);
    }
}

void sort_name_prem(gshow_t *sort_list)
{
	gshow_t *node, *cur, *min;
    struct list_head *tmp;
    struct list_head *tmp_min;
    int count = 0, check;

    list_for_each(tmp, &(sort_list->sort[1]))
    {
        node = list_entry(tmp, gshow_t, sort[1]);
        min = node;
        check = 0;
        list_for_each(tmp_min, &(sort_list->sort[1]))
        {
            cur = list_entry(tmp_min, gshow_t, sort[1]);
            if (strcmp(min->name, cur->name) > 0 &&
				min->prem_y == cur->prem_y && check > count)
                min = cur;
            if (cur->prem_y < min->prem_y && check > count)
                min = cur;
            check++;
        }
        count++;
        swap(node, min);
    }
}

void sort_name_genre(gshow_t *sort_list)
{
	gshow_t *node, *cur, *min;
    struct list_head *tmp;
    struct list_head *tmp_min;
    int count = 0, check;

    list_for_each(tmp, &(sort_list->sort[2]))
    {
        node = list_entry(tmp, gshow_t, sort[2]);
        min = node;
        check = 0;
        list_for_each(tmp_min, &(sort_list->sort[2]))
        {
            cur = list_entry(tmp_min, gshow_t, sort[2]);
            if (strcmp(cur->name, min->name) < 0 &&
				strcmp(cur->genre, min->genre) == 0 && check > count)
                min = cur;
            if (strcmp(cur->genre, min->genre) < 0 && check > count)
                min = cur;
            check++;
        }
        count++;
        swap(node, min);
    }
}

void print_sort(gshow_t *sort_list, int indx)
{
    gshow_t *node;
    struct list_head *tmp;
	
	// шапка таблицы
	printf("\n%-30s %-4s %-4s %-10s %-15s\n", "Name of game show",
		"PREM", "END", "Country", "Genre");
	for (int k = 0; k < 70; k++)
		printf("=");
	printf("\n");
	
	list_for_each(tmp, &(*sort_list).sort[indx])
	{
		node = list_entry(tmp, gshow_t, sort[indx]);
		print_node(node);
	}
	printf("\n");
}

void clear_sort(gshow_t *sort_list, int indx)
{
    gshow_t *node;
    struct list_head *tmp;
    struct list_head *ptr;

	list_for_each_safe(ptr, tmp, &(*sort_list).sort[indx])
	{
		node = list_entry(ptr, gshow_t, sort[indx]);
		list_del(ptr);
		if (node)
			free(node);
	}
}

