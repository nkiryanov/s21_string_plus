#include <stdarg.h>

#include "./s21_sprintf_utils/s21_sprintf_utils.h"
#include "s21_string.h"

int s21_sprintf(char *dest, const char *format, ...) {
    char *dest_start = dest;
    va_list args;

    va_start(args, format);

    while (*format) {
        specifier_t spec = SPECIFIER_DEFAULTS;

        if (*format != '%') {
            *dest++ = *format++;
            continue;
        }

        format += _parse_format(format, &spec, &args);
        switch (spec.conversion) {
            case 'c':
                dest += _char_handler(dest, &spec, &args);
                break;
            case 's':
                dest += _string_handler(dest, &spec, &args);
                break;
            case 'p':
                dest += _pointer_handler(dest, &spec, &args);
                break;
            case 'n':
                _bytes_proceeded_handler(dest - dest_start, &args);
                break;
            case 'd':
            case 'i':
            case 'u':
            case 'o':
            case 'x':
            case 'X':
                dest += _integer_handler(dest, &spec, &args);
                break;
            case 'f':
            case 'e':
            case 'E':
            case 'g':
            case 'G':
                dest += _float_handler(dest, &spec, &args);
                break;
            case '%':
            default:
                *dest = '%';
                *++dest = '\0';
                break;
        }
    }

    va_end(args);
    *dest = '\0';

    return dest - dest_start;
}
