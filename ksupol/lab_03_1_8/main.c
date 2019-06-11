#include <stdio.h>
#define OK 1
#define ERR_CMD 1
#define ERR_IO 2
int process(FILE *f,int *min_len)
{
	int prv, cur, nxt, pos = 0, prv_max = -2, cur_len, rc;
	if (fscanf(f,"%d",&prv)==1)
	{
		if (fscanf(f,"%d",&cur)== 1)
		{
			pos = 1;
			while (fscanf(f,"%d", &nxt) == 1)
			{
				if ((prv < cur) && (cur > nxt))
				{
					if (prv_max != -2)
					{
						cur_len = pos - prv_max;
						if (*min_len <= 0 || cur_len < *min_len)
							*min_len = cur_len;
					}
					else
						*min_len = 0;
					
					prv_max = pos;	
				}
				prv = cur;
				cur = nxt;
				pos += 1;
				
			}
		}
		rc = OK;
	}
	else
		rc = ERR_IO;
	return rc;
}
int main(int argc, char **argv)
{
	FILE *f;
	int rc = OK, min_len = -1;
	if (argc != 2)
	{
		printf("No files\n");
		
		rc = ERR_CMD;
	}
	else
	{
		f = fopen(argv[1], "r");     
		if (f == NULL)     
		{         
			printf("This file doesn't exist\n"); 
		
			rc = ERR_CMD;     
		} 
		else if (process(f, &min_len) == OK)
		{
			if (min_len == -1)
				printf("There are no local maximums\n");
			else if (min_len == 0)
				printf("There are only one local maximum\n");
			else
				printf("The distance between two local maximums is %d\n", min_len );
		}
		else
			printf("Incorrect data\n");
	}
	return rc;
}