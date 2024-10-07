#include "s21_string.h"

// essentials
void s21_int_to_char(FORMAT s_format, unsigned long long int num, char *buf,
                     int *i) {
  int flag = 1;
  if (num == 0 && s_format.spec != 'f' && !s_format.point) buf[*i] = '0';
  while (flag) {
    int digit = 0;
    if (num >= 10) {
      digit = num % 10;
      num = (num - digit) / 10;
    } else {
      digit = (int)num;
      flag = 0;
    }
    buf[*i] = (char)(digit + '0');
    (*i)++;
  }
  if (s_format.spec != 'f' && s_format.precision == 0 && num == 0 &&
      s_format.point)
    buf[0] = '\0';
  buf[*i] = '\0';
}

void s21_precision_int(FORMAT s_format, char *buf, int *i) {
  if (s_format.precision > 0) {
    while (*i < s_format.precision) {
      buf[*i] = '0';
      (*i)++;
    }
  }
}

void s21_int_to_string(char *buf, FORMAT s_format, long long int num) {
  int i = 0;
  int is_negative = 0;
  if (num < 0) {
    is_negative = 1;
    num *= -1;
  }
  s21_int_to_char(s_format, num, buf, &i);
  s21_precision_int(s_format, buf, &i);
  s21_reverse_string(buf, i);
  s21_make_flags(is_negative, s_format, buf);
  s21_make_width(s_format, buf, is_negative);
}

void s21_reverse_string(char *str, int i) {
  str[i] = '\0';
  int left = 0;
  int right = i - 1;
  while (left < right) {
    char temp = str[left];
    str[left++] = str[right];
    str[right--] = temp;
  }
}

void s21_reset_format(FORMAT *s_format) {
  s_format->minus = 0;
  s_format->plus = 0;
  s_format->double_len = 0;
  s_format->precision = 0;
  s_format->zero = 0;
  s_format->sharp = 0;
  s_format->point = 0;
  s_format->spec = 0;
  s_format->space = 0;
  s_format->width = 0;
  s_format->length = 0;
  s_format->star = 0;
}

void s21_move_string(char *buf) {
  int pos = 0;
  pos = s21_strlen(buf);
  buf[pos + 1] = '\0';
  while (pos > 0) {
    buf[pos] = buf[pos - 1];
    pos--;
  }
}

void s21_f_to_str(long double num, FORMAT s_format, char *buf) {
  int is_negative = 0;
  if (num < 0) {
    is_negative = 1;
    num *= -1;
  }
  if (num == s21_INF) {
    if (is_negative) {
      is_negative = 4;
    } else {
      is_negative = 3;
    }
    buf = s21_strncat(buf, "inf", 3);
  } else if (num != num) {
    is_negative = 2;
    buf = s21_strncat(buf, "nan", 3);
    s_format.spec = 's';
  } else {
    int i = 0;
    int accuracy = 0;
    if (s_format.point && s_format.precision >= 0) {
      accuracy = s_format.precision;
    } else {
      accuracy = 6;
    }
    if (num < 0) {
      is_negative = 1;
      num *= -1;
    }
    char buf_dec[256] = {0};
    long double pos_int = 0, dec = 0;
    long double p = pow(10, (accuracy));
    num = rintl(num * p) / p;
    dec = modfl(num, &pos_int);
    s21_int_to_char(s_format, rintl(pos_int), buf, &i);
    s21_reverse_string(buf, i);
    for (; buf[i]; i++)
      ;
    if (s_format.sharp || accuracy > 0) buf[i++] = '.';
    for (int in = 0; in < accuracy; in++) dec *= 10;
    i = 0;
    if (accuracy > 0) s21_int_to_char(s_format, rintl(dec), buf_dec, &i);
    s21_reverse_string(buf_dec, i);
    i = s21_strlen(buf_dec);
    for (int j = 0; i < accuracy; j++, i++) {
      s21_move_string(buf_dec);
      buf_dec[j] = '0';
    }
    buf_dec[i] = '\0';
    buf = s21_strncat(buf, buf_dec, 256);
  }
  s21_make_flags(is_negative, s_format, buf);
  s21_make_width(s_format, buf, is_negative);
}

