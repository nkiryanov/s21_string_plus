#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    /*
    Копирует до n символов из строки, на которую указывает src, в dest.
    */
    s21_size_t size = s21_strnlen(src, n);
    if (size != n) s21_memset(dest + size, '\0', n - size);
    return s21_memcpy(dest, src, size);
}
