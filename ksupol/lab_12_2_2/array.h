#ifndef __ARRAY__H__
#define __ARRAY__H__

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

ARR_DLL void ARR_DECL fibon(int *arr, int am);
ARR_DLL void ARR_DECL first_entry(int *arr, int am, int *arr_2, int *am_2);

#endif