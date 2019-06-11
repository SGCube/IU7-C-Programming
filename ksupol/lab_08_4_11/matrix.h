#ifndef __MATRIX_H__
#define __MATRIX_H__
int file_work(int argc, char **argv, FILE **f1, FILE **f2, FILE **f3);
int read_str_col(FILE *f1, int *n, int *m);
double **allocate_matrix(int n, int m);
int read_matrix(FILE *f, double ***matrix, int n, int m);
void free_matrix(double **matrix);
void err_code(int rc, char *argv);
void addition(double **matrix1, int n, int m,
	double **matrix2, double **matrix3);
void multiply(double **matrix1, int n, int m,
	int q, double **matrix2, double **matrix3);

double **matr(double **a, int n, int x, double **res);
double det(double **a, int n);
void print_matrix(FILE *f, int n, int m, double **matrix);
void print_det(FILE *f, double det);
#endif