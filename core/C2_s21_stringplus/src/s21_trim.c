#include "s21_string.h"

/**
 * @brief Returns a new string in which all leading and trailing occurrences of
 * a set of specified characters (`trim_chars`) from the given string (`src`)
 * are removed.
 * @param src a string to trim.
 * @param trim_chars array of characters to be trimmed from the string.
 * @return Trimmed string. Returns NULL in case of error.
 */
void *s21_trim(const char *src, const char *trim_chars) {
  char *string = S21_NULL;
  if (src != S21_NULL && trim_chars != S21_NULL) {
    s21_size_t len = s21_strlen(src);
    s21_size_t c_len = s21_strlen(trim_chars);

    s21_size_t start = 0;
    while (start < len && s21_contains_char(src[start], trim_chars, c_len))
      start++;

    s21_size_t end = len;
    while (end > start && s21_contains_char(src[end - 1], trim_chars, c_len))
      end--;

    s21_size_t new_len = end - start;

    string = (char *)malloc((new_len + 1) * sizeof(char));
    if (string != S21_NULL) {
      s21_strncpy(string, src + start, new_len);
      string[new_len] = '\0';
    }
  }

  return (void *)string;
}
