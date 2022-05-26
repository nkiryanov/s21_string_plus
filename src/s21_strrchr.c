#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  // Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке,
  // на которую указывает аргумент str.
  unsigned char char_to_find = (unsigned char)c;
  char *p, *found = S21_NULL;

  // FIXME: уверен, что можно сделать проще и быстрее, но не знаю как 😥
  if (char_to_find == '\0') {
    found = s21_strchr(str, char_to_find);
  } else {
    for (; (p = s21_strchr(str, char_to_find)) != S21_NULL; str = p + 1) {
      found = p;
    }
  }
  return found;
}
