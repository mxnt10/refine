#include <stdexcept>
#include <cstring>

#include "control_utils.h"

using namespace std;

/** Validate number. **/

int number_validate( char *x ) {
    int st = 1;
    try {
        int param_number = stoi(x, nullptr, 0);
        string check = to_string(param_number);
        if ( check == x ) st = 0;
        return (st);
    } catch ( const invalid_argument &ia ) {
        return (st);
    }
}

/** Verify if delimit for -d and -i is "-". **/

int check_delimit( char *x ) {
    int compare, ctl = 1;
    char check;
    for ( compare = 0; compare < strlen(x); compare++ ) {
        check = x[compare];
        if ( check == '-' ) ctl = 0;
    }
    return (ctl);
}
