#ifndef REF_ERR_MSG_H
#define REF_ERR_MSG_H

void err_num( char *x, char *y, int z );

void err_parm( char *x, bool y, char z, const char *msg );

void err_file( char *x, char *y );

void err_cs_first( char *x );

void err_cs( char *x );

#endif /** REF_ERR_MSG_H **/
