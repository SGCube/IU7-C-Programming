#ifndef __ARR__SORT__H__

#define __ARR__SORT__H__

#ifdef DLL_BUILD

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

#define FN_TYPE(T) ARR_DLL T ARR_DECL

#else
#define FN_TYPE(T) T

#endif

FN_TYPE(int) arr_avg(const int *pb_src, const int *pe_src,
	float *avg);

FN_TYPE(int) key(const int *pb_src, const int *pe_src,
	int *pb_dst, int **pe_dst, float avg);

FN_TYPE(int) compar_int(const void *pa, const void *pb);

FN_TYPE(int) compar_float(const void *pa, const void *pb);

FN_TYPE(int) compar_char(const void *pa, const void *pb);

FN_TYPE(int) shift(char *pb, char *pe, size_t size);

FN_TYPE(void) mysort(void *base, size_t nmemb, size_t size,
	int (*compar)(const void*, const void*));

#endif