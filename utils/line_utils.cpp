#include <iomanip>
#include <fstream>
#include <iostream>

#include "line_utils.h"
#include "file_utils.h"
#include "parm.h"

using namespace std;

/** To read the first lines of the files. **/

int view_lines( bool s, bool c, char p, char *f, long int x, unsigned long int y ) {
    int cnt = 0;
    string data;
    string blue, green, red, reset;
    if ( c ) {
        blue = BLUE;
        green = GREEN;
        red = RED;
        reset = RESET;
    }
    if ( !s ) cout << red << endl << f << ":" << reset << endl;
    ifstream file(f);

    /** To read the first lines of the files. **/

    if ( p == parm_f ) {
        while ( !file.fail() ) {
            cnt++;
            getline(file, data);
            if ( cnt <= x ) {
                if ( !s ) cout << blue << setw(10) << cnt << green << ": " << reset << data << endl;
                else cout << data << endl;
            }
        }
    }

    /** To read the last lines of the files. **/

    if ( p == parm_l ) {
        int lines = count_lines(f);
        while ( !file.fail() ) {
            cnt++;
            getline(file, data);
            if ( cnt >= (lines - x) ) {
                if ( cnt != lines ) {
                    if ( !s ) cout << blue << setw(10) << cnt << green << ": " << reset << data << endl;
                    else cout << data << endl;
                }
            }
        }
    }

    /** To read the specific lines of the files. **/

    if ( p == parm_d ) {
        if ( y == nullarg ) y = x;
        while ( !file.fail() ) {
            cnt++;
            getline(file, data);
            if ( cnt >= x && cnt <= y ) {
                if ( !s ) cout << blue << setw(10) << cnt << green << ": " << reset << data << endl;
                else cout << data << endl;
            }
        }
    }

    /** To read inverted the specific lines of the files. **/

    if ( p == parm_i ) {
        int lines = count_lines(f);
        if ( y == nullarg ) y = x;
        while ( !file.fail() ) {
            cnt++;
            getline(file, data);
            if ( cnt >= (lines + 1 - y) && cnt <= (lines + 1 - x) ) {
                if ( !s ) cout << blue << setw(10) << cnt << green << ": " << reset << data << endl;
                else cout << data << endl;
            }
        }
    }

    file.close();
    return (0);
}
