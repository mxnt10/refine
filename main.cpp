
/**     "refine v1.0" - Reads specific lines of text documents.     **
 **     By Mauricio Ferrari - Date: 2021/02/07.                     **/

#include <stdexcept>
#include <iostream>
#include <string>
#include "file_utils.h"

using namespace std;

/** Help function. **/

int view_help(char *i) {
    cout << "refine v1.0 - Reads specific lines of text documents." << endl;
    cout << "\nSyntax: " << i << " [options] file.txt" << endl;
    cout << "\nParameters:" << endl;
    cout << "\t-f: To read the first lines of the files." << endl;
    cout << "\t-f0: To read the first lines of the files without numbering." << endl;
    cout << "\t-l: To read the last lines of the files." << endl;
    cout << "\t-l0: To read the last lines of the files without numbering." << endl;
    cout << "\t-a: To read a line from a file." << endl;
    cout << "\t-a0: To read a line from a file without numbering." << endl;
    cout << "\t-d: To read the specific lines of the files. Defines start of the line. " << endl;
    cout << "\t-d0: To read the specific lines of the files without numbering. " << endl;
    cout << "\t-s: To read the specific lines of the files. Use with -d. Defines end of the line." << endl;
    cout << "\t-h: To view help information." << endl;
    return(0);
}

/** To read the first lines of the files. **/

int first_lines(int d, int x, char *y) {
    int cnt = 0;
    string data;
    cout << endl;
    if (d == 0) {
        cout << y << ":" << endl;
    }
    ifstream file(y);
    while (!file.fail()) {
        cnt++;
        getline(file, data);
        if ( cnt <= x) {
            if (d == 0) {
                cout << "\t" << cnt << ": " << data << endl;
            } else {
                cout << data << endl;
            }
        }
    }
    file.close();
    return(0);
}

/** To read the last lines of the files. **/

int last_lines(int d, int x, char *y) {
    int lines = count_lines(y);
    int cnt = 0;
    string data;
    cout << endl;
    if (d == 0) {
        cout << y << ":" << endl;
    }
    ifstream file(y);
    while (!file.fail()) {
        cnt++;
        getline(file, data);
        if ( cnt >= (lines - x)) {
            if (d == 0) {
                cout << "\t" << cnt << ": " << data << endl;
            } else {
                cout << data << endl;
            }
        }
    }
    file.close();
    return(0);
}

/** To read the specific lines of the files. **/

int delimit_lines(int d, int x, int y, char *z) {
    int cnt = 0;
    string data;
    cout << endl;
    if (d == 0) {
        cout << z << ":" << endl;
    }
    ifstream file(z);
    while (!file.fail()) {
        cnt++;
        getline(file, data);
        if ( cnt >= x && cnt <= y) {
            if (d == 0) {
                cout << "\t" << cnt << ": " << data << endl;
            } else {
                cout << data << endl;
            }
        }
    }
    file.close();
    return(0);
}

int a_line(int d, int x, char *y){
    int cnt = 0;
    string data;
    if (d == 0) {
        cout << endl << y << ":" << endl;
    }
    ifstream file(y);
    while (!file.fail()) {
        cnt++;
        getline(file, data);
        if ( cnt == x) {
            if (d == 0) {
                cout << "\t" << data << endl;
            } else {
                cout << data << endl;
            }
        }
    }
    file.close();
    return(0);
}

/** Main Function **/

int main(int argc, char * *argv) {
    int f, g;
    int c = 0, ctl = 0;
    int p1, p2 = 0;
    int sel1, sel2, dis = 0;
    string param;

    for (f = 0; f < argc; f++) {
        if (f == 1) {
            param = argv[f];
            if (param == "-f" || param == "-f0") {
                sel1 = 1;
                if (param == "-f0" ) {
                    dis = 1;
                }
            } else if (param == "-l" || param == "-l0") {
                sel1 = 2;
                if (param == "-l0" ) {
                    dis = 1;
                }
            } else if (param == "-a" || param == "-a0") {
                sel1 = 3;
                if (param == "-a0" ) {
                    dis = 1;
                }
            }else if (param == "-d" || param == "-d0") {
                sel1 = 4;
                if (param == "-d0" ) {
                    dis = 1;
                }
            }else if (param == "-h") {
                view_help(argv[0]);
                exit(0);
            } else {
                cout << "Invalid Parameter: " << param << "!" << endl;
                exit(1);
            }
            ctl++;
            c++;
        }
        if (f == 2 || f == 4 && param == "-s") {
            try {
                param = argv[f];
                if (sel2 == 1) {
                    p2 = stoi(param, nullptr, 0);
                    ctl++;
                } else {
                    p1 = stoi(param, nullptr, 0);
                }
            }
            catch (const invalid_argument& ia) {
                cerr << "Invalid argument: " << ia.what() << ": " << param << " not a number!" << endl;
                exit(1);
            }
            ctl++;
            c++;
        }
        if (f == 3) {
            param = argv[f];
            if (sel1 == 4) {
                if (param == "-s") {
                    sel2 = 1;
                } else {
                    cout << "Use -s as Parameter, you used: " << param << "!" << endl;
                    exit(1);
                }
            }
            ctl++;
            c++;
        }
        if (f > 4) {
            c++;
        }
    }

    /** View info case not there arguments. **/

    if (c == 0) {
        view_help(argv[0]);
        exit(0);
    }

    /** Error control. **/

    if (c < 2) {
        cout << "Value not specified for " << argv[1] << "!" << endl;
        exit(1);
    }
    if (c < 3 && sel1 < 3 || sel2 == 1 && p2 != 0 && c < 5) {
        cout << "No text file specified!" << endl;
        exit(1);
    }
    if (sel1 == 3 && c == 2) {
        cout << "Parameter -s not specified for -d!" << endl;
        exit(1);
    }
    if (sel2 == 1 && c < 4) {
        cout << "Value not specified for -s!" << endl;
        exit(1);
    }

    /** Multiple files support **/

    for (g = ctl; g < f; g++) {
        int check = check_files(argv[g]);
        if (check == 1) {
            cout << endl << argv[g] << ": file not exist!" << endl;
        } else {
            switch (sel1) {
                case 1: /** View first lines. **/
                    first_lines(dis, p1, argv[g]);
                    break;
                case 2: /** View last lines. **/
                    last_lines(dis, p1, argv[g]);
                    break;
                case 3: /** View a line. **/
                    a_line(dis, p1, argv[g]);
                    break;
                case 4: /** View specific lines. **/
                    delimit_lines(dis, p1, p2, argv[g]);
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
