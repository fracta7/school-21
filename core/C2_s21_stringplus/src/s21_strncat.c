#include "s21_string.h"

/**
 * @brief Appends the string pointed to, by `src` to the end of the string
 * pointed to, by dest up to `n` characters long.
 * @param dest destination string to append to.
 * @param src string to append.
 * @param n number of characters to append.
 * @return a pointer to resulting string.
 */
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i = 0;
  for (; i < n && src[i] != '\0'; i++) {
    dest[i + dest_len] = src[i];
  }
  dest[dest_len + i] = '\0';
  return dest;
}