#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    // Сравнивает первые n байтов str1 и str2.
    const unsigned char *str1_ptr = (const unsigned char *)str1;
    const unsigned char *str2_ptr = (const unsigned char *)str2;
    int result = 0;

    while (n > 0 && (result = *str1_ptr - *str2_ptr) == 0) {
        ++str1_ptr;
        ++str2_ptr;
        --n;
    }

    return result;
}
