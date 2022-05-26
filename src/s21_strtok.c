#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
    // Разбивает строку str на ряд токенов, разделенных delim.
    static char *save_ptr = S21_NULL;

    // printf("begin_save_ptr=%p\n", save_ptr);
    // If str is S21_NULL start with save_ptr
    if (S21_NULL == str) str = save_ptr;

    // Trim trailing delimiters
    while (str && *str && s21_strchr(delim, *str)) {
        str++;
    }

    // If end of string reached
    if (str && *str == '\0') {
        str = S21_NULL;
        save_ptr = S21_NULL;
    }

    // Set new `save_ptr` if delimeter is found and it's not end of the string
    if (str && *str != '\0') {
        save_ptr = str;
        while (*save_ptr && !(s21_strchr(delim, *save_ptr))) {
            save_ptr++;
        }
    }

    // Terminate string and make `*save_ptr` point past it if end is not reached
    if (save_ptr && *save_ptr) {
        *save_ptr = '\0';
        save_ptr++;
    }

    // Set `save_ptr` to S21_NULL if end of string reached
    if (save_ptr && *save_ptr == '\0') {
        save_ptr = S21_NULL;
    }

    return str;
}