void s21_e_to_str(long double num, FORMAT s_format, char *buf) {
  int is_negative = 0;
  if (num < 0) {
    is_negative = 1;
    num *= -1;
  }
  if (num == s21_INF) {
    buf = s21_strncat(buf, "inf", 4);
  } else {
    int exponent = 0;
    while (num >= 10.0) {
      num /= 10.0;
      exponent++;
    }
    while (num > 0 && num < 1.0) {
      num *= 10.0;
      exponent--;
    }
    FORMAT empty_format = {0};
    s21_reset_format(&empty_format);
    char number_buf[128] = {0};
    s21_f_to_str(num, empty_format, number_buf);
    char exp_buf[10] = {0};
    char exp_sign = (exponent >= 0) ? '+' : '-';
    exponent = (exponent >= 0) ? exponent : -exponent;
    exp_buf[0] = exp_sign;
    if (exponent < 10) s21_strncat(exp_buf, "0", 1);
    s21_int_to_string(exp_buf + s21_strlen(exp_buf), empty_format, exponent);
    buf = s21_strncat(buf, number_buf, s21_strlen(number_buf));
    char e = (s_format.spec == 'e') ? 'e' : 'E';
    buf = s21_strncat(buf, &e, 1);
    buf = s21_strncat(buf, exp_buf, s21_strlen(exp_buf));
  }
  s21_make_flags(is_negative, s_format, buf);
  s21_make_width(s_format, buf, is_negative);
}

int s21_is_digit(char c) { return (c >= '0' && c <= '9') ? 1 : 0; }

void s21_format_g_flags(char *buff, FORMAT s_format) {
  s21_make_flags(0, s_format, buff);
  s21_make_width(s_format, buff, 0);

  if (s_format.sharp && !s21_strchr(buff, '.')) s21_strncat(buff, ".", 1);
}

void s21_format_g_precision(char *buff, int precision) {
  int sig_digs = 0, not_zero_found = 0;
  s21_size_t len = s21_strlen(buff);

  for (s21_size_t i = 0; i < len; i++) {
    if ((buff[i] == '0' && !not_zero_found) || buff[i] == '.') {
      continue;
    } else {
      not_zero_found = 1;
    }

    if (s21_is_digit(buff[i]) && not_zero_found) sig_digs++;

    if (sig_digs == precision && i + 1 < len) {
      int next = buff[i + 1] == '.' ? 2 : 1;
      // Perform rounding by checking the next digit
      buff[i] = buff[i + next] - '0' > 5 ? (char)(buff[i] + 1) : buff[i];
      buff[i + 1] = '\0';
      break;
    }
  }
}

void s21_g_to_str(long double num, FORMAT s_format, char *buf) {
  // default precision is 6 if not set
  if (s_format.precision == 0) s_format.precision = 6;

  long double val = num;
  if (val == 0) {
    s21_strncpy(buf, "0.0", 3);  // Handle zero case directly
  } else {
    s21_f_to_str(val, s_format, buf);

    s21_format_g_precision(buf, s_format.precision);

    s21_format_g_flags(buf, s_format);
  }
}

void s21_x_to_str(unsigned long long int num, FORMAT s_format, char *buf) {
  int is_uppercase = (s_format.spec == 'X');

  // Handle the case where num is 0
  if (num == 0) {
    if (s_format.point && s_format.precision == 0) {
      buf[0] = '\0';
    } else {
      buf[0] = '0';
      buf[1] = '\0';
    }
  } else {
    char hex_digits[] = "0123456789abcdef";
    char upper_hex_digits[] = "0123456789ABCDEF";
    char temp_buf[64] = {0};
    int index = 0;

    // Convert the number to hexadecimal
    while (num != 0) {
      int digit = num % 16;
      num /= 16;
      temp_buf[index++] =
          is_uppercase ? upper_hex_digits[digit] : hex_digits[digit];
    }

    // Handle the precision
    while (index < s_format.precision) temp_buf[index++] = '0';

    if (s_format.sharp) {
      const char *prefix = (is_uppercase) ? "0X" : "0x";
      s21_strncat(buf, prefix, 2);
    }

    // reverse the buffer
    int buf_len = s21_strlen(buf);
    for (int i = 0; i < index; i++) buf[buf_len + i] = temp_buf[index - i - 1];
    buf[buf_len + index] = '\0';
  }

  s21_make_flags(0, s_format, buf);
  s21_make_width(s_format, buf, 0);
}

