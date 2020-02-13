#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "list.h"
#include "job.h"
#include "test_list.h"

void testmsg(int i, int rc)
{
	switch (rc)
	{
		case 0:
			printf("#%d\t%s\n", i, "PASSED");
			break;
		case 1:
			printf("#%d\t%s\n", i, "FAILED");
			break;
		case ERR_LIST:
			printf("#%d\t%s\n", i, "LIST CREATE ERROR");
			break;
		case ERR_NODE:
			printf("#%d\t%s\n", i, "NODE CREATE ERROR");
			break;
		default:
			printf("#%d\t%s\n", i, "UNKNOWN ERROR");
	}
}

void test_add_node_call(void)
{
	job data[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 }
		};
	printf("add_node:\n");
	// INCORRECT (node = NULL)
	testmsg(0, test_add_node(data, 2, 2, -1));
	// CORRECT
	int kk[] = { 1, 2, 3 };
	for (int i = 0; i < sizeof(kk) / sizeof(kk[0]); i++)
		testmsg(i + 1, test_add_node(data, kk[i] - 1, kk[i], kk[i] - 1));
	printf("\n");
}

void test_listlen_call(void)
{
	job data[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 }
		};
	printf("listlen:\n");
	int kk[] = { 0, 1, 3 };
	for (int i = 0; i < sizeof(kk) / sizeof(kk[0]); i++)
		testmsg(i + 1, test_listlen(data, kk[i]));
	printf("\n");
}

void test_get_node_call(void)
{
	job data[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 }
		};
	printf("get_node:\n");
	int kk[] = { 1, 0, 3, 1, 3, 3, 3 };
	int ii[] = { 0, 1, 4, 1, 1, 2, 3 };
	for (int i = 0; i < sizeof(kk) / sizeof(kk[0]); i++)
		testmsg(i + 1, test_get_node(data, kk[i], ii[i]));
	printf("\n");
}

void test_pop_back_call(void)
{
	job data[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 }
		};
	printf("pop_back:\n");
	// EMPTY
	testmsg(0, test_pop_back(data, 0, 0));
	// OTHER
	int kk[] = { 1, 2, 3 };
	for (int i = 0; i < sizeof(kk) / sizeof(kk[0]); i++)
		testmsg(i + 1, test_pop_back(data, kk[i], kk[i] - 1));
	printf("\n");
}

void test_insert_call(void)
{
	job data0[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 }
		};
	job data1[] = {
		{ "Java-Programmer", 200000 },
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 }
		};
	job data2[] = {
		{ "C-Programmer", 80000 },
		{ "Java-Programmer", 200000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 }
		};
	job data3[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "Java-Programmer", 200000 },
		{ "System Administrator", 100000 }
		};
	
	job *indata = malloc(sizeof(job));
	if (!indata)
		return;
	indata->name = "Java-Programmer";
	indata->salary = 200000;
	
	printf("insert:\n");
	testmsg(1, test_insert(data0, data0, (void *)indata, 2, 2, 0));
	testmsg(2, test_insert(data0, data0, (void *)indata, 2, 2, 4));
	testmsg(3, test_insert(data0, data1, (void *)indata, 0, 1, 1));
	testmsg(4, test_insert(data0, data1, (void *)indata, 1, 2, 1));
	testmsg(5, test_insert(data0, data1, (void *)indata, 3, 4, 1));
	testmsg(6, test_insert(data0, data2, (void *)indata, 3, 4, 2));
	testmsg(7, test_insert(data0, data3, (void *)indata, 3, 4, 3));
	printf("\n");
	free(indata);
}

void test_dupl_call(void)
{
	job data0[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 }
		};
	job data1_0[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "C-Programmer", 80000 }
		};
	job data1_1[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 }
		};
	job data2_0[] = {
		{ "C-Programmer", 80000 },
		{ "C-Programmer", 80000 },
		{ "C-Programmer", 80000 }
		};
	job data2_1[] = {
		{ "C-Programmer", 80000 }
		};
	job data3_0[] = {
		{ "C-Programmer", 80000 },
		{ "Java-Programmer", 60000 },
		{ "C-Programmer", 80000 },
		{ "Java-Programmer", 60000 }
		};
	job data3_1[] = {
		{ "C-Programmer", 80000 },
		{ "Java-Programmer", 60000 }
		};
	
	printf("remove_duplicates:\n");
	testmsg(1, test_dupl(data0, data0, 0, 0));
	testmsg(2, test_dupl(data0, data0, 1, 1));
	testmsg(3, test_dupl(data1_0, data1_1, 3, 2));
	testmsg(4, test_dupl(data2_0, data2_1, 3, 1));
	testmsg(5, test_dupl(data3_0, data3_1, 4, 2));
	printf("\n");
}

void test_split_call(void)
{
	job data[] = {
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 },
		{ "Java-Programmer", 60000 },
		{ "C-Programmer", 60000 },
		};
	
	printf("front_back_split:\n");
	testmsg(1, test_split(data, 0, 0, 0));
	testmsg(2, test_split(data, 1, 1, 0));
	testmsg(3, test_split(data, 2, 1, 1));
	testmsg(4, test_split(data, 3, 2, 1));
	testmsg(5, test_split(data, 4, 2, 2));
	testmsg(6, test_split(data, 5, 3, 2));
	printf("\n");
}

