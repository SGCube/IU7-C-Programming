#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"

#define OK 0
#define ERR_FILE -1
#define ERR_MEMORY -2
#define ERR_NO_AMOUNT -3

#define N 200

typedef unsigned long int tick_t;

tick_t tick(void)
{
	tick_t d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

void time_write(FILE *f, int *pa, int *pb, int n)
{
	assert(f);
	assert(pa && pb);
	assert(n > 0);
	
	tick_t t1, t2;
	
	fprintf(f, "%u\t", n);
	t1 = tick();
	mysort(pa, n, sizeof(int), compar_int);
	t2 = tick();
	fprintf(f, "%lu\t", t2 - t1);
	
	t1 = tick();
	qsort(pb, n, sizeof(int), compar_int);
	t2 = tick();
	fprintf(f, "%lu\n", t2 - t1);
}

int time_sorted(int **pa, int **pb, int n)
{
	assert(n > 0);
	
	*pa = malloc(n * sizeof(int));
	*pb = malloc(n * sizeof(int));
	
	if (!pa || !pb)
		return ERR_MEMORY;
	
	for (int *pc = *pa; pc < *pa + n; pc++)
		*pc = pc - *pa;
	for (int *pc = *pb; pc < *pb + n; pc++)
		*pc = pc - *pb;
	
	return OK;
}

int time_inverted(int **pa, int **pb, int n)
{
	assert(n > 0);
	
	*pa = malloc(n * sizeof(int));
	*pb = malloc(n * sizeof(int));
	
	if (!pa || !pb)
		return ERR_MEMORY;
	
	for (int *pc = *pa; pc < *pa + n; pc++)
		*pc = *pa + n - pc;
	for (int *pc = *pb; pc < *pb + n; pc++)
		*pc = *pb + n - pc;
	
	return OK;
}

int time_random(int **pa, int **pb, int n)
{
	assert(n > 0);
	
	*pa = malloc(n * sizeof(int));
	*pb = malloc(n * sizeof(int));
	
	if (!pa || !pb)
		return ERR_MEMORY;
	
	for (int *pc1 = *pa, *pc2 = *pb; pc1 < *pa + n; pc1++, pc2++)
	{
		*pc1 = rand();
		*pc2 = *pc1;
	}
	
	return OK;
}

int main()
{
	setbuf(stdin, NULL);
	srand(2);
	int rc = OK;
	int *pa = NULL, *pb = NULL;
	
	FILE *f[] = {
		fopen("t_sorted.txt", "w"),
		fopen("t_random.txt", "w"),
		fopen("t_inverted.txt", "w") };
		
	int (*t_func[3])(int **, int **, int) = {
		time_sorted,
		time_random,
		time_inverted };
		
	for (int i = 0; i < 3; i++)
		if (!f[i])
		{
			fprintf(stderr, "Couldn't create output file!");
			rc = ERR_FILE;
			break;
		}
	
	for (int j = 0; j < 3; j++)
	{
		for (int i = 1; i <= N; i++)
		{
			rc = t_func[j](&pa, &pb, i);
			if (rc == OK)
			{
				time_write(f[j], pa, pb, i);
				free(pa);
				free(pb);
			}
			else
				fprintf(stderr, "Memory allocation error!\n");
		}
	}
	
	for (int i = 0; i < 3; i++)
		if (f[i])
			fclose(f[i]);
	
	return rc;
}