void s21_p_to_str(void *ptr, FORMAT s_format, char *buf) {
  unsigned long long int num = (unsigned long long int)ptr;

  if (ptr == NULL) {
    s21_strncat(buf, "(nil)", 5);
  } else {
    FORMAT t_format = {0};
    s21_reset_format(&t_format);
    t_format.sharp = 1;
    s21_x_to_str(num, t_format, buf);
  }

  s21_make_flags(0, s_format, buf);
  s21_make_width(s_format, buf, 0);
}

void s21_u_to_str(char *buf, FORMAT s_format, unsigned long long int num) {
  int i = 0;
  s21_un_to_char(s_format, num, buf, &i);
  s21_precision_int(s_format, buf, &i);
  s21_reverse_string(buf, i);
  s21_make_flags(0, s_format, buf);
  s21_make_width(s_format, buf, 0);
}

void s21_ol_to_str(char *buf, unsigned long long num, FORMAT s_format) {
  int flag = 1;
  int i = 0;
  while (flag) {
    unsigned int digit;
    if (num > 7) {
      digit = num % 8;
      num = (num - digit) / 8;
    } else {
      digit = num;
      flag = 0;
    }
    buf[i++] = (char)(digit + '0');
  }
  if (s_format.sharp == 1) buf[i++] = '0';
  buf[i] = '\0';
  s21_precision_int(s_format, buf, &i);
  s21_reverse_string(buf, i);
  s21_make_flags(0, s_format, buf);
  s21_make_width(s_format, buf, 0);
}

void s21_un_to_char(FORMAT s_format, unsigned long long int num, char *buf,
                    int *i) {
  int flag = 1;
  while (flag) {
    int digit = 0;
    if (num >= 10) {
      digit = num % 10;
      num = (num - digit) / 10;
    } else {
      digit = num;
      flag = 0;
    }
    buf[*i] = (char)(digit + '0');
    (*i)++;
  }
  if (s_format.precision == 0 && num == 0 && s_format.point) buf[0] = '\0';
  buf[*i] = '\0';
}

// helper funcs
void s21_make_flags(int is_negative, FORMAT s_format, char *buf) {
  int i = 0;
  if (!s21_strchr("scuo\%", s_format.spec)) {
    if (is_negative == 1 || is_negative == 4) {
      s21_move_string(buf);
      buf[i++] = '-';
    } else if (s_format.plus) {
      s21_move_string(buf);
      buf[i] = '+';
    } else if (s_format.space) {
      s21_move_string(buf);
      buf[i] = ' ';
    }
  }
  if (s_format.minus) {
    i = s21_strlen(buf);
    while (i < s_format.width) {
      buf[i++] = ' ';
    }
  }
}

void s21_make_width(FORMAT s_format, char *buf, int is_negative) {
  int len = 0;
  len = s21_strlen(buf);
  len += s_format.error;
  int flag = 1;

  if ((s_format.spec != 'f' && s_format.point) ||
      (s_format.space && !s_format.zero))
    flag = 0;

  if (s_format.width > len) {
    int edge = 0;
    buf[s_format.width + 1] = '\0';
    if (!s21_strchr("scuo\%", s_format.spec) && is_negative < 2) {
      if (flag && s_format.zero) {
        if (is_negative == 1 || s_format.plus || s_format.space) {
          edge++;
        }
      }
    }
    while (len >= edge) {
      buf[s_format.width--] = buf[len--];
    }
    for (; edge <= s_format.width; edge++) {
      if (s21_strchr("diuoxp", s_format.spec)) {
        if (s_format.zero && !s_format.point) {
          buf[edge] = '0';
        } else {
          buf[edge] = ' ';
        }
      }
      if (s21_strchr("fcs", s_format.spec) && is_negative < 3) {
        if (s_format.zero) {
          buf[edge] = '0';
        } else {
          buf[edge] = ' ';
        }
      }
      if (is_negative > 1) {
        buf[edge] = ' ';
      }
    }
  }
}