void test_merge_call(void)
{
	job data1[] = {
		{ "C-Programmer", 80000 }
		};
	job res1[] = {
		{ "C-Programmer", 80000 }
		};
	
	job data2_1[] = {
		{ "Java-Programmer", 65000 },
		{ "C-Programmer", 80000 },
		};
	job data2_2[] = {
		{ "C-Programmer", 80000 },
		{ "Java-Programmer", 65000 },
		};	
	job res2[] = {
		{ "Java-Programmer", 65000 },
		{ "C-Programmer", 80000 }
		};
	
	job data3_1[] = {
		{ "Data Scientist", 75000 },
		{ "Java-Programmer", 65000 },
		{ "C-Programmer", 80000 },
		};
	job data3_2[] = {
		{ "Data Scientist", 75000 },
		{ "C-Programmer", 80000 },
		{ "Java-Programmer", 65000 },
		};
		
	job res3[] = {
		{ "Java-Programmer", 65000 },
		{ "Data Scientist", 75000 },
		{ "C-Programmer", 80000 }
		};
	
	job data4[] = {
		{ "Java-Programmer", 65000 },
		{ "C-Programmer", 80000 },
		{ "Data Scientist", 75000 },
		{ "System Administrator", 100000 }
		};	
	job res4[] = {
		{ "Java-Programmer", 65000 },
		{ "Data Scientist", 75000 },
		{ "C-Programmer", 80000 },
		{ "System Administrator", 100000 }
		};
	
	job data5_1[] = {
		{ "C-Programmer", 60000 },
		{ "Data Scientist", 75000 },
		{ "C-Programmer", 80000 },
		{ "Java-Programmer", 65000 },
		{ "System Administrator", 100000 }
		};
	job data5_2[] = {
		{ "C-Programmer", 60000 },
		{ "System Administrator", 100000 },
		{ "Java-Programmer", 65000 },
		{ "Data Scientist", 75000 },
		{ "C-Programmer", 80000 }
		};
	job res5[] = {
		{ "C-Programmer", 60000 },
		{ "Java-Programmer", 65000 },
		{ "Data Scientist", 75000 },
		{ "C-Programmer", 80000 },
		{ "System Administrator", 100000 }
		};
	
	printf("merge:\n");
	testmsg(1, test_merge(data1, res1, 0, 0, 0));
	testmsg(2, test_merge(data1, res1, 1, 0, 1));
	testmsg(3, test_merge(data1, res1, 0, 1, 1));
	testmsg(4, test_merge(data2_1, res2, 1, 1, 2));
	testmsg(5, test_merge(data2_2, res2, 1, 1, 2));
	testmsg(6, test_merge(data3_1, res3, 1, 2, 3));
	testmsg(7, test_merge(data3_2, res3, 2, 1, 3));
	testmsg(8, test_merge(data4, res4, 2, 2, 4));
	testmsg(9, test_merge(data5_1, res5, 3, 2, 5));
	testmsg(10, test_merge(data5_2, res5, 2, 3, 5));
	printf("\n");
}

void test_sort_call(void)
{	
	job data2[] = {
		{ "C-Programmer", 80000 }
		};
		
	job data3[] = {
		{ "C-Programmer", 80000 },
		{ "C-Programmer", 80000 },
		{ "C-Programmer", 80000 }
		};
		
	job data4[] = {
		{ "Java-Programmer", 60000 },
		{ "C-Programmer", 65000 },
		{ "System Administrator", 100000 }
		};
		
	job data5[] = {
		{ "System Administrator", 100000 },
		{ "C-Programmer", 65000 },
		{ "Java-Programmer", 60000 }
		};
		
	job data6[] = {
		{ "Java-Programmer", 60000 },
		{ "C-Programmer", 65000 },
		{ "System Administrator", 100000 },
		{ "C-Programmer", 65000 },
		{ "C-Programmer", 80000 }
		};
	
	job res6[] = {
		{ "Java-Programmer", 60000 },
		{ "C-Programmer", 65000 },
		{ "C-Programmer", 65000 },
		{ "C-Programmer", 80000 },
		{ "System Administrator", 100000 }
		};
	
	printf("sort:\n");
	testmsg(1, test_sort(data2, data2, 0));
	testmsg(2, test_sort(data2, data2, 1));
	testmsg(3, test_sort(data3, data3, 3));
	testmsg(4, test_sort(data4, data4, 3));
	testmsg(5, test_sort(data5, data4, 3));
	testmsg(6, test_sort(data6, res6, 5));
	printf("\n");
}

int main()
{
	setbuf(stdout, NULL);
	test_add_node_call();
	test_listlen_call();
	test_get_node_call();
	test_pop_back_call();
	test_insert_call();
	test_dupl_call();
	test_split_call();
	test_merge_call();
	test_sort_call();
	return 0;
}