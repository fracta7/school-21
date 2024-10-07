#include "s21_string.h"

/**
 * @brief Computes the length of the string `str` up to but not including the
 * terminating null character.
 * @param str string to calculate the length.
 * @return length of the string.
 */
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (str[len] != '\0') len++;
  return len;
}