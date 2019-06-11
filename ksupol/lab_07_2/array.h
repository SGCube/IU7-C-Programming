#ifndef __ARRAY_H__
#define __ARRAY_H__
int readarr(FILE *f, int **pa, int **pb);
int printarr(FILE *f, const int *pa, int const *pb);
int key(const int *pa, const int *pb, int **pa_new, int **pb_new);
void mysort(void *base, size_t nmemb, size_t size,
	int (*compar)(const void *, const void *));
int cmpint(const void *pa, const void *pb); // сравнивает два числа
int cmpchar(const void *pa, const void *pb);
int cmpfloat(const void *pa, const void *pb);
void movarr(char *pbeg, char *pend, size_t size);
#endif