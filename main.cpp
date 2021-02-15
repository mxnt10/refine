
/**     "refine v2.0" - Reads specific lines of text documents.     **
 **     By Mauricio Ferrari - Date Creation: 2021/02/07.            **
 **                         - Last Update:   2021/02/14.            **/

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include "utils/control_utils.h"
#include "utils/line_utils.h"

using namespace std;

/** Help function. **/

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

void view_help() {
    cout << "refine v2.0 - Reads specific lines of text documents." << endl;
    cout << "\nSyntax: refine [options] file.txt" << endl;
    cout << "\nParameters:" << endl;
    cout << "\t-f: To read the first lines of the files." << endl;
    cout << "\t-l: To read the last lines of the files." << endl;
    cout << "\t-d: To read the specific lines of the files." << endl;
    cout << "\t-i: To read inverted the specific lines of the files." << endl;
    cout << "\t-h: To view help information." << endl;
    cout << "\nOptionals:" << endl;
    cout << "\t c: Enable color for f, l, d and i parameters." << endl;
    cout << "\t 0: Simple visualization for f, l, d and i parameters." << endl;
    exit(0);
}
#pragma clang diagnostic pop

/** Main Function **/

int main(int argc, char * *argv) {
    int select = 0, simple = 0, color = 0;
    int param_number1, param_number2, param_file;
    int arg_number, char_number;
    int delimit = 0, control = 0;
    char character;
    string param;

    for (arg_number = 1; arg_number < argc; arg_number++) {
        if (arg_number == 1) {
            param = argv[arg_number];
            for (char_number = 0; char_number < strlen(argv[arg_number]); char_number++) {
                character = param[char_number];

                /** Select Parameters. **/

                switch (character) {
                    case 'f':
                        if (select != 0) {
                            cout << R"(Parameter "f" cannot be used with "l", "d" and "i"!)" << endl;
                            exit(1);
                        } else {
                            select = 1;
                        }
                        break;
                    case 'l':
                        if (select != 0) {
                            cout << R"(Parameter "l" cannot be used with "f", "d" and "i"!)" << endl;
                            exit(1);
                        } else {
                            select = 2;
                        }
                        break;
                    case 'd':
                        if (select != 0) {
                            cout << R"(Parameter "d" cannot be used with "f", "l" and "i"!)" << endl;
                            exit(1);
                        } else {
                            select = 3;
                        }
                        break;
                    case 'i':
                        if (select != 0) {
                            cout << R"(Parameter "d" cannot be used with "f", "l" and "d"!)" << endl;
                            exit(1);
                        } else {
                            select = 4;
                        }
                        break;
                    case 'c':
                        if (select != 0) {
                            color = 1;
                        } else {
                            cout << R"(Parameter "c" must be used with "f", "l", "d" or "i"!)" << endl;
                            exit(1);
                        }
                        break;
                    case '0':
                        if (select != 0) {
                            simple = 1;
                        } else {
                            cout << R"(Parameter "0" must be used with "f", "l", "d" or "i"!)" << endl;
                            exit(1);
                        }
                        break;
                    case 'h':
                        if (select == 0) {
                            view_help();
                        } else {
                            cout << R"(Parameter "h" cannot be used with other arguments!)" << endl;
                            exit(1);
                        }
                        break;
                    case '-':
                        break;
                    default:
                        cerr << "Invalid Parameter: " << character << "!" << endl;
                        exit(1);
                }
            }
        }

        /** Select Delimitation **/

        if (arg_number == 2) {
            int validate;
            char *test;
            string token;
            int check_param = check_delimit(argv[arg_number]);
            param = argv[arg_number];
            if (select == 3 && check_param == 0 || select == 4 && check_param == 0) {
                vector<string> tokens;
                istringstream tokenizer { param };
                while (getline(tokenizer, token, '-')) {
                    tokens.push_back(token);
                }
                for (const string &data: tokens){
                    copy(data.begin(),data.end(),token.begin());
                    test = &token[0];
                    validate = number_validate(test);
                    if (validate == 0) {
                        if (delimit == 0) {
                            param_number1 = stoi(data, nullptr, 0);
                        }
                        if (delimit == 1) {
                            param_number2 = stoi(data, nullptr, 0);
                        }
                    } else {
                        cerr << "Invalid argument: " << param << " not a correct delimiter!" << endl;
                        exit(1);
                    }
                    delimit++;
                }
            } else {
                validate = number_validate(argv[arg_number]);
                if (validate == 0) {
                    param_number1 = stoi(param, nullptr, 0);
                    param_number2 = 0;

                } else {
                    cerr << "Invalid argument: " << param << " not a number!" << endl;
                    exit(1);
                }
            }
        }
    control++;
    }

    /** View info case not there arguments. **/

    if (control == 0) {
        view_help();
    }

    /** Error control. **/

    if (control < 2) {
        cout << "Value not specified for " << argv[1] << "!" << endl;
        exit(1);
    }
    if (control < 3) {
        cout << "No text file specified!" << endl;
        exit(1);
    }

    /** Multiple files support **/

    for (param_file = 3; param_file < arg_number; param_file++) {
        int check_file = check_files(argv[param_file]);
        char *file = realpath(argv[param_file], nullptr);
        if (check_file == 1) {
            cout << endl << argv[param_file] << ": file not exist!" << endl;
        } else {
            switch (select) {
                case 1: /** View first lines. **/
                    first_lines(simple, color, param_number1, file);
                    break;
                case 2: /** View last lines. **/
                    last_lines(simple, color, param_number1, file);
                    break;
                case 3: /** View specific lines. **/
                    delimit_lines(simple, color, param_number1, param_number2, file);
                    break;
                case 4: /** Invert View specific lines. **/
                    invert_lines(simple, color, param_number1, param_number2, file);
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
