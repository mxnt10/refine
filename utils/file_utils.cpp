#include <fstream>
#include "file_utils.h"

using namespace std;

/** Count lines in text files. **/

int count_lines( char *x ) {
    int lines = 0;
    string data;
    ifstream file(x);
    while ( !file.fail() ) {
        getline(file, data);
        lines++;
    }
    file.close();
    return (lines);
}

/** Check if the Parameters is File. **/

int check_files( char *x ) {
    int st = 0;
    ifstream file(x);
    if ( !file ) st = 1;
    file.close();
    return (st);
}
