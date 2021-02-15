//
// Created by mauricio on 13/02/2021.
//

#ifndef REFINE_CONTROL_UTILS_H
#define REFINE_CONTROL_UTILS_H

#endif

#include <stdexcept>
#include <string>

using namespace std;

int number_validate(char *x) {
    try {
        int param_number;
        string check;
        param_number = stoi(x, nullptr, 0);
        check = to_string(param_number);
        if (check == x) {
            return (0);
        } else {
            return (1);
        }
    }
    catch (const invalid_argument& ia) {
        return(1);
    }
}

int check_delimit(char *x) {
    int compare, control = 0;
    char check;
    char character = '-';
    for (compare = 0; compare < strlen(x); compare++) {
        check = x[compare];
        if ( check == character) {
            control = 1;
        }
    }
    if (control == 1){
        return(0);
    } else {
        return(1);
    }
}