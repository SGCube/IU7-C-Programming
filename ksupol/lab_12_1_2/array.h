#ifndef __ARRAY__H__
#define __ARRAY__H__

#ifdef T
#define TYPE(a) ARR_DLL a ARR_DECL
#define ARR_DECL __cdecl

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#else
#define  TYPE(a) a
#endif

TYPE(void) mysort(void *base, size_t nmemb, size_t size,
	int (*compar)(const void *, const void *));
TYPE(int) cmpint(const void *pa, const void *pb);
TYPE(int) cmpchar(const void *pa, const void *pb);
TYPE(int) cmpfloat(const void *pa, const void *pb);
TYPE(void) movarr(char *pbeg, char *pend, size_t size);
TYPE(int) calc_amount(const int *pa, const int *pb);
TYPE(int) key(const int *pa, const int *pb,
	int *pa_new, int **pb_new, int am);

#endif