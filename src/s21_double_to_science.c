#include <math.h>

#include "s21_string.h"

s21_size_t s21_double_to_science(char *dest, long double number, int precision,
                                 int radix_required) {
    long double mantissa;
    char str_exponent[5] = "";
    char *dest_start = dest;
    int exponent, exponent_length = 0;

    if (number < 0) {
        number = -number;
        *dest++ = '-';
    }

    exponent = s21_get_science_exponent(number);
    mantissa = number / pow(10, exponent);

    dest += s21_dtoa(dest, mantissa, precision, radix_required);
    *dest++ = 'e';
    *dest++ = exponent < 0 ? '-' : '+';

    if (exponent < 0) exponent = -exponent;
    exponent_length = s21_uitoa(str_exponent, (unsigned long)exponent, 10);

    if (exponent_length < 2) *dest++ = '0', *dest = '\0';

    s21_strcat(dest, str_exponent);
    dest += exponent_length;

    return dest - dest_start;
}
