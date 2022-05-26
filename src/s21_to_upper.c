#include "s21_string.h"
#include <stdlib.h>

void *s21_to_upper(const char* str1) {
    /*
    Возвращает копию строки (str), преобразованной в верхний регистр.
    В случае какой-либо ошибки возвращает значение S21_NULL.
    */
    s21_size_t size = s21_strlen(str1);
    char* fin = (char*)calloc(size+1, sizeof(char));
    if (fin != S21_NULL) {
        for (s21_size_t i = 0; str1[i] != 0; i++) {
            if (str1[i] >= 'a' && str1[i] <= 'z') {
                fin[i] = str1[i]-('a'-'A');
            } else {
                fin[i] = str1[i];
            }
        }
    }
    return fin;
}
