#ifndef __TEST_LIST_H__
#define __TEST_LIST_H__

#include "job.h"
#include "list.h"

int listcmp(node_t *head1, node_t *head2);
int listcmp2(node_t *head1, node_t *head2);
int test_add_node(job *arr, int k1, int k2, int i);
int test_listlen(job *arr, int k);
int test_get_node(job *arr, int k, int i);
int test_pop_back(job *arr, int k1, int k2);
int test_insert(job *arr1, job *arr2, void *data, int k1, int k2, int i);
int test_dupl(job *arr1, job *arr2, int k1, int k2);
int test_split(job *arr, int k1, int k2, int k3);
int test_merge(job *arr, job *res, int k1, int k2, int k3);
int test_sort(job *arr1, job *arr2, int k);

#endif

