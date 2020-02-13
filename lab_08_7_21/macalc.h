/**
 * \file matrixio.h
 * \brief Matrices calculation functions
 **/
#ifndef __MACALC_H__
#define __MACALC_H__

/**
 * \fn void matrsum(double **ma1, double **ma2, double **ma, int n, int m)
 * \brief Function, which sums two matrices
 * \param [in] ma1 pointer to 1st matrix
 * \param [in] ma2 pointer to 2nd matrix
 * \param [in] ma pointer to result matrix
 * \param [in] n rows amount
 * \param [in] m columns amount
**/
void matrsum(double **ma1, double **ma2, double **ma, int n, int m);

/**
 * \fn void matrmult(double **ma1, double **ma2, double **ma,
	int n1, int m1, int n2, int m2)
 * \brief Function, which multiplies two matrices
 * \param [in] ma1 pointer to 1st matrix
 * \param [in] ma2 pointer to 2nd matrix
 * \param [in] ma pointer to result matrix
 * \param [in] n1 rows amount of 1st matrix
 * \param [in] m1 columns amount of 1st matrix
 * \param [in] n2 rows amount of 2nd matrix
 * \param [in] m2 columns amount of 2nd matrix
**/
void matrmult(double **ma1, double **ma2, double **ma,
	int n1, int m1, int n2, int m2);

/**
 * \fn int matrrev(double **ma, double **mar, int n)
 * \brief Function, which multiplies two matrices
 * \param [in] ma pointer to source matrix
 * \param [in] mar pointer to result matrix
 * \param [in] n rows & columns amount of 1st matrix
 * \return error code
**/	
int matrrev(double **ma, double **mar, int n);

#endif