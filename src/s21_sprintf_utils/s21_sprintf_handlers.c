#include <math.h>

#include "../s21_string.h"
#include "s21_sprintf_utils.h"

s21_size_t _char_handler(char *dest, specifier_t *spec_ptr, va_list *args_ptr) {
    char one_char_array[2];
    representation_t repr = REPRESENTATION_DEFAULTS;
    repr.repr = one_char_array;

    if (spec_ptr->modifier == lModifier) {
        one_char_array[0] = (char)va_arg(*args_ptr, wchar_t);
    } else {
        one_char_array[0] = (char)va_arg(*args_ptr, int);
    }

    one_char_array[1] = '\0';

    if (spec_ptr->width > 0) repr.spaces = spec_ptr->width - 1;
    if (spec_ptr->adjustment == LeftJustified) repr.spaces = -repr.spaces;

    return _repr_to_destination(dest, &repr);
}

s21_size_t _string_handler(char *dest, specifier_t *spec_ptr,
                           va_list *args_ptr) {
    s21_size_t string_length = 0;
    s21_size_t bytes_proceeded;
    representation_t repr = REPRESENTATION_DEFAULTS;

    if (spec_ptr->modifier == lModifier) {
        const wchar_t *input_wchar;

        input_wchar = va_arg(*args_ptr, wchar_t *);
        string_length = _wstrlen(input_wchar);  // Get length of wchar string
        repr.repr = _calloc_str(string_length);

        // Convert wchar to char. According to task it's eligible operation.
        for (int i = 0; input_wchar[i]; i++) {
            repr.repr[i] = (char)input_wchar[i];
        }

    } else {
        const char *input_char;

        input_char = va_arg(*args_ptr, char *);
        string_length = s21_strlen(input_char);
        repr.repr = _calloc_str(string_length);

        s21_strcpy(repr.repr, input_char);
    }

    // Set precision if it set
    if (spec_ptr->precision > 0 &&
        (unsigned)spec_ptr->precision < string_length) {
        *(repr.repr + spec_ptr->precision) = '\0';
        string_length = spec_ptr->precision;
    }

    repr.spaces = spec_ptr->width - string_length;
    repr.spaces = (repr.spaces > 0) ? repr.spaces : 0;

    if (spec_ptr->adjustment == LeftJustified) repr.spaces = -repr.spaces;

    bytes_proceeded = _repr_to_destination(dest, &repr);

    if (repr.repr) {
        free(repr.repr);
    }

    return bytes_proceeded;
}

s21_size_t _float_handler(char *dest, specifier_t *spec_ptr,
                          va_list *args_ptr) {
    long double ld_number;
    int sign, num_length, prefix_length, bytes_proceeded;
    representation_t repr = REPRESENTATION_DEFAULTS;

    // Get value. It is stored in long double.
    switch (spec_ptr->modifier) {
        case LModifier:
            ld_number = va_arg(*args_ptr, long double);
            break;
        default:
            ld_number = (long double)va_arg(*args_ptr, double);
            break;
    }

    // Set sign representation
    sign = (signbit(ld_number) == 0) ? 1 : -1;
    _set_sign_representation(sign, spec_ptr, &repr);

    // Edge case. ld is inf
    if (isinf(ld_number)) {
        repr.repr = "inf";
        num_length = 3;
    }

    // Edge case. ld_number is nan
    if (isnan(ld_number)) {
        repr.repr = "nan";
        num_length = 3;
    }

    // Zero or normal number.
    if (isfinite(ld_number)) {
        if (ld_number < 0) {
            sign = -1;
            ld_number = -ld_number;
        }

        // Set precision if required
        if (spec_ptr->precision == 0 &&
            (spec_ptr->conversion == 'g' || spec_ptr->conversion == 'G')) {
            spec_ptr->precision = 1;
        }
        if (spec_ptr->precision == NOT_SET) spec_ptr->precision = 6;

        // Allocate memory for string representation
        // LL_MAX_WIDTH - max integer width (it's an assumption for the task)
        // 1 - the value for end of the string
        // spec_ptr->precision — possible precision
        // 3 - the precision of representation may be bigger for 3 for g G spec
        repr.repr = (char *)malloc(LL_MAX_WIDTH + 1 + spec_ptr->precision + 3);
        if (repr.repr == S21_NULL) {
            exit(1);
        }

        // Get the number representation
        switch (spec_ptr->conversion) {
            case 'f':
                num_length = s21_dtoa(repr.repr, ld_number, spec_ptr->precision,
                                      spec_ptr->hash_flag);
                break;
            case 'e':
            case 'E':
                num_length = s21_double_to_science(repr.repr, ld_number,
                                                   spec_ptr->precision,
                                                   spec_ptr->hash_flag);
                break;
            case 'g':
            case 'G':
            default:
                num_length =
                    _double_to_alter_science(repr.repr, ld_number, spec_ptr);
                break;
        }

        // ee and gg specifiers should use uppercase
        if (spec_ptr->conversion == 'E' || spec_ptr->conversion == 'G') {
            _str_to_uppercase(repr.repr);
        }
    }

    // Calculate width
    prefix_length = s21_strlen(repr.prefix);
    repr.spaces = spec_ptr->width - (num_length + prefix_length);
    if (repr.spaces < 0) repr.spaces = 0;

    // Set spaces, zeros representation. Only two cases because default values
    // are fit all other cases.
    if (spec_ptr->adjustment == ZeroRightJustified) {
        repr.zeros = repr.spaces;
        repr.spaces = 0;
    } else if (spec_ptr->adjustment == LeftJustified) {
        repr.spaces = -repr.spaces;
    }

    // Copy values to destination
    bytes_proceeded = _repr_to_destination(dest, &repr);

    if (isfinite(ld_number) && repr.repr) free(repr.repr);

    return bytes_proceeded;
}

