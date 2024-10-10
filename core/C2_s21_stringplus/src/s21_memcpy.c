#include "s21_string.h"

/**
 * @brief copies `src` memory block to `dest` memory blocks up to `n` bytes.
 * @param dest destination to copy memory.
 * @param src source memory block to copy from.
 * @param n amount of bytes to copy.
 * @return a pointer to a destination block.
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
  }
  return dest;
}
