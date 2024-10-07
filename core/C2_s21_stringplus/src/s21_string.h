#ifndef S21_STRING_H
#define S21_STRING_H

#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#ifndef S21_NULL
#define S21_NULL ((void *)0)
#endif

#define s21_INF 1.0 / 0.0

typedef unsigned long s21_size_t;
typedef struct {
  int minus;
  int precision;
  int double_len;
  int spec;
  int length;
  int plus;
  int sharp;
  int zero;
  int point;
  int width;
  int star;
  int space;
  int error;
} FORMAT;

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

int s21_sscanf(const char *str, const char *format, ...);
int s21_sprintf(char *str, const char *format, ...);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

// util functions used by other functions

int s21_contains_char(const char c, const char *str, s21_size_t len);
int s21_normalize(int n);

// custom sprintf:

#define S21_IS_SPEC(ch)                                                       \
  ((ch) == 'c' || (ch) == 'd' || (ch) == 'i' || (ch) == 'f' || (ch) == 's' || \
   (ch) == 'u' || (ch) == '%' || (ch) == 'x' || (ch) == 'X' || (ch) == 'o' || \
   (ch) == 'p' || (ch) == 'n' || (ch) == 'e' || (ch) == 'E' || (ch) == 'g' || \
   (ch) == 'G')

#define S21_IS_LENGTH(ch) ((ch) == 'l' || (ch) == 'h' || (ch) == 'L')
#define S21_IS_NUMERIC(ch) (((ch) <= '9' && (ch) >= '0') || (ch) == '*')

void s21_check_star(FORMAT *s_format, int *pres_or_width, int *num, char f_ch);
int s21_parser(int ptr_f, const char *format, FORMAT *s_format);
int s21_char_to_int(const char *num_str, int *result);
void s21_int_to_char(FORMAT s_format, unsigned long long int num, char *buf,
                     int *i);
void s21_reverse_string(char *str, int i);
void s21_reset_format(FORMAT *s_format);
void s21_move_string(char *buf);
void s21_f_to_str(long double num, FORMAT s_format, char *buf);
void s21_e_to_str(long double num, FORMAT s_format, char *buf);
int s21_is_digit(char c);
void s21_format_g_flags(char *buff, FORMAT s_format);
void s21_format_g_precision(char *buff, int precision);
void s21_g_to_str(long double num, FORMAT s_format, char *buf);
void s21_x_to_str(unsigned long long int num, FORMAT s_format, char *buf);
void s21_p_to_str(void *ptr, FORMAT s_format, char *buf);
void s21_u_to_str(char *buf, FORMAT s_format, unsigned long long int num);
void s21_ol_to_str(char *buf, unsigned long long num, FORMAT s_format);
void s21_un_to_char(FORMAT s_format, unsigned long long int num, char *buf,
                    int *i);
void s21_make_flags(int is_negative, FORMAT s_format, char *buf);
void s21_make_width(FORMAT s_format, char *buf, int is_negative);
void s21_star_into_num(FORMAT *s_format, int *pres_or_width, va_list arg_list);
void s21_format_string(FORMAT *s_format, va_list arg_list, char *buf);
void s21_int_to_string(char *buf, FORMAT s_format, long long int num);
void s21_precision_int(FORMAT s_format, char *buf, int *i);
void s21_c_format(va_list arg_list, FORMAT *s_format, char *buf);
void s21_f_format(FORMAT s_format, va_list arg_list, char *buf);
void s21_s_format(const FORMAT *s_format, va_list arg_list, char *buf);
void s21_d_format(FORMAT s_format, va_list arg_list, char *buf);
void s21_u_format(FORMAT s_format, va_list arg_list, char *buf);
void s21_o_format(FORMAT s_format, va_list input, char *str);
void s21_x_format(FORMAT s_format, va_list input, char *str);
void s21_p_format(FORMAT s_format, va_list input, char *str);
void s21_e_format(FORMAT s_format, va_list input, char *str);
void s21_g_format(FORMAT s_format, va_list input, char *str);
void s21_percent_format(FORMAT s_format, char *buf);

// Custom sscanf:
void s21_custom_atoi(char **src, long *num, int length);
char *s21_get_int(char *src, long *num, int length);
void s21_get_float(char **src, long double *num, int length);
void s21_get_char(char **src, int *c, int length);
void s21_get_octa(char **src, unsigned long *num, int length);
void s21_get_hexa(char **src, unsigned long *num, int length);
void s21_get_ptr(char **src, void **ptr, int length);
void s21_skip_spaces(char **str);
void s21_get_string(char **src, char *dest, int length);
int s21_get_character_index(const char *src, const char c);

#endif
