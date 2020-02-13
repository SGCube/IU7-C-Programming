#include <stdio.h>
#include "error.h"

void errmsg(int rc)
{
	switch (rc)
	{
		case OK:
			break;
		case ERR_ARG:
			printf("Not enough arguments!\n");
			break;
		case ERR_FLAG:
			printf("Invalid flag!\n");
			break;
		case ERR_FILE:
			printf("Can't open a file!\n");
			break;
		case ERR_ALLOC:
			printf("Memory allocation error!\n");
			break;
		case ERR_EMPTY:
			printf("Empty file!\n");
			break;
		case ERR_INPUT:
			printf("Input error!\n");
			break;
		case ERR_INDEX:
			printf("Invalid index!\n");
			break;
		default:
			printf("Unknown error!\n");
			break;
	}
}