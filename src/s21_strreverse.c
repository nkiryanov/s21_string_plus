#include "string.h"

char *s21_strreverse(char* str) {
    // Reverse string in place. Also returns ptr to the same string.
    char *start, *end;

    start = str;
    end = str + strlen(str) - 1;

    while (start < end) {
        char tmp_chr = *end;
        *end-- = *start;
        *start++ = tmp_chr;
    }

    return str;
}
