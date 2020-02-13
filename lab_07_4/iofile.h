/**
 * \file iofile.h
 * \brief File I/O function headers
 * \details Code contains input/output array from/into file functions headers
**/
#ifndef __IOFILE_H__
#define __IOFILE_H__

/**
 * \fn int read_array(FILE *f, int *arr, int n)
 * \brief Read array from file function
 * \details Function, which read array of numbers from file
 * \param [in] *f pointer to input file variable
 * \param [out] **pb pointer to pointer to first number of array
 * \param [out] **pb pointer to pointer to number after last of array
 * \return error code
**/
int read_array(FILE *f, int **pb, int **pe);
/**
 * \fn int print_array(FILE *f, int *pb, int *pe)
 * \brief Print array into file function
 * \details Function, which print array of numbers into file
 * \param [in] *f pointer to output file variable
 * \param [in] *pb pointer to first element of array
 * \param [in] *pe pointer to after last element of array
 * \return error code
**/
int print_array(FILE *f, const int *pb, const int *pe);

#endif