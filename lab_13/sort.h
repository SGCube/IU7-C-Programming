#ifndef __SORT__H__
#define __SORT__H__

#include "gshow.h"

int init_sort(gshow_t *head, gshow_t *sort, int indx);

void sort_name(gshow_t *sort);

void sort_name_prem(gshow_t *sort);

void sort_name_genre(gshow_t *sort);

void print_sort(gshow_t *sort, int indx);

void clear_sort(gshow_t *sort, int indx);

#endif