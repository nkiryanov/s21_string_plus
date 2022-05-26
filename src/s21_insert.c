#include "s21_string.h"
#include <stdlib.h>

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
/*
Возвращает новую строку, в которой указанная строка (str)
вставлена в указанную позицию (start_index) в данной строке (src).
В случае какой-либо ошибки возвращает значение S21_NULL
*/
    char* fin;
    s21_size_t src_lenght, str_lenght;
    if (src != S21_NULL) {
        src_lenght = s21_strlen(src);
    } else {
       src_lenght = 0;
    }
    if (str != S21_NULL) {
        str_lenght = s21_strlen(str);
    } else {
        str_lenght = 0;
    }
    s21_size_t fin_lenght = src_lenght + str_lenght;
    fin = (char*)calloc(src_lenght+str_lenght+1, sizeof(char));
    if (start_index <= src_lenght && fin != S21_NULL) {
        for (s21_size_t i = 0; i < fin_lenght; i++) {
            if (i < start_index) {
                fin[i] = src[i];
            } else if (i < str_lenght+start_index) {
                fin[i] = str[i-start_index];
            } else {
                fin[i] = src[i-str_lenght];
            }
        }
    } else {
        fin = S21_NULL;
    }
    return fin;
}
