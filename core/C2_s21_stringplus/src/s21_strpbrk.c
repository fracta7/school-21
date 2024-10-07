#include "s21_string.h"

/**
 * @brief Finds the first character in the string `str1` that matches any
 * character specified in `str2`.
 * @param str1 string to search in.
 * @param str2 character array for search.
 * @return a pointer to found position.
 */
char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    s21_size_t str1_len = s21_strlen(str1);
    s21_size_t str2_len = s21_strlen(str2);
    for (s21_size_t i = 0; i < str1_len; i++) {
      if (s21_contains_char(str1[i], str2, str2_len)) {
        result = (char *)&(str1[i]);
        break;
      }
    }
  }
  return result;
}