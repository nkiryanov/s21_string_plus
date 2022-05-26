#include <math.h>

#include "s21_string.h"

int s21_dtoa(char *dest, double long number, int precision,
             int radix_required) {
    // Double to string conversion. `dest` should be large enough.
    // The algorithm is trivial. It will not work with numbers that couldnt
    // be fit in long long integers.
    //
    // Params:
    // - precision. The precision of the number. If precision is 0 the radix
    // characters may be removed (it controls `truncate_radix` param)
    // - radix_required. Make sense only when precision is 0. If it's value is
    // FALSE and precision is 0 then radix character will be removed.
    unsigned long long discrete_part;
    char *dest_start = dest;

    if (number < 0) {
        number = -number;
        *dest++ = '-';
    }

    // Rounding up
    number += 55 * pow(10, -(precision + 2));

    // Get and write to destination. Move carrige to the end.
    discrete_part = (unsigned long long)number;
    number -= discrete_part;
    dest += s21_uitoa(dest, discrete_part, 10);

    // Write delimeter if precision > 0 and truncate_radix is FALSE
    if (precision > 0 || radix_required == TRUE) {
        *dest++ = '.';
        *dest = '\0';
    }

    // Get and write fraction part step by step.
    for (int i = precision; i > 0; i--) {
        number *= 10;
        discrete_part = (unsigned long long)number;
        number -= discrete_part;
        dest += s21_uitoa(dest, discrete_part, 10);
    }

    return dest - dest_start;
}
