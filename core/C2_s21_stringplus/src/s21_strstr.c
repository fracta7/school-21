#include "s21_string.h"

/**
 * @brief Finds the first occurrence of the entire string `needle` (not
 * including the terminating null character) which appears in the string
 * `haystack`.
 * @param haystack a string to search in.
 * @param needle a string to search for.
 * @return a pointer to a matching posiiton.
 */
char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  if (haystack != S21_NULL && needle != S21_NULL) {
    if (*needle == '\0') {
      result = (char *)haystack;
    } else {
      s21_size_t len = s21_strlen(haystack);
      s21_size_t needle_len = s21_strlen(needle);
      if (len >= needle_len) {
        for (s21_size_t i = 0; i <= len - needle_len; i++) {
          if (s21_strncmp(&(haystack[i]), needle, needle_len) == 0) {
            result = (char *)&(haystack[i]);
            break;
          }
        }
      }
    }
  }
  return result;
}