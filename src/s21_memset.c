#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char char_to_set = (unsigned char)c;
    unsigned char *str_ptr = (unsigned char *)str;

    for (s21_size_t i = 0; i < n; i++) {
        str_ptr[i] = char_to_set;
    }

    return str;
}
