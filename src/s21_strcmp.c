#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
    int result = 0;
    for (int i = 0; str1[i] != 0 || str2[i] != 0; i++) {
        if (str1[i] != str2[i]) {
            result = str1[i] - str2[i];
            break;
        }
    }
    return result;
}
