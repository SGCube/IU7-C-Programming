/**
 * \file matrixio.h
 * \brief Matrix I/O from/to file functions
 **/
#ifndef __MATRIXIO_H__
#define __MATRIXIO_H__

/**
 * \fn int read_matrix_size(FILE *f, int *n, int *m)
 * \brief Function, which reads matrix size
 * \param [in] f source file
 * \param [in-out] n pointer to rows amount
 * \param [in-out] m pointer to columns amount
 * \return error code
**/
int read_matrix_size(FILE *f, int *ro, int *co);
/**
 * \fn int alloc_matrix(int n, int m)
 * \brief Function, which allocates memory for matrix
 * \param [in] n rows amount
 * \param [in] m columns amount
 * \return pointer to matrix or NULL
**/
double **alloc_matrix(int n, int m);

/**
 * \fn void ident_matrix(double **ma, int n, int m)
 * \brief Function, which initialize square matrix as indentiy matrix
 * \param [in] ma pointer to matrix
 * \param [in] n rows & columns amount
**/
void ident_matrix(double **ma, int n);

/**
 * \fn void init_matrix(double **ma, int n, int m)
 * \brief Function, which initialize matrix with nulls
 * \param [in] ma pointer to matrix
 * \param [in] n rows amount
 * \param [in] m columns amount
**/
void init_matrix(double **ma, int n, int m);

/**
 * \fn int read_matrix(FILE *f, double **ma, int n, int m);
 * \brief Function, which reads matrix from file
 * \param [in] f source file 
 * \param [in] ma pointer to matrix
 * \param [in] n rows amount
 * \param [in] m columns amount
 * \return error code
**/
int read_matrix(FILE *f, double **ma, int n, int m);

/**
 * \fn int print_matrix(FILE *f, double **ma, int n, int m);
 * \brief Function, which prints matrix to file
 * \param [in] f output file 
 * \param [in] ma pointer to matrix
 * \param [in] n rows amount
 * \param [in] m columns amount
**/
void print_matrix(FILE *f, double **ma, int n, int m);

#endif