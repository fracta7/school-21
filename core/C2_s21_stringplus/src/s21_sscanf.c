#include "s21_string.h"

void s21_custom_atoi(char **src, long *num, int length) {
  int minus = 0;
  char *q = *src;
  if (length == -1)
    length = s21_strlen(*src);
  else if (length == 0)
    return;
  if (*q == '-') {
    minus = 1;
    q++;
    length--;
  } else if (*q == '+') {
    q++;
    length--;
  }
  if (*q == '0') {
    q++;
    length--;
    // int n;
    int len = 0;
    if (*q == 'x') {
      q++;
      length--;
      const char *blank = "0123456789ABCDEF";
      if (length > 0) *num = 0;
      while (s21_get_character_index(blank, *q) != -1 && length > 0) {
        len++;
        q++;
        length--;
      }
      q -= len;
      for (; len > 0; len--) {
        *num += s21_get_character_index(blank, *q) * pow(16, len - 1);
        q++;
      }
    } else {
      const char *blank = "01234567";
      if (length > 0) *num = 0;
      while (s21_get_character_index(blank, *q) != -1 && length > 0) {
        len++;
        q++;
        length--;
      }
      q -= len;
      for (; len > 0; len--) {
        *num += s21_get_character_index(blank, *q) * pow(8, len - 1);
        q++;
      }
    }
  } else {
    if (length > 0) *num = 0;
    while (*q >= '0' && *q <= '9' && length > 0) {
      *num *= 10;
      *num += *q - 48;
      q++;
      length--;
    }
  }
  *src = q;
  if (minus == 1) *num *= -1;
}

void s21_skip_spaces(char **str) {
  char *q = *str;
  while (*q == ' ') {
    q++;
  }

  *str = q;
}

char *s21_get_int(char *src, long *num, int length) {
  int minus = 0;
  if (length == -1) {
    length = s21_strlen(src);
  } else if (length == 0) {
    return src;
  }
  if (*src == '-') {
    minus = 1;
    src++;
    length--;
  } else if (*src == '+') {
    src++;
    length--;
  }

  if (length > 0) {
    *num = 0;
  }

  *num = 0;  // added by doz

  while (*src >= '0' && *src <= '9' && length > 0) {
    *num *= 10;
    *num += *src - 48;
    src++;
    length--;
  }

  if (minus == 1) *num *= -1;

  return src;
}

void s21_get_char(char **src, int *c, int length) {
  if (length == 0) return;
  char *q = *src;
  *c = q[0];
  q++;
  *src = q;
}

void s21_parse_integer_part(char **q, long double *num, int *length) {
  while (**q >= '0' && **q <= '9' && *length > 0) {
    *num *= 10.0L;
    *num += (**q - '0');
    (*q)++;
    (*length)--;
  }
}

void s21_parse_fraction_part(char **q, long double *num, int *length) {
  if (**q == '.') {
    long double fraction = 0.0L;
    long double divider = 1.0L;
    (*q)++;
    (*length)--;
    while (**q >= '0' && **q <= '9' && *length > 0) {
      fraction = fraction * 10.0L + (**q - '0');
      divider *= 10.0L;
      (*q)++;
      (*length)--;
    }
    *num += fraction / divider;
  }
}

void s21_parse_exponent_part(char **q, long double *num, int *length) {
  if (**q == 'e' || **q == 'E') {
    (*q)++;
    (*length)--;
    int exp_sign = 1;
    if (**q == '-') {
      exp_sign = -1;
      (*q)++;
      (*length)--;
    } else if (**q == '+') {
      (*q)++;
      (*length)--;
    }

    long exponent = 0;
    while (**q >= '0' && **q <= '9' && *length > 0) {
      exponent = exponent * 10 + (**q - '0');
      (*q)++;
      (*length)--;
    }

    for (long i = 0; i < exponent; i++) {
      if (exp_sign == -1) {
        *num /= 10.0L;
      } else {
        *num *= 10.0L;
      }
    }
  }
}

