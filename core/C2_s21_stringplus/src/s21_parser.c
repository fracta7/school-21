#include "s21_string.h"

void s21_check_star(FORMAT *s_format, int *pres_or_width, int *num, char f_ch) {
  if (f_ch == '*') {
    if (*pres_or_width) {
      s_format->error = 1;
    } else {
      *pres_or_width = '*';  // Set as a star
      s_format->star = 1;
    }
  } else {
    if (*pres_or_width == '*') {
      s_format->error = 1;
    } else {
      // Convert f_ch to an integer
      int result;
      const char num_str[2] = {f_ch, '\0'};  // Create a string from f_ch
      int status = s21_char_to_int(num_str, &result);
      if (status == 0) {
        *num = result;  // Store the converted value in num
      } else {
        s_format->error = 1;  // Set error if conversion fails
      }
    }
  }
}

int s21_char_to_int(const char *num_str, int *result) {
  if (num_str == NULL || result == NULL) {
    return -1;  // Indicate an error if inputs are invalid
  }

  int sign = 1;
  *result = 0;  // Initialize the result
  const char *ptr = num_str;

  // Skip whitespace
  while (*ptr == ' ') {
    ptr++;
  }

  // Handle optional sign
  if (*ptr == '-') {
    sign = -1;
    ptr++;
  } else if (*ptr == '+') {
    ptr++;
  }

  // Convert characters to integer
  while (*ptr >= '0' && *ptr <= '9') {
    int digit = *ptr - '0';

    // Check for overflow
    if (*result > (INT_MAX - digit) / 10) {
      return -2;  // Indicate an overflow error
    }

    *result = *result * 10 + digit;
    ptr++;
  }

  *result *= sign;  // Apply sign
  return 0;         // Indicate success
}

int s21_parser(int ptr_f, const char *format, FORMAT *s_format) {
  ptr_f++;
  int num_p = 0;
  int num_w = 0;
  int count = 0;
  while (!s_format->spec) {
    if (S21_IS_SPEC(format[ptr_f])) {
      s_format->spec = format[ptr_f];
    } else if (S21_IS_LENGTH(format[ptr_f])) {
      if (!count) {
        s_format->length = format[ptr_f];
        count++;
      } else {
        if (s_format->length != format[ptr_f]) {
          s_format->error = 1;
        } else {
          s_format->double_len = 1;
        }
      }
    } else if (format[ptr_f] == '.') {
      s_format->point = 1;
    } else if (format[ptr_f] == '0' && !num_w && !s_format->point) {
      s_format->zero = 1;
    } else if (s_format->point && S21_IS_NUMERIC(format[ptr_f])) {
      s21_check_star(s_format, &s_format->precision, &num_p, format[ptr_f]);
    } else if (S21_IS_NUMERIC(format[ptr_f])) {
      s21_check_star(s_format, &s_format->width, &num_w, format[ptr_f]);
    } else if (format[ptr_f] == '-') {
      s_format->minus = 1;
    } else if (format[ptr_f] == '+') {
      s_format->plus = 1;
    } else if (format[ptr_f] == ' ') {
      s_format->space = 1;
    } else if (format[ptr_f] == '#') {
      s_format->sharp = 1;
    }
    ptr_f++;
  }
  if (s_format->precision != 42) s_format->precision = num_p;
  if (s_format->width != 42) s_format->width = num_w;

  return ptr_f;
}
