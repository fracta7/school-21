#include "test_cases.h"

START_TEST(test_sprintf_basic_string) {
  printf("[Running tests for s21_sprintf...]\n");
  char s21_result[100];
  char real_result[100];

  char *input = "Hello, world!";
  int s21 = s21_sprintf(s21_result, "%s", input);
  int real = sprintf(real_result, "%s", input);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_integer) {
  char s21_result[100];
  char real_result[100];

  int num = 42;
  int s21 = s21_sprintf(s21_result, "%d", num);
  int real = sprintf(real_result, "%d", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_integer_with_zero_flag) {
  char s21_result[100];
  char real_result[100];

  int num = 42;

  int s21 = s21_sprintf(s21_result, "%05d", num);
  int real = sprintf(real_result, "%05d", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_integer_i) {
  char s21_result[100];
  char real_result[100];

  int num = 42;
  int s21 = s21_sprintf(s21_result, "%i", num);
  int real = sprintf(real_result, "%i", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_float) {
  char s21_result[100];
  char real_result[100];

  float num = 3.1415;
  int s21 = s21_sprintf(s21_result, "%.2f", num);
  int real = sprintf(real_result, "%.2f", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_integer_width) {
  char s21_result[100];
  char real_result[100];

  int num = 42;
  int s21 = s21_sprintf(s21_result, "%6d", num);
  int real = sprintf(real_result, "%6d", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_mixed) {
  char s21_result[100];
  char real_result[100];

  int num = 123;
  char *str = "Test";
  float f_num = 45.678;

  int s21 = s21_sprintf(s21_result, "String: %s, Integer: %d, Float: %.1f", str,
                        num, f_num);
  int real = sprintf(real_result, "String: %s, Integer: %d, Float: %.1f", str,
                     num, f_num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_char) {
  char s21_result[100];
  char real_result[100];

  char c = 'A';
  int s21 = s21_sprintf(s21_result, "%c", c);
  int real = sprintf(real_result, "%c", c);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char s21_result[100];
  char real_result[100];

  int s21 = s21_sprintf(s21_result, "%%");
  int real = sprintf(real_result, "%%");

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_unsigned) {
  char s21_result[100];
  char real_result[100];

  unsigned int num = 4294967295;  // Maximum value for a 32-bit unsigned int
  int s21 = s21_sprintf(s21_result, "%u", num);
  int real = sprintf(real_result, "%u", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for a combination of %u and %d
START_TEST(test_sprintf_combined_unsigned) {
  char s21_result[100];
  char real_result[100];

  unsigned int u_num = 100;
  int num = -50;

  int s21 = s21_sprintf(s21_result, "Unsigned: %u, Signed: %d", u_num, num);
  int real = sprintf(real_result, "Unsigned: %u, Signed: %d", u_num, num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for a combination of %u and %n
START_TEST(test_sprintf_combined_unsigned_and_n) {
  char s21_result[100];
  char real_result[100];
  unsigned int u_num = 256;
  int s21_written = 0;
  int real_written = 0;

  int s21 = s21_sprintf(s21_result, "Number: %u%n", u_num, &s21_written);
  int real = sprintf(real_result, "Number: %u%n", u_num, &real_written);

  // Check that the strings are equal
  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %o (octal)
START_TEST(test_sprintf_octal) {
  char s21_result[100];
  char real_result[100];

  unsigned int num = 511;  // This will be represented as "777" in octal
  int s21 = s21_sprintf(s21_result, "%o", num);
  int real = sprintf(real_result, "%o", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %lo (long octal)
START_TEST(test_sprintf_long_octal) {
  char s21_result[100];
  char real_result[100];

  unsigned long num = 65535;  // This will be represented in octal as "177777"
  int s21 = s21_sprintf(s21_result, "%lo", num);
  int real = sprintf(real_result, "%lo", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for a combination of %o and %d
START_TEST(test_sprintf_combined_octal) {
  char s21_result[100];
  char real_result[100];

  unsigned int octal_num = 123;
  int decimal_num = -456;

  int s21 =
      s21_sprintf(s21_result, "Octal: %o, Decimal: %d", octal_num, decimal_num);
  int real =
      sprintf(real_result, "Octal: %o, Decimal: %d", octal_num, decimal_num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %lo and %ld combination
START_TEST(test_sprintf_combined_long_octal) {
  char s21_result[100];
  char real_result[100];

  unsigned long long_octal_num = 12345;
  long long_decimal_num = -6789;

  int s21 = s21_sprintf(s21_result, "Long Octal: %lo, Long Decimal: %ld",
                        long_octal_num, long_decimal_num);
  int real = sprintf(real_result, "Long Octal: %lo, Long Decimal: %ld",
                     long_octal_num, long_decimal_num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for octal edge case (zero)
START_TEST(test_sprintf_octal_zero) {
  char s21_result[100];
  char real_result[100];

  unsigned int num = 0;  // Octal for 0 is still "0"
  int s21 = s21_sprintf(s21_result, "%o", num);
  int real = sprintf(real_result, "%o", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for long octal edge case (large value)
START_TEST(test_sprintf_long_octal_large_value) {
  char s21_result[100];
  char real_result[100];

  unsigned long num = 4294967295;  // Maximum value for 32-bit unsigned long,
                                   // octal "37777777777"
  int s21 = s21_sprintf(s21_result, "%lo", num);
  int real = sprintf(real_result, "%lo", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %ld (long decimal)
START_TEST(test_sprintf_long_decimal) {
  char s21_result[100];
  char real_result[100];

  long num = 1234567890L;  // Long decimal value
  int s21 = s21_sprintf(s21_result, "%ld", num);
  int real = sprintf(real_result, "%ld", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %hd (short decimal)
START_TEST(test_sprintf_short_decimal) {
  char s21_result[100];
  char real_result[100];

  short num = 12345;  // Short decimal value
  int s21 = s21_sprintf(s21_result, "%hd", num);
  int real = sprintf(real_result, "%hd", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %lu (unsigned long)
START_TEST(test_sprintf_unsigned_long) {
  char s21_result[100];
  char real_result[100];

  unsigned long num = 123456789UL;  // Unsigned long value
  int s21 = s21_sprintf(s21_result, "%lu", num);
  int real = sprintf(real_result, "%lu", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %hu (unsigned short)
START_TEST(test_sprintf_unsigned_short) {
  char s21_result[100];
  char real_result[100];

  unsigned short num = 65535;  // Unsigned short max value
  int s21 = s21_sprintf(s21_result, "%hu", num);
  int real = sprintf(real_result, "%hu", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %lf (double)
START_TEST(test_sprintf_double) {
  char s21_result[100];
  char real_result[100];

  double num = 12345.6789;  // Double value
  int s21 = s21_sprintf(s21_result, "%lf", num);
  int real = sprintf(real_result, "%lf", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_long_double) {
  char s21_result[100];
  char real_result[100];

  long double num = 12345.6789;  // Double value
  int s21 = s21_sprintf(s21_result, "%Lf", num);
  int real = sprintf(real_result, "%Lf", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %hd (short edge case)
START_TEST(test_sprintf_short_edge_case) {
  char s21_result[100];
  char real_result[100];

  short num = -32768;  // Minimum short value
  int s21 = s21_sprintf(s21_result, "%hd", num);
  int real = sprintf(real_result, "%hd", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %ld (long negative value)
START_TEST(test_sprintf_long_negative) {
  char s21_result[100];
  char real_result[100];

  long num = -9876543210L;  // Negative long value
  int s21 = s21_sprintf(s21_result, "%ld", num);
  int real = sprintf(real_result, "%ld", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for dynamic width with %d
START_TEST(test_sprintf_dynamic_width_decimal) {
  char s21_result[100];
  char real_result[100];

  int width = 10;
  int num = 42;

  int s21 = s21_sprintf(s21_result, "%*d", width, num);
  int real = sprintf(real_result, "%*d", width, num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for dynamic precision with %f
START_TEST(test_sprintf_dynamic_precision_float) {
  char s21_result[100];
  char real_result[100];

  double num = 123.456789;
  int precision = 4;

  int s21 = s21_sprintf(s21_result, "%.*f", precision, num);
  int real = sprintf(real_result, "%.*f", precision, num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for dynamic width and precision with %s
START_TEST(test_sprintf_dynamic_width_precision_string) {
  char s21_result[100];
  char real_result[100];

  char *str = "hello";
  int width = 10;
  int precision = 3;

  int s21 = s21_sprintf(s21_result, "%*.*s", width, precision, str);
  int real = sprintf(real_result, "%*.*s", width, precision, str);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for dynamic width with %x (hexadecimal)
START_TEST(test_sprintf_dynamic_width_hex) {
  char s21_result[100];
  char real_result[100];

  unsigned int num = 255;
  int width = 6;

  int s21 = s21_sprintf(s21_result, "%*x", width, num);
  int real = sprintf(real_result, "%*x", width, num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for negative dynamic width with %d
START_TEST(test_sprintf_negative_width_decimal) {
  char s21_result[100];
  char real_result[100];

  int num = 42;
  int width = -10;

  int s21 = s21_sprintf(s21_result, "%*d", width, num);
  int real = sprintf(real_result, "%*d", width, num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for dynamic width and precision with %f (float)
START_TEST(test_sprintf_dynamic_width_precision_float) {
  char s21_result[100];
  char real_result[100];

  double num = 123.456789;
  int width = 10;
  int precision = 5;

  int s21 = s21_sprintf(s21_result, "%*.*f", width, precision, num);
  int real = sprintf(real_result, "%*.*f", width, precision, num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for %hd (short edge case)
START_TEST(test_sprintf_short) {
  char s21_result[100];
  char real_result[100];

  unsigned short num = 1;  // Minimum short value
  int s21 = s21_sprintf(s21_result, "  %ho", num);
  int real = sprintf(real_result, "  %ho", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for positive sign with %d
START_TEST(test_sprintf_plus_sign_decimal) {
  char s21_result[100];
  char real_result[100];

  int num = 42;

  int s21 = s21_sprintf(s21_result, "%+d", num);
  int real = sprintf(real_result, "%+d", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for negative sign with %d
START_TEST(test_sprintf_negative_sign_decimal) {
  char s21_result[100];
  char real_result[100];

  int num = -42;

  int s21 = s21_sprintf(s21_result, "%+d", num);
  int real = sprintf(real_result, "%+d", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for space with %d
START_TEST(test_sprintf_space_sign_decimal) {
  char s21_result[100];
  char real_result[100];

  int num = 42;

  int s21 = s21_sprintf(s21_result, "% d", num);
  int real = sprintf(real_result, "% d", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for positive sign with %f
START_TEST(test_sprintf_plus_sign_float) {
  char s21_result[100];
  char real_result[100];

  double num = 42.5;

  int s21 = s21_sprintf(s21_result, "%+f", num);
  int real = sprintf(real_result, "%+f", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for negative sign with %f
START_TEST(test_sprintf_negative_sign_float) {
  char s21_result[100];
  char real_result[100];

  double num = -42.5;

  int s21 = s21_sprintf(s21_result, "%+f", num);
  int real = sprintf(real_result, "%+f", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for space with %f
START_TEST(test_sprintf_space_sign_float) {
  char s21_result[100];
  char real_result[100];

  double num = 42.5;

  int s21 = s21_sprintf(s21_result, "% f", num);
  int real = sprintf(real_result, "% f", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for mixed sign with %d
START_TEST(test_sprintf_mixed_signs) {
  char s21_result[100];
  char real_result[100];

  int pos_num = 42;
  int neg_num = -42;

  int s21 = s21_sprintf(s21_result, "%+d %+d", pos_num, neg_num);
  int real = sprintf(real_result, "%+d %+d", pos_num, neg_num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_minus) {
  char s21_result[100];
  char real_result[100];

  int pos_num = 42;
  int neg_num = -42;

  int s21 = s21_sprintf(s21_result, "%-d %-d", pos_num, neg_num);
  int real = sprintf(real_result, "%-d %-d", pos_num, neg_num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for hexadecimal with # flag
// Test case for lowercase hexadecimal without # flag
START_TEST(test_sprintf_hex_no_hash) {
  char s21_result[100];
  char real_result[100];

  int num = 42;

  int s21 = s21_sprintf(s21_result, "%x", num);
  int real = sprintf(real_result, "%x", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for lowercase hexadecimal with # flag
START_TEST(test_sprintf_hex_with_hash) {
  char s21_result[100];
  char real_result[100];

  int num = 42;

  int s21 = s21_sprintf(s21_result, "%#x", num);
  int real = sprintf(real_result, "%#x", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for uppercase hexadecimal without # flag
START_TEST(test_sprintf_hex_uppercase_no_hash) {
  char s21_result[100];
  char real_result[100];

  int num = 42;

  int s21 = s21_sprintf(s21_result, "%X", num);
  int real = sprintf(real_result, "%X", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for uppercase hexadecimal with # flag
START_TEST(test_sprintf_hex_uppercase_with_hash) {
  char s21_result[100];
  char real_result[100];

  int num = 42;

  int s21 = s21_sprintf(s21_result, "%#X", num);
  int real = sprintf(real_result, "%#X", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for zero value with lowercase hexadecimal and # flag
START_TEST(test_sprintf_hex_zero_with_hash) {
  char s21_result[100];
  char real_result[100];

  int num = 0;

  int s21 = s21_sprintf(s21_result, "%#x", num);
  int real = sprintf(real_result, "%#x", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for zero value with uppercase hexadecimal and # flag
START_TEST(test_sprintf_hex_uppercase_zero_with_hash) {
  char s21_result[100];
  char real_result[100];

  int num = 0;

  int s21 = s21_sprintf(s21_result, "%#X", num);
  int real = sprintf(real_result, "%#X", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_l_hex) {
  char s21_result[100];
  char real_result[100];

  unsigned long num = 12345678910111213;

  int s21 = s21_sprintf(s21_result, "%lX", num);
  int real = sprintf(real_result, "%lX", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for octal with # flag
START_TEST(test_sprintf_octal_with_hash) {
  char s21_result[100];
  char real_result[100];

  int num = 42;

  int s21 = s21_sprintf(s21_result, "%#o", num);
  int real = sprintf(real_result, "%#o", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for floating-point with # flag
START_TEST(test_sprintf_float_with_hash) {
  char s21_result[100];
  char real_result[100];

  double num = 42.0;

  int s21 = s21_sprintf(s21_result, "%#f", num);
  int real = sprintf(real_result, "%#f", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for floating-point with # flag (no digits after decimal)
START_TEST(test_sprintf_float_with_hash_no_decimal) {
  char s21_result[100];
  char real_result[100];

  double num = 42.0;

  int s21 = s21_sprintf(s21_result, "%#g", num);
  int real = sprintf(real_result, "%#g", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

// Test case for floating-point with # flag and no digits
START_TEST(test_sprintf_float_with_hash_no_digits) {
  char s21_result[100];
  char real_result[100];

  double num = 42.0;

  int s21 = s21_sprintf(s21_result, "%#.0f", num);
  int real = sprintf(real_result, "%#.0f", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_exponent) {
  char s21_result[100];
  char real_result[100];

  double num = 12345.6789;

  int s21 = s21_sprintf(s21_result, "%+e", num);
  int real = sprintf(real_result, "%+e", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_exponent_upper) {
  char s21_result[100];
  char real_result[100];

  double num = 0.06789;

  int s21 = s21_sprintf(s21_result, "%+E", num);
  int real = sprintf(real_result, "%+E", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_exponent_precision) {
  char s21_result[100];
  char real_result[100];

  double num = 12345.6789;

  int s21 = s21_sprintf(s21_result, "%+5e", num);
  int real = sprintf(real_result, "%+5e", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_g_exponent) {
  char s21_result[100];
  char real_result[100];

  double num = 12345.6789;

  int s21 = s21_sprintf(s21_result, "%3g", num);
  int real = sprintf(real_result, "%3g", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_g_exponent_large) {
  char s21_result[100];
  char real_result[100];

  double num = 123456.789;

  int s21 = s21_sprintf(s21_result, "%g", num);
  int real = sprintf(real_result, "%g", num);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_pointer) {
  char s21_result[100];
  char real_result[100];

  int num = 42;
  void *ptr = &num;

  // Use %p to print the pointer address
  int s21 = s21_sprintf(s21_result, "%p", ptr);
  int real = sprintf(real_result, "%p", ptr);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_null_pointer) {
  char s21_result[100];
  char real_result[100];
  void *ptr = NULL;

  // Use %p to print the pointer address
  int s21 = s21_sprintf(s21_result, "%p", ptr);
  int real = sprintf(real_result, "%p", ptr);

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_null) {
  char s21_result[100];
  char real_result[100];

  // Use %p to print the pointer address
  int s21 = s21_sprintf(s21_result, " ");
  int real = sprintf(real_result, " ");

  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_sprintf_hash_flag) {
  char s21_result[100];
  char real_result[100];

  // Test for octal with # flag
  int num_octal = 10;
  int s21 = s21_sprintf(s21_result, "%#o", num_octal);
  int real = sprintf(real_result, "%#o", num_octal);
  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);

  // Test for lowercase hexadecimal with # flag
  unsigned int num_hex_lower = 255;
  s21 = s21_sprintf(s21_result, "%#x", num_hex_lower);
  real = sprintf(real_result, "%#x", num_hex_lower);
  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);

  // Test for uppercase hexadecimal with # flag
  s21 = s21_sprintf(s21_result, "%#X", num_hex_lower);
  real = sprintf(real_result, "%#X", num_hex_lower);
  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);

  // Test for float with # flag
  double num_float = 3.14;
  s21 = s21_sprintf(s21_result, "%#f", num_float);
  real = sprintf(real_result, "%#f", num_float);
  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);

  // Test for float with # flag and zero decimal places
  s21 = s21_sprintf(s21_result, "%#.0f", num_float);
  real = sprintf(real_result, "%#.0f", num_float);
  ck_assert_str_eq(s21_result, real_result);
  ck_assert_int_eq(s21, real);
}
END_TEST

TCase *test_sprintf(void) {
  TCase *tc = tcase_create("sprintf");

  tcase_add_test(tc, test_sprintf_basic_string);
  tcase_add_test(tc, test_sprintf_integer);
  tcase_add_test(tc, test_sprintf_integer_i);
  tcase_add_test(tc, test_sprintf_integer_width);
  tcase_add_test(tc, test_sprintf_integer_with_zero_flag);
  tcase_add_test(tc, test_sprintf_float);
  tcase_add_test(tc, test_sprintf_mixed);
  tcase_add_test(tc, test_sprintf_char);
  tcase_add_test(tc, test_sprintf_percent);
  tcase_add_test(tc, test_sprintf_unsigned);
  tcase_add_test(tc, test_sprintf_combined_unsigned);
  tcase_add_test(tc, test_sprintf_combined_unsigned_and_n);
  tcase_add_test(tc, test_sprintf_octal);
  tcase_add_test(tc, test_sprintf_long_octal);
  tcase_add_test(tc, test_sprintf_combined_octal);
  tcase_add_test(tc, test_sprintf_combined_long_octal);
  tcase_add_test(tc, test_sprintf_octal_zero);
  tcase_add_test(tc, test_sprintf_long_octal_large_value);
  tcase_add_test(tc, test_sprintf_long_decimal);
  tcase_add_test(tc, test_sprintf_short_decimal);
  tcase_add_test(tc, test_sprintf_unsigned_long);
  tcase_add_test(tc, test_sprintf_unsigned_short);
  tcase_add_test(tc, test_sprintf_double);
  tcase_add_test(tc, test_sprintf_long_double);
  tcase_add_test(tc, test_sprintf_short_edge_case);
  tcase_add_test(tc, test_sprintf_long_negative);
  tcase_add_test(tc, test_sprintf_dynamic_width_decimal);
  tcase_add_test(tc, test_sprintf_dynamic_precision_float);
  tcase_add_test(tc, test_sprintf_dynamic_width_precision_string);
  tcase_add_test(tc, test_sprintf_dynamic_width_hex);
  tcase_add_test(tc, test_sprintf_negative_width_decimal);
  tcase_add_test(tc, test_sprintf_dynamic_width_precision_float);
  tcase_add_test(tc, test_sprintf_short);
  tcase_add_test(tc, test_sprintf_plus_sign_decimal);
  tcase_add_test(tc, test_sprintf_negative_sign_decimal);
  tcase_add_test(tc, test_sprintf_space_sign_decimal);
  tcase_add_test(tc, test_sprintf_plus_sign_float);
  tcase_add_test(tc, test_sprintf_negative_sign_float);
  tcase_add_test(tc, test_sprintf_space_sign_float);
  tcase_add_test(tc, test_sprintf_mixed_signs);
  tcase_add_test(tc, test_sprintf_hex_with_hash);
  tcase_add_test(tc, test_sprintf_hex_uppercase_with_hash);
  tcase_add_test(tc, test_sprintf_octal_with_hash);
  tcase_add_test(tc, test_sprintf_float_with_hash);
  tcase_add_test(tc, test_sprintf_float_with_hash_no_decimal);
  tcase_add_test(tc, test_sprintf_float_with_hash_no_digits);
  tcase_add_test(tc, test_sprintf_exponent);
  tcase_add_test(tc, test_sprintf_exponent_upper);
  tcase_add_test(tc, test_sprintf_exponent_precision);
  tcase_add_test(tc, test_sprintf_g_exponent);
  tcase_add_test(tc, test_sprintf_g_exponent_large);
  tcase_add_test(tc, test_sprintf_pointer);
  tcase_add_test(tc, test_sprintf_null_pointer);
  tcase_add_test(tc, test_sprintf_hash_flag);
  tcase_add_test(tc, test_sprintf_hex_uppercase_zero_with_hash);
  tcase_add_test(tc, test_sprintf_hex_zero_with_hash);
  tcase_add_test(tc, test_sprintf_hex_uppercase_no_hash);
  tcase_add_test(tc, test_sprintf_hex_no_hash);
  tcase_add_test(tc, test_sprintf_l_hex);
  tcase_add_test(tc, test_sprintf_minus);
  tcase_add_test(tc, test_sprintf_null);

  return tc;
}
