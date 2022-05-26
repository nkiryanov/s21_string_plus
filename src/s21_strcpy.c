#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
    /*
    Копирует строку, на которую указывает src, в dest.
    */
    return s21_memcpy(dest, src, s21_strlen(src) + 1);
}
