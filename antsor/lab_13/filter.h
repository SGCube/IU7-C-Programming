#ifndef __FILTER__H__
#define __FILTER__H__

#include "gshow.h"

int init_filter(gshow_t *head, gshow_t *filter, int indx);

void filter_prem(gshow_t *filter, unsigned int prem_y);

void filter_genre(gshow_t *filter, char *genre);

void print_filter(gshow_t *filter, int indx);

void clear_filter(gshow_t *filter, int indx);

#endif