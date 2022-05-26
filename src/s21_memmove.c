#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    // Функция для копирования n символов из str в dest.
    // Работает в том числе для пересекающихся отрезков, когда с memcpy могут
    // быть коллизии. За реализацию взята основа muslc.
    unsigned char *dest_ptr = (unsigned char *)dest;
    const unsigned char *src_ptr = (const unsigned char *)src;
    int is_moved = 0;

    // If src and destination the same we have nothing to do
    if (dest_ptr == src_ptr) {
        is_moved = 1;
    }

    // Case 1:
    //      ...dest.....src......   <- copy from left to right
    //      ...src....n..dest....   <- copy from left to right
    // Case 2:
    //      ...src...dest..n.....   <- src overlap dest. Copy right to left
    if (!is_moved) {
        if (dest_ptr < src_ptr || dest_ptr > src_ptr + n - 1) {
            for (; n; n--) *dest_ptr++ = *src_ptr++;
        } else {
            while (n) n--, *(dest_ptr + n) = *(src_ptr + n);
        }
    }

    return dest;
}
