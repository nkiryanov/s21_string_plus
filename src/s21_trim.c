#include "s21_string.h"
#include <stdlib.h>

void *s21_trim(const char *src, const char *trim_chars) {
    /*
    Возвращает новую строку, в которой удаляются все начальные и
    конечные вхождения набора заданных символов (trim_chars) из данной строки (src).
    В случае какой-либо ошибки возвращает значение S21_NULL
    */
    s21_size_t status = 0, cut_up = 0, cut_dwn = 0, size_src, size_trim;
    if (src != S21_NULL) {
        size_src = s21_strlen(src);
    } else {
        size_src = 0;
    }
    /* Проверка на массив == S21_NULL, после этого проверка на пустой массив */
    if (trim_chars != S21_NULL) {
        if (trim_chars[0] != 0) {
            size_trim = s21_strlen(trim_chars);
        } else {
            status = 1;
            size_trim = 3;
        }
    } else {
        status = 1;
        size_trim = 3;
    }
    char* trim = calloc(size_trim, sizeof(char));
    if (status == 1) {
        trim[0] = ' ';
        trim[1] = '\t';
        trim[2] = '\n';
        trim[3] = 0;
    } else {
        for (s21_size_t i = 0; i <= size_trim; i++) {
            if (i < size_trim) {
                trim[i] = trim_chars[i];
            }
        }
    }
    for (s21_size_t i = size_src-1; i > 0; i--) {
        status = 0;
        for (s21_size_t y = 0; y < size_trim; y++) {
            if (trim[y] == src[i] && status == 0) {
                cut_up += 1;
                status = 1;
            }
        }
        if (status == 0) break;
    }
    for (s21_size_t i = 0; i < size_src-cut_up; i++) {
        status = 0;
        for (s21_size_t y = 0; y < size_trim; y++) {
            if (trim[y] == src[i] && status == 0) {
                cut_dwn += 1;
                status = 1;
            }
        }
        if (status == 0) break;
    }
    free(trim);
    status = 0;
    s21_size_t fin_size = size_src-cut_up-cut_dwn;
    if (fin_size == 0) {
        status = 1;
        fin_size = 1;
    }
    char a = '\0';
    char *fin = (char *)calloc(fin_size+1, sizeof(char));
    if (fin != S21_NULL) {
        if (size_src > 0 && status == 0) {
            for (s21_size_t i = cut_dwn; i < size_src-cut_up; i++) fin[i-cut_dwn] = src[i];
        } else {
            fin[0] = a;
        }
    }
    return fin;
}
