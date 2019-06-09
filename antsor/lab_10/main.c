#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "error.h"
#include "list.h"
#include "job.h"

int main(int argc, char **argv)
{
	int rc = OK, kjob = 0;
	FILE *fin = NULL, *fout = NULL;
	node_t *head = NULL;
	job *data_arr = NULL;
	char act = 0;
	setbuf(stdout, NULL);
	
	if (argc < 2)
	{
		errmsg(ERR_ARG);
		return ERR_ARG;
	}
	if (strcmp(argv[1], "h") == 0)
	{
		printf("only app.exe <action> <input_file> <output_file>\n"
			"action:\n"
			"\t* p - only print list (output not needed)\n"
			"\t* b - pop last elem from list\n"
			"\t* i - insert elem to list\n"
			"\t* d - remove duplicates from list\n"
			"\t* s - sort list by salary (min -> max)\n");
		return OK;
	}
	
	act = argv[1][0];
	if (argc < 3 || (argc < 4 && act != 'p'))
	{
		errmsg(ERR_ARG);
		return ERR_ARG;
	}
	if (act != 'p' && act != 'b' && act != 'i' && act != 'd' && act != 's')
	{
		errmsg(ERR_FLAG);
		return ERR_FLAG;
	}
	fin = fopen(argv[2], "r");
	if (!fin)
	{
		errmsg(ERR_FILE);
		return ERR_FILE;
	}
	if (act != 'p')
	{
		fout = fopen(argv[3], "w");
		if (!fout)
		{
			errmsg(ERR_FILE);
			fclose(fin);
			return ERR_FILE;
		}
	}
	
	data_arr = malloc(N_ALLOC * sizeof(job));
	if (!data_arr)
	{
		errmsg(rc);
		fclose(fin);
		if (fout)
			fclose(fout);
		return rc;
	}
	
	rc = read_joblist(fin, &head, &data_arr, &kjob);
	if (rc != OK)
	{
		errmsg(rc);
		fclose(fin);
		if (fout)
			fclose(fout);
		free_all_jobs(data_arr, kjob);
		delete_all(&head);
		return rc;
	}
	fclose(fin);
	
	printf("LIST:\n");
	print_joblist(head, stdout);
	
	if (act == 'p')
	{
		free_all_jobs(data_arr, kjob);
		delete_all(&head);
		return OK;
	}
	if (act == 'b')
	{
		void *data = pop_back(&head);
		if (data)
		{
			printf("\nPopped out data:\n");
			print_job(data, stdout);
		}
	}
	if (act == 'i')
		job_insert(&head, &data_arr, &kjob);
	if (act == 'd')
		remove_duplicates(&head, jobcmp);
	if (act == 's')
		head = sort(head, jobcmpsal);
	
	if (rc == OK)
	{
		printf("\nLIST:\n");
		print_joblist(head, stdout);
		print_joblist(head, fout);
	}
	
	errmsg(rc);
	fclose(fout);
	free_all_jobs(data_arr, kjob);
	delete_all(&head);
	return OK;
}