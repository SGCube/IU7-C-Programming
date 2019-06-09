#ifndef __ARR__IO__H__

#define __ARR__IO__H__

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

FN_TYPE(int) array_len(FILE *f);

FN_TYPE(int) read_array(FILE *f, int *pb, int **pe, int n);

FN_TYPE(int) print_array(FILE *f, const int *pb, const int *pe);

#endif