void s21_get_float(char **src, long double *num, int length) {
  char *q = *src;
  int minus = 0;
  if (length == -1)
    length = s21_strlen(*src);
  else if (length <= 0)
    *num = 0;

  if (*q == '-') {
    minus = 1;
    q++;
    length--;
  } else if (*q == '+') {
    q++;
    length--;
  }

  if (length > 0) *num = 0;

  // Integer part
  s21_parse_integer_part(&q, num, &length);

  // Fractional part
  s21_parse_fraction_part(&q, num, &length);

  // Exponent part
  s21_parse_exponent_part(&q, num, &length);

  *src = q;
  if (minus) *num *= -1;
}

void s21_get_string(char **src, char *dest, int length) {
  char *q = *src;
  s21_size_t i = 0;
  if (length == -1)
    length = s21_strlen(*src);
  else if (length == 0)
    return;
  while (*q != ' ' && *q != '\0' && length != 0) {
    dest[i] = *q;
    i++;
    q++;
    length--;
  }
  dest[i] = '\0';
  *src = q;
}

int s21_get_character_index(const char *src, const char c) {
  int index = -1;
  s21_size_t len = s21_strlen(src);
  for (s21_size_t i = 0; i < len; i++) {
    if (src[i] == c) {
      index = i;
      break;
    }
  }
  return index;
}

void s21_get_octa(char **src, unsigned long *num, int length) {
  char *q = *src;
  int minus = 0;
  if (length == -1)
    length = s21_strlen(*src);
  else if (length == 0)
    return;
  if (*q == '-') {
    minus = 1;
    q++;
    length--;
  } else if (*q == '+') {
    q++;
    length--;
  }
  int len = 0;
  const char *blank = "01234567";
  if (length > 0) *num = 0;
  while (s21_get_character_index(blank, *q) != -1 && length > 0) {
    len++;
    q++;
    length--;
  }
  q -= len;
  for (; len > 0; len--) {
    *num += s21_get_character_index(blank, *q) * pow(8, len - 1);
    q++;
  }
  if (minus == 1) *num *= -1;
  *src = q;
}

void s21_handle_c(const char **str, va_list *args, int star_flag, long length,
                  int *count) {
  if (star_flag) {
    int tmp;
    s21_get_char((char **)str, &tmp, length);
  } else {
    s21_get_char((char **)str, va_arg(*args, int *), length);
  }
  (*count)++;
}

void s21_handle_s(const char **str, va_list *args, int star_flag, long length,
                  int l, int *count) {
  s21_skip_spaces((char **)str);
  if (star_flag) {
    char *tmp = malloc(sizeof(char));
    s21_get_string((char **)str, tmp, length);
    free(tmp);
  } else if (l == 1) {
    // Handle wide character strings here
  } else {
    s21_get_string((char **)str, va_arg(*args, char *), length);
  }
  (*count)++;
}

void s21_handle_i(const char **str, va_list *args, int star_flag, long length,
                  int *count) {
  s21_skip_spaces((char **)str);
  if (star_flag) {
    long tmp;
    s21_custom_atoi((char **)str, &tmp, length);
  } else {
    s21_custom_atoi((char **)str, (long *)(va_arg(*args, int *)), length);
  }
  (*count)++;
}

void s21_handle_d_u(const char **str, va_list *args, int star_flag, long length,
                    int *count) {
  s21_skip_spaces((char **)str);
  if (star_flag) {
    long tmp;
    *str = s21_get_int((char *)*str, &tmp, length);
  } else {
    *str = s21_get_int((char *)*str, (long *)(va_arg(*args, short *)), length);
  }
  (*count)++;
}

void s21_handle_f_e_g(const char **str, va_list *args, int star_flag,
                      long length, int h, int l, int L, int *count) {
  s21_skip_spaces((char **)str);
  if (star_flag) {
    long double tmp;
    s21_get_float((char **)str, &tmp, length);
  } else if (l == 1 || h == 1) {
    double *t_l = va_arg(*args, double *);
    long double tmp;
    s21_get_float((char **)str, &tmp, length);
    *t_l = (double)tmp;
  } else if (L == 1) {
    s21_get_float((char **)str, va_arg(*args, long double *), length);
  } else {
    float *t_l = va_arg(*args, float *);
    long double tmp;
    s21_get_float((char **)str, &tmp, length);
    *t_l = (float)tmp;
  }
  (*count)++;
}

