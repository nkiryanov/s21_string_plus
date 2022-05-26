#include "s21_sprintf_utils.h"

#include <math.h>
#include <stdlib.h>

#include "../s21_string.h"

void _str_to_uppercase(char *str) {
    // Uppercase inplace
    for (; *str; str++) {
        if (*str >= 'a' && *str <= 'z') *str -= 'a' - 'A';
    }
}

s21_size_t _wstrlen(const wchar_t *w_str) {
    // Strlen for wide chars.
    const wchar_t *s;
    for (s = w_str; *s; ++s) {
    }
    return (s - w_str);
}

s21_size_t _truncate_fraction_zeros(char *str, int str_length) {
    // Truncate fraction trailing zeros if exists. Returns str_length after
    // truncating
    char *str_end = str + str_length - 1;

    while (str_end > str && *str_end == '0') {
        *str_end-- = '\0';
    }

    if (*str_end == '.') {
        *str_end-- = '\0';
    }

    return str_end - str;
}

void _set_sign_representation(int sign, specifier_t *spec_ptr,
                              representation_t *repr_ptr) {
    // Set sign prefix representation based on actual sign and sign_flag
    if (spec_ptr->sign_flag) repr_ptr->prefix[0] = spec_ptr->sign_flag;
    if (sign < 0) repr_ptr->prefix[0] = '-';
}

s21_size_t _repr_to_destination(char *dest, representation_t *repr_ptr) {
    // Push representation struct to destination char
    char *dest_start = dest;
    char *num_repr = repr_ptr->repr;

    while (repr_ptr->spaces-- > 0) {
        *dest++ = ' ';
    }
    for (int i = 0; repr_ptr->prefix[i]; i++) {
        *dest++ = repr_ptr->prefix[i];
    }
    while (repr_ptr->zeros-- > 0) {
        *dest++ = '0';
    }
    while (*num_repr) {
        *dest++ = *num_repr++;
    }
    while (++repr_ptr->spaces < 0) {
        *dest++ = ' ';
    }
    *dest = '\0';

    return dest - dest_start;
}

s21_size_t _double_to_alter_science(char *dest, long double ld_number,
                                    specifier_t *spec_prt) {
    s21_size_t num_length;
    int g_precision;
    int possible_exp = 0;

    possible_exp = s21_get_science_exponent(ld_number);

    g_precision = spec_prt->precision;
    if (g_precision > possible_exp && possible_exp >= -4) {
        g_precision -= possible_exp + 1;
        num_length =
            s21_dtoa(dest, ld_number, g_precision, spec_prt->hash_flag);
    } else {
        g_precision--;
        num_length = s21_double_to_science(dest, ld_number, g_precision,
                                           spec_prt->hash_flag);
    }

    // Truncate leading fraction zeros unless hash flag was used
    if (!spec_prt->hash_flag) {
        num_length = _truncate_fraction_zeros(dest, num_length);
    }

    return num_length;
}

char *_calloc_str(int str_length) {
    char *line;
    line = (char *)calloc(str_length + 1, sizeof(char));
    if (line == S21_NULL) {
        exit(1);
    }
    return line;
}