// format funcs
void s21_c_format(va_list arg_list, FORMAT *s_format, char *buf) {
  buf[0] = va_arg(arg_list, int);
  buf[1] = '\0';
  if (!s21_strlen(buf)) s_format->error++;
  s21_make_flags(0, *s_format, buf);
  s21_make_width(*s_format, buf, 0);
}

void s21_f_format(FORMAT s_format, va_list arg_list, char *buf) {
  if ((s_format.length == 'l' && s_format.double_len) ||
      s_format.length == 'L') {
    long double ld_num = (long double)va_arg(arg_list, long double);
    s21_f_to_str(ld_num, s_format, buf);
  } else {
    double d_num = (double)va_arg(arg_list, double);
    s21_f_to_str(d_num, s_format, buf);
  }
}

void s21_s_format(const FORMAT *s_format, va_list arg_list, char *buf) {
  const char *c_buf = va_arg(arg_list, char *);
  if (c_buf) {
    s21_size_t t_len = s21_strlen(c_buf);
    buf = s21_strncat(buf, c_buf, t_len);
  } else {
    buf = s21_strncat(buf, "(null)", 6);
  }
  int accuracy = 0;
  if (s_format->point) {
    accuracy = s_format->precision;
  } else {
    accuracy = s21_strlen(buf);
  }
  int i = 0;
  for (; i < accuracy; i++)
    ;
  while (buf[i] != '\0') {
    buf[i] = '\0';
    i++;
  }
  s21_make_flags(0, *s_format, buf);
  s21_make_width(*s_format, buf, 0);
}

void s21_d_format(FORMAT s_format, va_list arg_list, char *buf) {
  if (!s_format.length) {
    int num = (int)va_arg(arg_list, int);
    s21_int_to_string(buf, s_format, num);
  } else if (s_format.length == 'l') {
    if (s_format.double_len) {
      long long int ll_num = va_arg(arg_list, long long int);
      s21_int_to_string(buf, s_format, ll_num);
    } else {
      long int l_num = (long int)va_arg(arg_list, long int);
      s21_int_to_string(buf, s_format, l_num);
    }
  } else if (s_format.length == 'h') {
    if (s_format.double_len) {
      signed char hh_num = (signed char)va_arg(arg_list, int);
      s21_int_to_string(buf, s_format, hh_num);
    } else {
      short int h_num = (short int)va_arg(arg_list, int);
      s21_int_to_string(buf, s_format, h_num);
    }
  }
}

void s21_u_format(FORMAT s_format, va_list arg_list, char *buf) {
  if (!s_format.length) {
    unsigned int u_num = (unsigned int)va_arg(arg_list, unsigned int);
    s21_u_to_str(buf, s_format, u_num);
  } else if (s_format.length == 'l') {
    if (s_format.double_len) {
      unsigned long long int ull_num = va_arg(arg_list, unsigned long long int);
      s21_u_to_str(buf, s_format, ull_num);
    } else {
      unsigned long ul_num = (unsigned long)va_arg(arg_list, unsigned long int);
      s21_u_to_str(buf, s_format, ul_num);
    }
  } else if (s_format.length == 'h') {
    if (s_format.double_len) {
      unsigned char uc_num = (unsigned char)va_arg(arg_list, unsigned int);
      s21_u_to_str(buf, s_format, uc_num);
    } else {
      unsigned short us_num = (unsigned short)va_arg(arg_list, unsigned int);
      s21_u_to_str(buf, s_format, us_num);
    }
  }
}

void s21_o_format(FORMAT s_format, va_list input, char *str) {
  unsigned long int ld_num = 0;
  unsigned short int sd_num = 0;
  unsigned int num = 0;

  switch (s_format.length) {
    case 'h':
      sd_num = (unsigned short int)va_arg(input, unsigned int);
      s21_ol_to_str(str, sd_num, s_format);
      break;
    case 'l':
      ld_num = (unsigned long int)va_arg(input, unsigned long int);
      s21_ol_to_str(str, ld_num, s_format);
      break;
    default:
      num = va_arg(input, unsigned int);
      s21_ol_to_str(str, num, s_format);
      break;
  }
}

