#include "s21_string.h"

char *s21_strchr(const char *str, const char chr) {
  char *pointer = S21_NULL;
  while (*str && *str != chr) {
    str++;
  }
  if (*str == chr) {
    pointer = (char *)str;
  }

  return pointer;
}
