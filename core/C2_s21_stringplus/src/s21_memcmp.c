#include "s21_string.h"

/**
 * @brief Compares the first n bytes of str1 and str2.
 * @param str1 first block of memory.
 * @param str2 second block of memory.
 * @return difference between the blocks. Returns 0 when blocks are identical.
 */
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  const unsigned char *block1 = (const unsigned char *)str1;
  const unsigned char *block2 = (const unsigned char *)str2;
  for (s21_size_t i = 0; i < n; i++) {
    int diff = block1[i] - block2[i];
    if (diff != 0) {
      result = s21_normalize(diff);
      break;
    }
  }
  return result;
}
