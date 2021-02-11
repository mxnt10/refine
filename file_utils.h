//
// Created by mauricio on 07/02/2021.
//

#ifndef READTO_FILE_UTILS_H
#define READTO_FILE_UTILS_H

#endif //READTO_FILE_UTILS_H

#include <fstream>

using namespace std;

int count_lines(char *x) {
    int lines = 0;
    string data;
    ifstream file(x);
    while (!file.fail()) {
        getline(file, data);
        lines++;
    }
    file.close();
    return(lines);
}

int check_files(char *x) {
    ifstream file(x);
    if (! file) {
        file.close();
        return(1);
    } else {
        file.close();
        return(0);
    }
}

