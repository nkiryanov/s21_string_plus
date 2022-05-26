#include "../s21_string.h"
#include "s21_sprintf_utils.h"

s21_size_t _parse_format(const char *format, specifier_t *spec_ptr,
                         va_list *args_ptr) {
    // Parse format string save result in spec_ptr structure. Return number of
    // proceeded bytes.
    const char *format_start = format;

    format += _get_flags(format, spec_ptr);
    format += _get_width_precision(format, &(spec_ptr->width), args_ptr);
    if (*format == '.') {
        format++;
        format +=
            _get_width_precision(format, &(spec_ptr->precision), args_ptr);
    }
    format += _get_length_modifier(format, spec_ptr);
    format += _get_conversion_specifier(format, spec_ptr);

    _turn_off_incompatible_flags(spec_ptr);

    return format - format_start;
}

int _get_flags(const char *format, specifier_t *spec_ptr) {
    // Get flags from format string and set them on spec_ptr
    int possible_flag_in_format = TRUE;
    const char *format_start = format;

    // Read format flags.
    while (possible_flag_in_format) {
        switch (*++format) {
            case '-':
                spec_ptr->adjustment = LeftJustified;
                break;
            case '+':
                spec_ptr->sign_flag = '+';
                break;
            case ' ':
                spec_ptr->sign_flag = MAX(spec_ptr->sign_flag, ' ');
                break;
            case '#':
                spec_ptr->hash_flag = TRUE;
                break;
            case '0':
                spec_ptr->adjustment =
                    MAX(spec_ptr->adjustment, ZeroRightJustified);
                break;
            default:
                // If flag was not found = not any more flag could be used for
                // the specifier.
                possible_flag_in_format = FALSE;
                break;
        }
    }

    // Return number of proceeded chars in format string to move pointer
    return format - format_start;
}

int _get_width_precision(const char *format, int *num_ptr, va_list *args_ptr) {
    // Get number from format string or read it form `args`. Returns the
    // number of proceeded chars.
    int number = 0;
    const char *format_start = format;

    while (s21_isdigit(*format)) {
        number = number * 10 + *format - '0';
        format++;
    }
    if (*format == '*') {
        number = va_arg(*args_ptr, int);
        format++;
    }

    *num_ptr = number;
    return format - format_start;
}

int _get_length_modifier(const char *format, specifier_t *spec_ptr) {
    // Get length modifier. Returns int (0 or 1) as indicator whether
    // modifier was found;
    int is_modifier_found = TRUE;

    switch (*format++) {
        case 'h':
            spec_ptr->modifier = hModifier;
            break;
        case 'l':
            spec_ptr->modifier = lModifier;
            break;
        case 'L':
            spec_ptr->modifier = LModifier;
            break;
        default:
            is_modifier_found = FALSE;
            break;
    }

    return is_modifier_found;
}

int _get_conversion_specifier(const char *format, specifier_t *spec_ptr) {
    // Get conversion value. The specifier will be read if it is found in
    // string of allowed specifiers.
    int is_spec_found = FALSE;
    char conversion_specifier = *format;

    if (is_spec_found || s21_strchr("diuoxXfeEgGcspn%", conversion_specifier)) {
        spec_ptr->conversion = conversion_specifier;
        is_spec_found = TRUE;
    }

    return is_spec_found;
}

void _turn_off_incompatible_flags(specifier_t *spec_ptr) {
    // For int specifiers: leading zero is not compatible with precision. Turn
    // it off.
    if (s21_strchr("diuoxX", spec_ptr->conversion) &&
        spec_ptr->adjustment == ZeroRightJustified &&
        spec_ptr->precision != NOT_SET) {
        spec_ptr->adjustment = RightJustified;
    }

    // For unsigned specifiers: space or sign flags are undefined. Turn them
    // off.
    if (s21_strchr("uoxX", spec_ptr->conversion)) {
        spec_ptr->sign_flag = '\0';
    }
}
