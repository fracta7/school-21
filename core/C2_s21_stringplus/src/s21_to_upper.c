#include "s21_string.h"

/**
 * @brief Returns a copy of string (str) converted to uppercase.
 * @param str a string to convert to upper case.
 * @return a copy of string with uppercase letters. Returns `NULL` if fails.
 */
void *s21_to_upper(const char *str) {
  char *copy = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t len = s21_strlen(str);
    copy = (char *)malloc((len + 1) * sizeof(char));
    if (copy != S21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        if (str[i] > 96 && str[i] < 123)
          copy[i] = (char)str[i] - 32;
        else
          copy[i] = (char)str[i];
      }
      copy[len] = '\0';
    }
  }
  return (void *)copy;
}
