#ifndef __TEST__SORT__H__
#define __TEST__SORT__H__

#include "gshow.h"

int compare(gshow_t *p1, gshow_t *p2);

int compare_sort_list(gshow_t *, gshow_t *, int);

void test_sort_name();

void test_sort_name_genre();

void test_sort_name_prem();

#endif