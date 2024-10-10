#include "s21_string.h"

/**
 * @brief Checks if `c` is in `str` array.
 * @param c character to search in a string.
 * @param str string to search in.
 * @param len the lengths of the string.
 * @return `1` when the string has the character, `0` when it doesn't.
 */
int s21_contains_char(const char c, const char *str, s21_size_t len) {
  int result = 0;
  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] == c) {
      result = 1;
      break;
    }
  }
  return result;
}