void s21_handle_o(const char **str, va_list *args, int star_flag, long length,
                  int *count) {
  s21_skip_spaces((char **)str);
  if (star_flag) {
    unsigned long tmp;
    s21_get_octa((char **)str, &tmp, length);
  } else {
    s21_get_octa((char **)str, va_arg(*args, unsigned long *), length);
  }
  (*count)++;
}

void s21_handle_x(const char **str, va_list *args, int star_flag, int *count) {
  s21_skip_spaces((char **)str);
  unsigned long tmp = 0;

  if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    *str += 2;
  }

  while ((**str >= '0' && **str <= '9') || (**str >= 'a' && **str <= 'f') ||
         (**str >= 'A' && **str <= 'F')) {
    if (**str >= '0' && **str <= '9') {
      tmp = (tmp << 4) | (**str - '0');
    } else if (**str >= 'a' && **str <= 'f') {
      tmp = (tmp << 4) | (**str - 'a' + 10);
    } else if (**str >= 'A' && **str <= 'F') {
      tmp = (tmp << 4) | (**str - 'A' + 10);
    }
    (*str)++;
  }

  if (!star_flag) {
    *(unsigned long *)va_arg(*args, unsigned long *) = tmp;
  }

  (*count)++;
}

void s21_handle_p(const char **str, va_list *args, int star_flag, int *count) {
  s21_skip_spaces((char **)str);
  unsigned long tmp = 0;

  if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    *str += 2;
  }

  while ((**str >= '0' && **str <= '9') || (**str >= 'a' && **str <= 'f') ||
         (**str >= 'A' && **str <= 'F')) {
    if (**str >= '0' && **str <= '9') {
      tmp = (tmp << 4) | (**str - '0');
    } else if (**str >= 'a' && **str <= 'f') {
      tmp = (tmp << 4) | (**str - 'a' + 10);
    } else if (**str >= 'A' && **str <= 'F') {
      tmp = (tmp << 4) | (**str - 'A' + 10);
    }
    (*str)++;
  }

  if (!star_flag) {
    *(void **)va_arg(*args, void **) = (void *)tmp;
  }

  (*count)++;
}

void s21_ss_handle_flags(const char **format, int *star_flag, long *length,
                         int *h, int *l, int *L) {
  // Reset flags
  *star_flag = 0;
  *h = 0;
  *l = 0;
  *L = 0;
  *length = -1;

  // Parse optional width (number)
  if (**format >= '0' && **format <= '9') {
    *format = s21_get_int((char *)*format, length, -1);
  } else if (**format == '*') {  // Parse '*' (star flag)
    *star_flag = 1;
    (*format)++;
  }

  // Parse length modifiers (h, l, L)
  if (**format == 'h') {
    *h = 1;
    (*format)++;
  } else if (**format == 'l') {
    *l = 1;
    (*format)++;
  } else if (**format == 'L') {
    *L = 1;
    (*format)++;
  }
}

void s21_ss_handle_spec(const char **str, const char **format, va_list *args,
                        int star_flag, long length, int h, int l, int L,
                        int *count) {
  switch (**format) {
    case 'c':
      s21_handle_c(str, args, star_flag, length, count);
      break;
    case 's':
      s21_handle_s(str, args, star_flag, length, l, count);
      break;
    case 'i':
      s21_handle_i(str, args, star_flag, length, count);
      break;
    case 'u':
    case 'd':
      s21_handle_d_u(str, args, star_flag, length, count);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      s21_handle_f_e_g(str, args, star_flag, length, h, l, L, count);
      break;
    case 'o':
      s21_handle_o(str, args, star_flag, length, count);
      break;
    case 'x':
    case 'X':
      s21_handle_x(str, args, star_flag, count);
      break;
    case 'p':
      s21_handle_p(str, args, star_flag, count);
      break;
    case 'n': {
      int *num = va_arg(*args, int *);
      *num = s21_strlen(*str) - length;
      *num *= -1;
      (*count)++;
      break;
    }
  }
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int count = 0;
  long length;
  while (*format) {
    length = -1;
    if (*format == '%') {
      int star_flag = 0, h = 0, l = 0, L = 0;
      format++;
      s21_ss_handle_flags(&format, &star_flag, &length, &h, &l, &L);
      s21_ss_handle_spec(&str, &format, &args, star_flag, length, h, l, L,
                         &count);
    }
    format++;
  }
  va_end(args);
  return count;
}
