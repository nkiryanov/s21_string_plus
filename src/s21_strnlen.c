#include "s21_string.h"

s21_size_t s21_strnlen(const char *str, s21_size_t n) {
    s21_size_t i = 0;
    for (; i < n && str[i] != '\0'; i++) continue;
    return i;
}
