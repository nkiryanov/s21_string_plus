#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  /*
  Добавляет строку, на которую указывает src, в конец строки, на которую
  указывает dest, длиной до n символов.
  */
  char *start = dest;

  dest += s21_strlen(dest);
  s21_size_t dest_plus_src_len = s21_strnlen(src, n);

  dest[dest_plus_src_len] = '\0';
  s21_memcpy(dest, src, dest_plus_src_len);

  return start;
}
