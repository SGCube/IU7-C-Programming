#ifndef __ARR__LIB__H__

#define __ARR__LIB__H__

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)	
#endif

#define ARR_DECL __cdecl

ARR_DLL int ARR_DECL is_prime(int x);

ARR_DLL void ARR_DECL arr_fill_prime(int *arr, int n);

ARR_DLL void ARR_DECL arr_copy_spec(int *arr1, int *arr2,
	int n1, int *n2, int num);

#endif