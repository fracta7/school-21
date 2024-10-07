#include "s21_string.h"

/**
 * @brief Breaks string `str` into a series of tokens separated by `delim`.
 * @param str a string to break into tokens.
 * @param delim an array of deliminator character to replace with null
 * character.
 * @return a pointer to the `n`th token.
 */
char *s21_strtok(char *str, const char *delim) {
  static char *last = S21_NULL;
  char *start = last;
  s21_size_t delim_len = s21_strlen(delim);

  if (str != S21_NULL) last = str;

  if (last != S21_NULL) {
    // skip leading delimiters
    while (*last && s21_contains_char(*last, delim, delim_len)) last++;

    if (*last == '\0') {
      last = S21_NULL;   // reset if the string is fully parsed
      start = S21_NULL;  // no tokens left
    } else {
      start = last;  // point to the start of the token

      // move last pointer to the end of the token
      while (*last && !s21_contains_char(*last, delim, delim_len)) last++;

      // null-terminate the token
      if (*last) {
        *last = '\0';
        last++;  // move to the next token
      } else {
        last = S21_NULL;  // reset last
      }
    }
  }

  return start;
}
