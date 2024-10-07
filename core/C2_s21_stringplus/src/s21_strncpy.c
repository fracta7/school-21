#include "s21_string.h"

/**
 * @brief Copies string up to `n` from `src` to `dest`
 * @param dest a destination string to copy to.
 * @param src a source string to copy from.
 * @param n number of characters to copy.
 * @return a pointer to destination string.
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  for (; i < n; i++) {
    dest[i] = '\0';
  }
  return dest;
}