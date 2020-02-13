#ifndef __GSHOW__H__
#define __GSHOW__H__

#include "list.h"

#define MAX_SORT_INDX 3
#define MAX_FILTER_INDX 2

typedef struct gameshow gshow_t;

struct gameshow
{
	char *name;
	int prem_y;
	int end_y;
	char *country;
	char *genre;
	
	struct list_head sort[MAX_SORT_INDX];
    struct list_head filter[MAX_FILTER_INDX];
	
	gshow_t *next;
};

#endif