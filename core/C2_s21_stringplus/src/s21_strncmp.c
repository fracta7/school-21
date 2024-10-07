#include "s21_string.h"

/**
 * @brief Compares at most the first `n` bytes of `str1` and `str2`.
 * @param str1 first string.
 * @param str2 second string.
 * @param n number of bytes to compare.
 * @return difference between the strings, returns `0` when they are identical.
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  s21_size_t i = 0;
  while (i < n && (str1[i] != '\0' && str2[i] != '\0')) {
    int diff = (unsigned char)str1[i] - (unsigned char)str2[i];
    if (diff != 0) {
      result = s21_normalize(diff);
      break;
    }
    i++;
  }
  if (result == 0 && i < n) result = s21_normalize(str1[i] - str2[i]);
  return result;
}
