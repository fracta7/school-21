#include "s21_string.h"

/**
 * @brief Returns a new string in which a specified string (`str`) is inserted
 * at a specified index position (`start_index`) in the given string (`src`).
 * @param src a string to insert to.
 * @param str a string to insert.
 * @param start_index starting index at which `str` is inserted.
 * @return a new string with insertion. Returns `NULL` if there is error.
 */
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *string = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);

    if (start_index <= src_len) {
      string = (char *)malloc((src_len + str_len + 1) * sizeof(char));
      if (string != S21_NULL) {
        for (s21_size_t i = 0; i < start_index; i++) string[i] = src[i];

        for (s21_size_t i = 0; i < str_len; i++)
          string[i + start_index] = str[i];

        for (s21_size_t i = start_index; i <= src_len; i++)
          string[i + str_len] = src[i];

        string[src_len + str_len] = '\0';
      }
    }
  }
  return (void *)string;
}
