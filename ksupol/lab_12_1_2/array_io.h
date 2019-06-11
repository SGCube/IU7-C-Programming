#ifndef __ARRAY__IO__H__
#define __ARRAY__IO__H__

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

TYPE(int) readarr(FILE *f, int **pa, int **pb);
TYPE(int) printarr(FILE *f, const int *pa, const int *pb);

#endif