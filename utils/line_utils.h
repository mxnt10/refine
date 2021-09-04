#ifndef REF_LINE_UTILS_H
#define REF_LINE_UTILS_H

#define RED "\x1B[31m"
#define BLUE "\x1B[34m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

int view_lines( bool s, bool c, char p, char *f, long int x, unsigned long int y );

#endif //REF_LINE_UTILS_H
