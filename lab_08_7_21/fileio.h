/**
 * \file fileio.h
 * \brief File open/close function headers
 **/
#ifndef __FILEIO_H__
#define __FILEIO_H__

/**
 * \fn int file_open(char act, char **argv, FILE **fin1, FILE **fin2,
 * FILE **fout)
 * \brief Function, which opens input and output files
 * \param [in] act type of action
 * \param [in] argv array of strings which contains arguments
 * \param [in-out] fin1 1st input file
 * \param [in-out] fin2 2nd input file
 * \param [in-out] fout output file
 * \return error code
**/
int file_open(char act, char **argv, FILE **fin1, FILE **fin2, FILE **fout);

/**
 * \fn void ioerror_msg(int rc, char *fname)
 * \brief Function, which prints file or I/O handling error message
 * \param [in] rc error code
 * \param [in] fname name of file with error
**/
void ioerror_msg(int rc, char *fname);

/**
 * \fn void fclose_all(FILE *f1, FILE *f2, FILE *f3)
 * \brief Function, which closes 3 files
 * \param [in-out] f1 1st file
 * \param [in-out] f2 2nd file
 * \param [in-out] f3 3rd file
**/
void fclose_all(FILE *f1, FILE *f2, FILE *f3);
#endif