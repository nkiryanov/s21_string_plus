#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  // Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
  // байтах строки, на которую указывает аргумент str.
  const unsigned char *char_ptr = (const unsigned char *)str;
  const unsigned char converted_chr = (const unsigned char)c;
  s21_size_t tmp = n;

  for (; --tmp > 0 && *char_ptr != converted_chr; char_ptr++) {
  }

  return (*char_ptr == converted_chr && n != 0) ? (void *)char_ptr : S21_NULL;
}
