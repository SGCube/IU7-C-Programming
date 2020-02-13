/**
 * \file sort.h
 * \brief Sort & filter function header
 * \details File which contains sorting and filtering function headers
**/
#ifndef __SORT_H__
#define __SORT_H__

/**
 * \fn int key(const int *pb_src, const int *pe_src, int **pb_dstm int **pe_dst)
 * \brief Filter elements by key
 * \details Function, which create new array from numbers which larger than average
 * \param [in] *pb_src pointer to first number of source array
 * \param [in] *pe_src pointer to after last number of source array
 * \param [out] *pb_dst pointer to first number of new array
 * \param [out] *pe_dst pointer to after last number of new array
 * \return error code
**/
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

/**
 * \fn int compar_int(const void *pa, const void *pb)
 * \brief Compare function
 * \details Function, which compares two integer elements
 * \param [in] *pa pointer to first element
 * \param [in] *pb pointer to second element
 * \return <0 - second larger, 0 - equal, >0 - first larger
**/
int compar_int(const void *pa, const void *pb);
/**
 * \fn int compar_float(const void *pa, const void *pb)
 * \brief Compare function
 * \details Function, which compares two float elements
 * \param [in] *pa pointer to first element
 * \param [in] *pb pointer to second element
 * \return <0 - second larger, 0 - equal, >0 - first larger
**/
int compar_float(const void *pa, const void *pb);
/**
 * \fn int compar_char(const void *pa, const void *pb)
 * \brief Compare function
 * \details Function, which compares two char elements
 * \param [in] *pa pointer to first element
 * \param [in] *pb pointer to second element
 * \return <0 - second larger, 0 - equal, >0 - first larger
**/
int compar_char(const void *pa, const void *pb);

/**
 * \fn void shift(char *pb, char *pe, size_t size)
 * \brief Shift right function
 * \details Function, which shifts right all elements in queue
 * and places last into beginning
 * \param [in] *pb pointer to first element in queue
 * \param [in] *pe pointer to after last element in queue
 * \param [in] size size of variable type
**/
int shift(char *pb, char *pe, size_t size);

/**
 * \fn void mysort(void *base, size_t nmemb, size_t size,
 * int (*compar)(const void*, const void*))
 * \brief Sorting function
 * \details Function, which sorts array of numbers
 * \param [in-out] *base pointer to first element
 * \param [in] nmemb amount of elements
 * \param [in] size size of element
 * \param [in] *compar() function comparing two numbers
**/
int mysort(void *base, size_t nmemb, size_t size,
	int (*compar)(const void*, const void*));

#endif