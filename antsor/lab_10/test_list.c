#include <stdlib.h>
#include "test_list.h"
#include "error.h"

int listcmp(node_t *head1, node_t *head2)
{
	node_t *p1 = head1, *p2 = head2;
	while (p1 && p2)
	{
		if (p1->data != p2->data)
			return 1;
		p1 = p1->next;
		p2 = p2->next;
	}
	if (p1 || p2)
		return 1;
	return 0;
}

int listcmp2(node_t *head1, node_t *head2)
{
	node_t *p1 = head1, *p2 = head2;
	while (p1 && p2)
	{
		if (!(p1->data) || !(p2->data))
			return 1;
		if (jobcmp(p1->data, p2->data) == 1)
			return 1;
		p1 = p1->next;
		p2 = p2->next;
	}
	if (p1 || p2)
		return 1;
	return 0;
}

int test_add_node(job *arr, int k1, int k2, int i)
{
	if (!arr)
		return ERR_LIST;
	int rc = 0;
	node_t *head = NULL, *headc = NULL;
	
	rc = create_joblist(&head, arr, k1);
	if (rc != OK)
	{
		delete_all(&head);
		return ERR_LIST;
	}
	
	rc = create_joblist(&headc, arr, k2);
	if (rc != OK)
	{
		delete_all(&head);
		delete_all(&headc);
		return ERR_LIST;
	}
	
	node_t *node = NULL;
	if (i >= 0 && i < k2)
		rc = create_node(&node, (void *)(arr + i));
	if (rc != OK)
	{
		delete_all(&head);
		delete_all(&headc);
		return ERR_NODE;
	}
	
	head = add_node(head, node);
	rc = listcmp(head, headc);
	
	delete_all(&head);
	delete_all(&headc);
	return rc;
}

int test_listlen(job *arr, int k)
{
	if (!arr)
		return ERR_LIST;
	int rc = 0;
	node_t *head = NULL;
	
	rc = create_joblist(&head, arr, k);
	if (rc != OK)
	{
		delete_all(&head);
		return ERR_LIST;
	}
	
	rc = 0;
	if (listlen(head) != k)
		rc = 1;
	
	delete_all(&head);
	return rc;
}

int test_get_node(job *arr, int k, int i)
{
	if (!arr)
		return ERR_LIST;
	int rc = 0;
	node_t *head = NULL;
	
	rc = create_joblist(&head, arr, k);
	if (rc != OK)
	{
		delete_all(&head);
		return ERR_LIST;
	}
	
	rc = 0;
	node_t *node = get_node(head, i);
	if (!head || i < 1 || i > k)
	{
		if (node)
			rc = 1;
	}
	else if (!node)
		rc = 1;
	else if (node->data != &arr[i - 1])
		rc = 1;
	
	delete_all(&head);
	return rc;
}

int test_pop_back(job *arr, int k1, int k2)
{
	if (!arr)
		return ERR_LIST;
	int rc = 0;
	node_t *head = NULL, *headc = NULL;
	
	rc = create_joblist(&head, arr, k1);
	if (rc != OK)
	{
		delete_all(&head);
		return ERR_LIST;
	}
	
	rc = create_joblist(&headc, arr, k2);
	if (rc != OK)
	{
		delete_all(&head);
		delete_all(&headc);
		return ERR_LIST;
	}
	
	void *data = pop_back(&head);
	rc = 0;
	if (k1 == 0)
	{
		if (data != NULL)
			rc = 1;
	}
	else if (k2 < 0 || k2 > k1)
		rc = 1;
	else if (data != &arr[k2])
		rc = 1;
	else
		rc = listcmp(head, headc);
	
	delete_all(&head);
	delete_all(&headc);
	return rc;
}

int test_insert(job *arr1, job *arr2, void *data, int k1, int k2, int i)
{
	if (!arr1 || !arr2 || !data || k1 < 0 || k2 < 0)
		return ERR_LIST;
	int rc = 0;
	node_t *head = NULL, *headc = NULL;
	
	node_t *node = NULL;
	int rcode = create_node(&node, data);
	if (rcode != OK)
		return ERR_NODE;
	
	rc = create_joblist(&head, arr1, k1);
	if (rc != OK)
	{
		delete_all(&head);
		free(node);
		return ERR_LIST;
	}
	
	rc = create_joblist(&headc, arr2, k2);
	if (rc != OK)
	{
		delete_all(&head);
		delete_all(&headc);
		free(node);
		return ERR_LIST;
	}
	
	node_t *before = get_node(head, i);
	
	if (head && (i < 1 || i > k1))
	{
		if (before)
			rc = 1;
		free(node);
	}
	else if (!before && head)
	{
		rc = 1;
		free(node);
	}
	else
	{
		insert(&head, node, before);
		rc = listcmp2(head, headc);
	}
	delete_all(&head);
	delete_all(&headc);
	return rc;
}

