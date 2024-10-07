#include "s21_string.h"

/**
 * @brief Copies the character `c` (an `unsigned char`) to the first `n`
 * characters of the string pointed to, by the argument `str`.
 * @param str memory block to fill with `c` bytes.
 * @param c a byte to fill with.
 * @param n amount of memory to fill.
 * @return a pointer to a `str`.
 */
void *s21_memset(void *str, int c, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    ((unsigned char *)str)[i] = (unsigned char)c;
  }
  return str;
}