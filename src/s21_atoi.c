#include "s21_string.h"

int s21_atoi(char *str) {
    int sign;
    int number = 0;
    char digit;

    sign = (*str == '-') ? -1 : 1;
    if (*str == '-' || *str == '+') str++;

    while (s21_isdigit(digit = *str++)) {
        number = number * 10 + digit - '0';
    }

    number *= sign;
    return number;
}
