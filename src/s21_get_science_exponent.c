#include <math.h>
#include <stdio.h>

#include "s21_string.h"

int s21_get_science_exponent(long double ld_number) {
    // Get exponent that is required for float numbers science notation
    // representation.
    int exponent = 0;
    int is_normal;

    is_normal = isnormal(ld_number);

    if (is_normal && ld_number != 0.0 && ld_number > 10) {
        while (ld_number / pow(10, ++exponent) > 10) {
        }
    }
    if (is_normal && ld_number != 0.0 && ld_number < 1) {
        while (ld_number / pow(10, --exponent) < 1) {
        }
    }

    return exponent;
}