int test_dupl(job *arr1, job *arr2, int k1, int k2)
{
	if (!arr1 || !arr2)
		return ERR_LIST;
	int rc = 0;
	node_t *head = NULL, *headc = NULL;
	
	rc = create_joblist(&head, arr1, k1);
	if (rc != OK)
	{
		delete_all(&head);
		return ERR_LIST;
	}
	
	rc = create_joblist(&headc, arr2, k2);
	if (rc != OK)
	{
		delete_all(&head);
		delete_all(&headc);
		return ERR_LIST;
	}
	
	remove_duplicates(&head, jobcmp);
	if (k2 == 0)
	{
		if (head != NULL)
			rc = 1;
	}
	else
		rc = listcmp2(head, headc);
	
	delete_all(&head);
	delete_all(&headc);
	return rc;
}

int test_split(job *arr, int k1, int k2, int k3)
{
	if (!arr)
		return ERR_LIST;
	int rc = 0;
	node_t *head = NULL, *back = NULL;
	node_t *head1 = NULL, *head2 = NULL;
	
	rc = create_joblist(&head, arr, k1);
	if (rc != OK)
	{
		delete_all(&head);
		return ERR_LIST;
	}
	
	rc = create_joblist(&head1, arr, k2);
	if (rc != OK)
	{
		delete_all(&head);
		delete_all(&head1);
		return ERR_LIST;
	}
	
	rc = create_joblist(&head2, &arr[k2], k3);
	if (rc != OK)
	{
		delete_all(&head);
		delete_all(&head1);
		delete_all(&head2);
		return ERR_LIST;
	}
	
	front_back_split(head, &back);
	if (k2 == 0 && head)
		rc = 1;
	else if (k3 == 0 && back)
		rc = 1;
	else
	{
		rc = listcmp(head, head1);
		if (rc == 0)
			rc = listcmp(back, head2);
	}
	
	delete_all(&head);
	delete_all(&back);
	delete_all(&head1);
	delete_all(&head2);
	return rc;
}

int test_merge(job *arr, job *res, int k1, int k2, int k3)
{
	if (!arr)
		return ERR_LIST;
	int rc = 0;
	node_t *head_a = NULL, *head_b = NULL;
	node_t *head = NULL, *headc = NULL;
	
	rc = create_joblist(&head_a, arr, k1);
	if (rc != OK)
	{
		delete_all(&head_a);
		return ERR_LIST;
	}
	
	rc = create_joblist(&head_b, &arr[k1], k2);
	if (rc != OK)
	{
		delete_all(&head_a);
		delete_all(&head_b);
		return ERR_LIST;
	}
	
	rc = create_joblist(&headc, res, k3);
	if (rc != OK)
	{
		delete_all(&headc);
		delete_all(&head_a);
		delete_all(&head_b);
		return ERR_LIST;
	}
	
	head = sorted_merge(&head_a, &head_b, jobcmpsal);
	if (head_a || head_b)
		rc = 1;
	else if (k3 == 0 && head)
		rc = 1;
	else
		rc = listcmp2(head, headc);
	
	delete_all(&head);
	delete_all(&headc);
	delete_all(&head_a);
	delete_all(&head_b);
	return rc;
}

int test_sort(job *arr1, job *arr2, int k)
{
	if (!arr1 || !arr2)
		return ERR_LIST;
	int rc = 0;
	node_t *head = NULL, *headc = NULL;
	
	rc = create_joblist(&head, arr1, k);
	if (rc != OK)
	{
		delete_all(&head);
		return ERR_LIST;
	}
	
	rc = create_joblist(&headc, arr2, k);
	if (rc != OK)
	{
		delete_all(&head);
		delete_all(&headc);
		return ERR_LIST;
	}
	
	head = sort(head, jobcmpsal);
	if (k == 0)
	{
		if (head != NULL)
			rc = 1;
	}
	else
		rc = listcmp2(head, headc);
	
	delete_all(&head);
	delete_all(&headc);
	return rc;
}