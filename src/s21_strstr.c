#include "s21_string.h"

char *s21_strstr(char *string, char *substring) {
    char *a, *b, *p = S21_NULL;
    int flag = 0;

    b = substring;
    if (*b == 0) {
        p = string;
    }
    for (; *string != 0; string += 1) {
        if (*string != *b) {
            continue;
        }
        a = string;
        while (1) {
            if (*b == 0) {
                p = string;
                flag = 1;
                break;
            }
            if (*a++ != *b++) {
                break;
            }
        }
        if (flag) {
            break;
        }
        b = substring;
    }
    return p;
}
