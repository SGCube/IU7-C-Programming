#ifndef __ERROR_H__
#define __ERROR_H__

#define OK 0
#define ERR_ARG -1
#define ERR_FLAG -2
#define ERR_FILE -3
#define ERR_ALLOC -4
#define ERR_EMPTY -5
#define ERR_INPUT -6
#define ERR_INDEX -7

#define ERR_LIST -101
#define ERR_NODE -102

void errmsg(int rc);

#endif