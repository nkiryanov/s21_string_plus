#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    /*
    Возвращает новую строку, в которой указанная строка (str)
    вставлена в указанную позицию (start_index) в данной строке (src).
    В случае какой-либо ошибки возвращает значение S21_NULL
    */
    char *fin = S21_NULL;
    s21_size_t src_length, str_length;
    src_length = (src == S21_NULL) ? 0 : s21_strlen(src);
    str_length = (str == S21_NULL) ? 0 : s21_strlen(str);

    s21_size_t fin_length = src_length + str_length;
    if (start_index <= src_length) {
        fin = (char *)calloc(src_length + str_length + 1, sizeof(char));
    }

    if (fin != S21_NULL) {
        for (s21_size_t i = 0; i < fin_length; i++) {
            if (i < start_index) {
                fin[i] = src[i];
            } else if (i < str_length + start_index) {
                fin[i] = str[i - start_index];
            } else {
                fin[i] = src[i - str_length];
            }
        }
    }

    return fin;
}
