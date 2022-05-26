#include "s21_string.h"

void s21_long_to_unsigned(long number, unsigned long *u_number_ptr, int *sign_ptr) {
    // Get long number and write it's abs in u_number and set sign 1 or -1

    *sign_ptr = (number < 0) ? -1 : 1;
    if (*sign_ptr < 0) {
        number++;
        *u_number_ptr = (unsigned long)(-number);
        (*u_number_ptr)++;
    } else {
        *u_number_ptr = (unsigned long)number;
    }
}
