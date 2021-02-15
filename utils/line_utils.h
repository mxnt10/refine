//
// Created by mauricio on 13/02/2021.
//

#ifndef REFINE_LINE_UTILS_H
#define REFINE_LINE_UTILS_H

#define RED "\x1B[31m"
#define BLUE "\x1B[34m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

#endif

#include "file_utils.h"
#include <iomanip>

using namespace std;

/** To read the first lines of the files. **/

int first_lines(int s, int c, int x, char *y) {
    int cnt = 0;
    string data;
    string blue, green, red, reset;
    if (c == 1) {
        blue = BLUE;
        green = GREEN;
        red = RED;
        reset = RESET;
    }
    if (s == 0) {
        cout << red << endl << y << ":" << reset << endl;
    }
    ifstream file(y);
    while (!file.fail()) {
        cnt++;
        getline(file, data);
        if ( cnt <= x) {
            if (s == 0) {
                cout << blue << setw(10) << cnt << green << ": " << reset << data << endl;
            } else {
                cout << data << endl;
            }
        }
    }
    file.close();
    return(0);
}

/** To read the last lines of the files. **/

int last_lines(int s, int c, int x, char *y) {
    int lines = count_lines(y);
    int cnt = 0;
    string data;
    string blue, green, red, reset;
    if (c == 1) {
        blue = BLUE;
        green = GREEN;
        red = RED;
        reset = RESET;
    }
    if (s == 0) {
        cout << red << endl << y << ":" << reset << endl;
    }
    ifstream file(y);
    while (!file.fail()) {
        cnt++;
        getline(file, data);
        if ( cnt >= (lines - x)) {
            if (cnt != lines) {
                if (s == 0) {
                    cout << blue << setw(10) << cnt << green << ": " << reset << data << endl;
                } else {
                    cout << data << endl;
                }
            }
        }
    }
    file.close();
    return(0);
}

/** To read the specific lines of the files. **/

int delimit_lines(int s, int c, int x, int y, char *z) {
    int cnt = 0;
    string data;
    string blue, green, red, reset;
    if (c == 1) {
        blue = BLUE;
        green = GREEN;
        red = RED;
        reset = RESET;
    }
    if (y == 0) {
        y = x;
    }
    if (s == 0) {
        cout << red << endl << z << ":" << reset << endl;
    }
    ifstream file(z);
    while (!file.fail()) {
        cnt++;
        getline(file, data);
        if ( cnt >= x && cnt <= y) {
            if (s == 0) {
                cout << blue << setw(10) << cnt << green << ": " << reset << data << endl;
            } else {
                cout << data << endl;
            }
        }
    }
    file.close();
    return(0);
}

/** To read inverted the specific lines of the files. **/

int invert_lines(int s, int c, int x, int y, char *z) {
    int lines = count_lines(z);
    int cnt = 0;
    string data;
    string blue, green, red, reset;
    if (c == 1) {
        blue = BLUE;
        green = GREEN;
        red = RED;
        reset = RESET;
    }
    if (y == 0) {
        y = x;
    }
    if (s == 0) {
        cout << red << endl << z << ":" << reset << endl;
    }
    ifstream file(z);
    while (!file.fail()) {
        cnt++;
        getline(file, data);
        if ( cnt >= (lines + 1 - y) && cnt <= (lines + 1 - x)) {
            if (s == 0) {
                cout << blue << setw(10) << cnt << green << ": " << reset << data << endl;
            } else {
                cout << data << endl;
            }
        }
    }
    file.close();
    return(0);
}