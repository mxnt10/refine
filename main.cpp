/**     "refine v3.0" - Reads specific lines of text documents.     **
 **     By Mauricio Ferrari - Date Creation: 2021/02/07.            **
 **                         - Last Update:   2021/09/04.            **/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

#include <getopt.h> /** Include C Library. **/

#include "utils/control_utils.h"
#include "utils/err_msg.h"
#include "utils/file_utils.h"
#include "utils/line_utils.h"
#include "utils/parm.h"
#include "main.h"

using namespace std;

/** Help function. **/

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

void help( char *x ) {
    cout << "refine v3.0 - Reads specific lines of text documents." << endl;
    cout << "\nSyntax: " << x << " [options] text_file" << endl;
    cout << "\nParameters:" << endl;
    cout << "\t-f: To read the first lines of the files." << endl;
    cout << "\t-l: To read the last lines of the files." << endl;
    cout << "\t-d: To read the specific lines of the files." << endl;
    cout << "\t-i: To read inverted the specific lines of the files." << endl;
    cout << "\t-h: To view help information." << endl;
    cout << "\nOptionals:" << endl;
    cout << "\t-c: Enable color for f, l, d and i parameters." << endl;
    cout << "\t-s: Simple visualization for f, l, d and i parameters." << endl;
    exit(0);
}

#pragma clang diagnostic pop

/** Main function. **/