s21_size_t _integer_handler(char *dest, specifier_t *spec_ptr,
                            va_list *args_ptr) {
    // Integer specifier to destination string.
    // Params:
    //  - precision. Minimum number of digits to appear. If the value can be
    //      represented in fewer digits, it would be expanded with leading
    //      zeros
    //  - width. Minimum width of the string. If converted number has fewer
    //      digits or symbols it will padded from the left with spaces.
    //  - leading-zero. If set 0 will be used for padding.
    //  - left-justified. The string will be padded form the right. Leading
    //      zero will be ignored.
    //  - sign. Could be `default`, `space` or `plus`.
    //      Default: nothing will be used for positive numbers.
    //      Space: trailing space for positive numbers
    //      Plus: trailing space for positive numbers.

    char num_str[LL_MAX_WIDTH];
    unsigned long u_number;
    int radix, sign, num_length, prefix_length;

    representation_t repr = REPRESENTATION_DEFAULTS;
    repr.repr = num_str;

    // Read argument according to modifier. Save sign and number separately
    switch (spec_ptr->conversion) {
        case 'u':
        case 'o':
        case 'x':
        case 'X':
            if (spec_ptr->modifier == lModifier) {
                u_number = va_arg(*args_ptr, unsigned long);
            } else {
                u_number = (unsigned long)va_arg(*args_ptr, unsigned);
            }
            sign = 1;
            break;
        case 'd':
        case 'i':
        default:
            if (spec_ptr->modifier == lModifier) {
                s21_long_to_unsigned(va_arg(*args_ptr, long), &u_number, &sign);
            } else {
                s21_long_to_unsigned(va_arg(*args_ptr, int), &u_number, &sign);
            }
            break;
    }

    // Set radix for representation.
    switch (spec_ptr->conversion) {
        case 'o':
            radix = 8;
            break;
        case 'x':
        case 'X':
            radix = 16;
            break;
        case 'd':
        case 'u':
        case 'i':
        default:
            radix = 10;
            break;
    }

    // Convert unsigned long number to string representation
    num_length = s21_uitoa(num_str, u_number, radix);

    // Edge case: if number and precision is 0 than print nothing.
    if (spec_ptr->precision == 0 && *num_str == '0') {
        num_length = 0;
        *num_str = '\0';
    }

    // Set sign prefix if required
    _set_sign_representation(sign, spec_ptr, &repr);

    // Process `#` flag
    if (spec_ptr->hash_flag) {
        if (spec_ptr->conversion == 'o' &&
            (*num_str != '0' || num_length == 0)) {
            s21_strcat(repr.prefix, "0");
        }
        if (spec_ptr->conversion == 'x' && *num_str != '0') {
            s21_strcat(repr.prefix, "0x");
        }
        if (spec_ptr->conversion == 'X' && *num_str != '0') {
            s21_strcat(repr.prefix, "0X");
        }
    }

    // Uppercase if chars if conversion specifier is `X`
    if (spec_ptr->conversion == 'X') {
        _str_to_uppercase(num_str);
    }

    prefix_length = s21_strlen(repr.prefix);
    repr.zeros = spec_ptr->precision - num_length;
    if (repr.zeros < 0) repr.zeros = 0;

    repr.spaces = spec_ptr->width - (num_length + prefix_length + repr.zeros);
    if (repr.spaces < 0) repr.spaces = 0;

    // Set zeros and spaces
    if (spec_ptr->adjustment == ZeroRightJustified) {
        repr.zeros += repr.spaces;
        repr.spaces = 0;
    } else if (spec_ptr->adjustment == LeftJustified) {
        repr.spaces = -repr.spaces;
    }

    return _repr_to_destination(dest, &repr);
}

s21_size_t _pointer_handler(char *dest, specifier_t *spec_ptr,
                            va_list *args_ptr) {
    spec_ptr->conversion = 'x';
    spec_ptr->modifier = lModifier;
    spec_ptr->hash_flag = TRUE;
    return _integer_handler(dest, spec_ptr, args_ptr);
}

void _bytes_proceeded_handler(int bytes_proceeded, va_list *args_ptr) {
    int *value_storage;

    value_storage = va_arg(*args_ptr, int *);
    *value_storage = bytes_proceeded;
}
