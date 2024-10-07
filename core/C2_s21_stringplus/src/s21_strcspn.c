#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = s21_strlen(str2);
  int count = 0;
  int flag = 0;
  char *str11 = (char *)str1;
  while (*str11 != '\0') {
    for (s21_size_t i = 0; i < len; i++) {
      if ((*str11) == str2[i]) {
        flag = 1;
        break;
      }
    }
    if (flag == 1) break;
    str11++;
    count++;
  }

  return count;
}