void s21_x_format(FORMAT s_format, va_list input, char *str) {
  unsigned long int ld_num = 0;
  unsigned int num = 0;

  switch (s_format.length) {
    case 'l':
      ld_num = (unsigned long int)va_arg(input, unsigned long int);
      s21_x_to_str(ld_num, s_format, str);
      break;
    default:
      num = va_arg(input, unsigned int);
      s21_x_to_str(num, s_format, str);
      break;
  }
}

void s21_p_format(FORMAT s_format, va_list input, char *str) {
  void *ptr = (void *)va_arg(input, void *);
  s21_p_to_str(ptr, s_format, str);
}

void s21_e_format(FORMAT s_format, va_list input, char *str) {
  long double value = (long double)va_arg(input, double);
  s21_e_to_str(value, s_format, str);
}

void s21_g_format(FORMAT s_format, va_list input, char *str) {
  long double value = (long double)va_arg(input, double);
  s21_g_to_str(value, s_format, str);
}

void s21_percent_format(FORMAT s_format, char *buf) {
  s21_strncat(buf, "%", 1);
  s21_make_flags(0, s_format, buf);
  s21_make_width(s_format, buf, 0);
}

// Main
void s21_star_into_num(FORMAT *s_format, int *pres_or_width, va_list arg_list) {
  if (*pres_or_width == '*') {
    *pres_or_width = va_arg(arg_list, int);
    if (s_format->width < 0) {
      s_format->width *= -1;
      s_format->minus = 1;
    }
  }
}

void s21_format_string(FORMAT *s_format, va_list arg_list, char *buf) {
  switch (s_format->spec) {
    case 'e':
    case 'E':
      s21_e_format(*s_format, arg_list, buf);
      break;
    case 'g':
    case 'G':
      s21_g_format(*s_format, arg_list, buf);
      break;
    case 'c':
      s21_c_format(arg_list, s_format, buf);
      break;
    case 'f':
      s21_f_format(*s_format, arg_list, buf);
      break;
    case 's':
      s21_s_format(s_format, arg_list, buf);
      break;
    case 'i':
    case 'd':
      s21_d_format(*s_format, arg_list, buf);
      break;
    case 'u':
      s21_u_format(*s_format, arg_list, buf);
      break;
    case 'o':
      s21_o_format(*s_format, arg_list, buf);
      break;
    case 'x':
    case 'X':
      s21_x_format(*s_format, arg_list, buf);
      break;
    case 'p':
      s21_p_format(*s_format, arg_list, buf);
      break;
    case '%':
      s21_percent_format(*s_format, buf);
      break;
    default:
      break;
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int ptr_str = 0;
  int ptr_f = 0;
  int edge = 0;
  int flag = 0;
  s21_strncpy(str, "", 1);
  FORMAT s_format = {0};
  while (format[ptr_f]) {
    if (format[ptr_f] == '%') {
      char *buf = S21_NULL;
      buf = calloc(1000, sizeof(char));
      if (buf) {
        s21_reset_format(&s_format);
        ptr_f = s21_parser(ptr_f, format, &s_format);
        if (s_format.spec) {
          s21_star_into_num(&s_format, &s_format.width, args);
          s21_star_into_num(&s_format, &s_format.precision, args);
          s21_format_string(&s_format, args, buf);
          s21_size_t buf_len = s21_strlen(buf);
          str = s21_strncat(str, buf, buf_len);
          ptr_str = s21_strlen(str);
          if (s_format.error == 1 && !flag) {
            if ((!s_format.zero && s_format.width > 1 && !s_format.minus) ||
                (s_format.zero && !s_format.minus) || !s_format.width) {
              edge = ptr_str;
            }
            flag++;
          }
        }
      }
      free(buf);
    } else {
      str[ptr_str++] = format[ptr_f++];
    }
    str[ptr_str] = '\0';
  }
  va_end(args);
  int bytes = s21_strlen(str);
  if (!(s_format.minus && s_format.width)) bytes += s_format.error;
  if (s_format.error)
    while (ptr_str > edge) str[edge++] = '\0';

  return bytes;
}
