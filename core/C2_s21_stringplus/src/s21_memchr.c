#include "s21_string.h"

/**
 * @brief Searches for the first occurrence of the character `c` (an `unsigned
 * char`) in the first `n` bytes of the string pointed to, by the argument
 * `str`.
 * @param str block of memory to search in.
 * @param c a byte (`unsigned char`) to search in `str`.
 * @return a pointer to a memory where the byte is found.
 */
void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *result = S21_NULL;
  const unsigned char *string = (const unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    if (string[i] == (unsigned char)c) {
      result = (void *)&(string[i]);
      break;
    }
  }
  return result;
}
