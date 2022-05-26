#include "s21_string.h"

int s21_uitoa(char* dest, unsigned long long u_number,
              const unsigned int radix) {
    // Copy unsigned long long number to dest as string representation.
    // Radix should be 2, 8, 10, 16 only

    int i;
    char tmp[LL_MAX_WIDTH];

    // Copy all digits in tmp array as chars in reversed order
    i = 0;
    do {
        tmp[i] = (u_number % radix) + '0';
        if (radix == 16 && tmp[i] >= ':') tmp[i] += 'a' - ':';
        i++;
    } while (u_number /= radix);

    // Copy all the digits-char in resulted string
    for (int j = i - 1; j >= 0; j--) {
        *dest++ = tmp[j];
    }

    *dest = '\0';

    // Return length of the string.
    return i;
}
