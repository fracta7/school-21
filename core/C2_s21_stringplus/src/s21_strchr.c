#include "s21_string.h"

/**
 * @brief Searches for the first occurrence of the character `c` (an `unsigned
 * char`) in the string pointed to, by the argument `str`.
 * @param str string to search in.
 * @param c character to search (`unsigned char`).
 * @return a pointer to found position.
 */
char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  s21_size_t len = 0;
  while (str[len] != '\0') {
    if ((unsigned char)str[len] == (unsigned char)c) {
      result = (char *)&(str[len]);
      break;
    }
    len++;
  }

  // check if c is '\0' character at the end of string
  if ((unsigned char)str[len] == (unsigned char)c) {
    result = (char *)&(str[len]);
  }
  return result;
}