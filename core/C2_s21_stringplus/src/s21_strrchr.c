#include "s21_string.h"

/**
 * @brief Searches for the last occurrence of the character `c` (an `unsigned
 * char`) in the string pointed to by the argument `str`.
 * @param str string to search in.
 * @param c character to find (`unsigned char`).
 * @return a pointer to matching position.
 */
char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = len; i > 0; i--) {
    if ((unsigned char)str[i] == (unsigned char)c) {
      result = (char *)&(str[i]);
      break;
    }
  }
  if (result == S21_NULL && (unsigned char)str[0] == (unsigned char)c)
    result = (char *)&(str[0]);
  return result;
}