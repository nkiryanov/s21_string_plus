#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    // Вычисляет длину начального сегмента str1, который полностью состоит из
    // символов, не входящих в str2.
    s21_size_t i, len = s21_strlen(str1);
    for (i = 0; i < len; i++) {
        if (s21_strchr(str2, str1[i]) != S21_NULL) {
            break;
        }
    }
    return i;
}
