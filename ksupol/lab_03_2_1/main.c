#include <stdio.h>
#define OK 0
#define ERR_WRONG_CMD -1
#define ERR_NO_FILE -2
#define ERR_IO -3

 int process(FILE *f, int *kol)
 {     
	float num, min, max, sr;
	
    if (fscanf(f, "%f", &num) == 1)
	{  
		min = num;
		max = num;
		while (fscanf(f, "%f", &num) == 1)   
		{
			if (num > max)                 
				max = num; 
			else if (num < min)
				min = num;
		}
		sr = (min + max) / 2;
		
		rewind(f);
		while (fscanf(f,"%f", &num) == 1)
			if (num > sr)
				*kol += 1;
        return OK;     
	}
	return ERR_IO; 
} 

 int main(int argc, char **argv) 
 {     
	FILE *f; 
	int kol = 0; 
	int rc = OK;
	if (argc != 2)
	{
		printf("No file name\n");
		return ERR_WRONG_CMD;
	}
	else
	{
		f = fopen(argv[1], "r");     
		if (f)     
		{         
			rc = process(f, &kol);
			if (rc == OK)
				printf("Amount is %d\n", kol);
			else				
				printf("Data read error\n");  
		}
		else
		{
			printf("File doesn't exists\n"); 
			rc = ERR_NO_FILE; 
		}
		fclose(f);
	}
	 return rc; 
} 
