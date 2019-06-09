#ifndef __MATRIX__H__

#define __MATRIX__H__

#include <stdio.h>

typedef int item_t;

typedef struct matrix_type* matrix_t;

matrix_t create();

int read(matrix_t ma, FILE *f);

void destroy(matrix_t ma);

void print(matrix_t ma);

void write(matrix_t ma, FILE *f);

int sum(matrix_t ma1, matrix_t ma2, matrix_t ma);

int multiply(matrix_t ma1, matrix_t ma2, matrix_t ma);

int compare(matrix_t ma1, matrix_t ma2);

#endif