int main( int argc, char **argv ) {

    char *ref_file = basename(argv[0]);
    if ( argc == 1 ) help(ref_file);

    int opt, i;
    int first_line = default_view;
    int last_line = default_view;

    long int delimit_f;
    unsigned long int delimit_l = nullarg;

    char *first_parm = nullptr;
    char *last_parm = nullptr;
    char *delimit_line = nullptr;
    char *invert_line = nullptr;

    char *recover_arg = nullptr;
    char *file;

    bool set_first = false;
    bool set_last = false;
    bool set_delimit = false;
    bool set_invert = false;
    bool set_color = false;
    bool set_simple = false;
    bool discount_arg = false;

    /** Struct for parameters. **/

    const struct option parm[] = {
            {"first",   optional_argument, null_p, parm_f},
            {"last",    optional_argument, null_p, parm_l},
            {"delimit", required_argument, null_p, parm_d},
            {"invert",  required_argument, null_p, parm_i},
            {"color",   no_argument,       null_p, parm_c},
            {"simple",  no_argument,       null_p, parm_s},
            {"help",    no_argument,       null_p, parm_h},
            {null_p,    no_argument,       null_p, null_p},
    };

    /** Parameters selection. **/

    while ( (opt = getopt_long(argc, argv, "f::l::d:i:csh", parm, nullptr)) > 0 ) {

        /** Control for optional parameters. **/

        if ( !optarg
            && optind < argc
            && nullptr != argv[optind]
            && '\0' != argv[optind][0]
            && '-' != argv[optind][0] ) optarg = argv[optind++];

        switch ( opt ) {

            case 'f': /** Option -f or --first **/

                if ( set_first
                    || set_last
                    || set_delimit
                    || set_invert ) err_parm(ref_file, set_first, parm_f, msg_err_first);

                if ( optarg != nullptr ) {
                    if ( number_validate(optarg) == 0 ) first_line = stoi(optarg, nullptr, 0);
                    else {
                        discount_arg = true;
                        first_parm = optarg;
                    }
                }

                set_first = true;
                break;

            case 'l': /** Option -l or --last **/

                if ( set_first
                    || set_last
                    || set_delimit
                    || set_invert ) err_parm(ref_file, set_last, parm_l, msg_err_last);

                if ( optarg != nullptr ) {
                    if ( number_validate(optarg) == 0 ) last_line = stoi(optarg, nullptr, 0);
                    else {
                        discount_arg = true;
                        last_parm = optarg;
                    }
                }

                set_last = true;
                break;

            case 'd': /** Option -d or --delimit **/

                if ( set_first
                    || set_last
                    || set_delimit
                    || set_invert ) err_parm(ref_file, set_delimit, parm_d, msg_err_delimit);

                delimit_line = optarg;
                set_delimit = true;
                discount_arg = false;
                break;

            case 'i': /** Option -i or --invert **/

                if ( set_first
                    || set_last
                    || set_delimit
                    || set_invert ) err_parm(ref_file, set_invert, parm_i, msg_err_invert);

                invert_line = optarg;
                set_invert = true;
                discount_arg = false;
                break;

            case 'c': /** Option -c or --color **/

                if ( set_color ) err_parm(ref_file, set_color, parm_c, nullptr);

                set_color = true;
                discount_arg = true;
                break;

            case 's': /** Option -s or --simple **/

                if ( set_simple ) err_parm(ref_file, set_color, parm_s, nullptr);

                set_simple = true;
                discount_arg = true;
                break;

            case 'h': /** Option -h or --help **/
                help(ref_file);
                break;

            default:
                cerr << ref_file << ": Invalid option or argument not found." << endl;
                exit(1);
        }
    }

    /** Additional error control for -c and -s. **/

    if ( set_color ) {
        if ( !set_first
            && !set_last
            && !set_delimit
            && !set_invert ) err_parm(ref_file, false, parm_c, msg_err_color);
    }

    if ( set_simple ) {
        if ( !set_first
            && !set_last
            && !set_delimit
            && !set_invert ) err_parm(ref_file, false, parm_s, msg_err_simple);
    }

    /** Additional controls. **/

    if ( strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-s") == 0 ) err_cs_first(ref_file);
    if ( set_color && set_simple ) err_cs(ref_file);
    if ( optind == 1 || argc < 3 ) help(ref_file);

    /** Select delimitation for -f and -l parameters. **/

    if ( set_delimit || set_invert ) {
        int delimit = 0;
        char *test, *option_parm;
        string token;

        if ( set_delimit ) option_parm = delimit_line;
        else option_parm = invert_line;

        if ( check_delimit(option_parm) == 0 ) {
            vector<string> tokens;
            istringstream tokenizer{option_parm};
            while ( getline(tokenizer, token, '-')) tokens.push_back(token);

            for ( const string &data: tokens ) {
                copy(data.begin(), data.end(), token.begin());
                test = &token[0];
                if ( number_validate(test) == 0 ) {
                    if ( delimit == 0 ) delimit_f = stoi(data, nullptr, 0);
                    if ( delimit == 1 ) delimit_l = stoi(data, nullptr, 0);
                } else err_num(ref_file, option_parm, 1);
                delimit++;
            }

        } else {
            if ( number_validate(option_parm) == 0 ) delimit_f = stoi(option_parm, nullptr, 0);
            else err_num(ref_file, option_parm, 0);
        }
    }

    int res = optind;
    if ( discount_arg ) res--;

    /** Error control for -c parameters in the end and for -f/-l parameters without arguments. **/

    for ( i = res; argv[i] != nullptr; i++ ) {
        if ( strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-s") == 0 ) {
            res++;
            if ( first_parm != nullptr ) recover_arg = first_parm;
            if ( last_parm != nullptr ) recover_arg = last_parm;
        }
    }

    /** Control for optional parameters for -f and -l. **/

    if ( recover_arg != nullptr ) {
        if ( check_files(recover_arg) == 1 ) err_file(ref_file, recover_arg);
        file = realpath(recover_arg, nullptr);
        if ( set_first ) view_lines(set_simple, set_color, parm_f, file, first_line, nullarg);
        if ( set_last ) view_lines(set_simple, set_color, parm_l, file, last_line, nullarg);
    }

    /** Control for entry files. **/

    for ( i = res; argv[i] != nullptr; i++ ) {
        if ( check_files(argv[i]) == 1 ) err_file(ref_file, argv[i]);
        file = realpath(argv[i], nullptr);
        if ( set_first ) view_lines(set_simple, set_color, parm_f, file, first_line, nullarg);
        if ( set_last ) view_lines(set_simple, set_color, parm_l, file, last_line, nullarg);
        if ( set_delimit ) view_lines(set_simple, set_color, parm_d, file, delimit_f, delimit_l);
        if ( set_invert ) view_lines(set_simple, set_color, parm_i, file, delimit_f, delimit_l);
    }
    return 0;
}
