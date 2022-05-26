#ifndef SRC_S21_SPRINTF_UTILS_S21_SPRINTF_UTILS_H_
#define SRC_S21_SPRINTF_UTILS_S21_SPRINTF_UTILS_H_

#include <stdarg.h>
#include <stdlib.h>

#include "../s21_string.h"

// NOT_SET declaration
#ifndef NOT_SET
#define NOT_SET -1
#endif  // NOT_SET

#define MAX(first, second) ((first) > (second) ? (first) : (second))

enum adjustment { RightJustified, ZeroRightJustified, LeftJustified };
enum modifier { OrdinaryModifier, hModifier, lModifier, LModifier };

typedef struct specifier_t {
    enum adjustment adjustment;
    char sign_flag;
    int hash_flag;
    int width;
    int precision;
    enum modifier modifier;
    char conversion;
} specifier_t;

typedef struct representation_t {
    int spaces;
    char prefix[4];
    int zeros;
    char *repr;
} representation_t;

#define SPECIFIER_DEFAULTS \
    { RightJustified, '\0', FALSE, NOT_SET, NOT_SET, OrdinaryModifier, '\0' }
#define REPRESENTATION_DEFAULTS \
    { 0, "", 0, S21_NULL }

// Utils
void _str_to_uppercase(char *str);
s21_size_t _wstrlen(const wchar_t *w_str);
s21_size_t _repr_to_destination(char *dest, representation_t *repr_ptr);
s21_size_t _double_to_alter_science(char *dest, long double num,
                                    specifier_t *spec);
s21_size_t _truncate_fraction_zeros(char *str, int str_length);
char * _calloc_str(int str_length);

// sprintf parse utils
s21_size_t _parse_format(const char *format, specifier_t *spec, va_list *args);
int _get_flags(const char *format, specifier_t *spec);
int _get_width_precision(const char *format, int *num_ptr, va_list *args);
int _get_length_modifier(const char *format, specifier_t *spec);
int _get_conversion_specifier(const char *format, specifier_t *spec);
void _set_sign_representation(int sign, specifier_t *spec,
                              representation_t *repr);
void _turn_off_incompatible_flags(specifier_t *spec_ptr);

// sprintf handlers
s21_size_t _char_handler(char *dest, specifier_t *spec, va_list *args_ptr);
s21_size_t _string_handler(char *dest, specifier_t *spec, va_list *args_ptr);
s21_size_t _float_handler(char *dest, specifier_t *spec, va_list *args_ptr);
s21_size_t _integer_handler(char *dest, specifier_t *spec, va_list *args_ptr);
s21_size_t _pointer_handler(char *dest, specifier_t *spec, va_list *args_ptr);
void _bytes_proceeded_handler(int bytes_proceeded, va_list *args_ptr);

#endif  // SRC_S21_SPRINTF_UTILS_S21_SPRINTF_UTILS_H_
