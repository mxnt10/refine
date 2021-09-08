#include <iostream>

#include "err_msg.h"

using namespace std;

void err_num( char *x, char *y, int z ) {
    string msg = "number.";
    if ( z == 1 ) msg = "correct delimiter.";
    cerr << x << ": Invalid argument, '" << y << "' is not a " << msg << endl;
    exit(1);
}

void err_parm( char *x, bool y, char z, const char *msg ) {
    if ( y ) cerr << x << ": Parameter '" << z << "' is repeated." << endl;
    else cerr << x << ": " << msg << endl;
    exit(1);
}

void err_file( char *x, char *y, int z ) {
    if ( z == 1 ) cerr << x << ": No file entries." << endl;
    else cerr << x << ": File '" << y << "' not exist." << endl;
    exit(1);
}

void err_cs_first( char *x ) {
    cerr << x << ": The command must start with the parameters '-f', '-l', '-d' and '-i'." << endl;
    exit(1);
}

void err_cs( char *x ) {
    cerr << x << ": the parameters '-c' and '-s' must not be combined." << endl;
    exit(1);
}
