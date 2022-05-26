#include "s21_string.h"

int s21_itoa(char *dest, long number, const unsigned int radix) {
    // Copy int number to dest as string representation.
    // Radix should be 2, 8, 10, 16 only
    int bytes_proceeded, sign;
    unsigned long u_number;

    // Save sign if number is negative.
    // Negative value may be INT_MIN. Unsigned int should be used to deal that.
    s21_long_to_unsigned(number, &u_number, &sign);
    if (sign < 0) *dest++ = '-';

    bytes_proceeded = s21_uitoa(dest, u_number, radix);
    return (sign < 0) ? bytes_proceeded + 1 : bytes_proceeded;
}
