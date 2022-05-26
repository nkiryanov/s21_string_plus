#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  /*
  Возвращает указатель на первый символ в строке, указанный параметром str1,
  который совпадает с любым символом в строке, на который указывает str2.
  */

  int is_found = 0;
  const char *result_ptr = S21_NULL;

  for (int i = 0; !is_found && str1[i] != '\0'; i++) {
    for (int j = 0; !is_found && str2[j] != '\0'; j++)
      if (str1[i] == str2[j]) {
        result_ptr = str1 + i;
        is_found = 1;
      }
  }

  return (char *) result_ptr;
}
