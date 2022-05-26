#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

// s21_size_t declaration
#ifndef s21_size_t
typedef unsigned long s21_size_t;
#endif  // s21_size_t

// TRUE declaration
#ifndef TRUE
#define TRUE 1
#endif  // TRUE

// FALSE declaration
#ifndef FALSE
#define FALSE 0
#endif  // FALSE

// NULL pointer declaration
#ifndef S21_NULL
#define S21_NULL ((void *)0)
#endif  // S21_NULL

#ifndef LL_MAX_WIDTH
#define LL_MAX_WIDTH (sizeof(long long int) * 8 + sizeof(char) * 2)
#endif  // LL_MAX_WIDTH

// Manually written standard functions declaration

// s21_string_utils
void s21_long_to_unsigned(long number, unsigned long *u_number_ptr,
                          int *sign_ptr);

// Support functions in separate files
int s21_uitoa(char *dest, unsigned long long u_number,
              const unsigned int radix);
int s21_itoa(char *dest, long number, const unsigned int radix);
int s21_dtoa(char *dest, double long number, int precision, int radix_required);
int s21_atoi(char *digits_str);
int s21_isdigit(char chr);
int s21_get_science_exponent(long double ld_number);

// s21_functions
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, const char chr);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(char *string, char *substring);

s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strnlen(const char *str, s21_size_t n);

int s21_sprintf(char *dest, const char *format, ...);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strreverse(char *str);
char *s21_strrchr(const char *str, int c);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char* str1);
void *s21_to_lower(const char* str1);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
s21_size_t s21_double_to_science(char *dest, long double number, int precision,
                             int radix_required);

char *s21_strpbrk(const char *str1, const char *str2);

#endif  // SRC_S21_STRING_H_
