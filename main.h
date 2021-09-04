#ifndef REFN_MAIN_H
#define REFN_MAIN_H

/** Default value for -f and -l parameters. **/

#define default_view 10

/** Error messages for function err_parm(). **/

#define msg_err_first   "Parameter 'f' cannot be used with 'l', 'd' and 'i'."
#define msg_err_last    "Parameter 'l' cannot be used with 'f', 'd' and 'i'."
#define msg_err_delimit "Parameter 'd' cannot be used with 'f', 'l' and 'i'."
#define msg_err_invert  "Parameter 'i' cannot be used with 'f', 'l' and 'd'."
#define msg_err_color   "Parameter 'c' must be used with 'f', 'l', 'd' or 'i'."
#define msg_err_simple  "Parameter 's' must be used with 'f', 'l', 'd' or 'i'."

/** Functions declaration. **/

void help( char *x );

#endif /** REFN_MAIN_H **/