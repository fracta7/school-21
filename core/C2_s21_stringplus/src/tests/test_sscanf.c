#include "test_cases.h"

START_TEST(test_sscanf_basic_string) {
  printf("[Running tests for s21_sscanf...]\n");
  const char buffer[] = "Hello World";
  char real_result[100];
  char s21_result[100];

  sscanf(buffer, "%15s", real_result);
  s21_sscanf(buffer, "%15s", s21_result);

  ck_assert_str_eq(real_result, s21_result);
}
END_TEST

START_TEST(test_sscanf_integer) {
  const char buffer[] = "42";
  int real_value;
  int s21_value;

  sscanf(buffer, "%d", &real_value);
  s21_sscanf(buffer, "%d", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_float) {
  const char buffer[] = "3.14159";
  float real_value;
  float s21_value;

  sscanf(buffer, "%f", &real_value);
  s21_sscanf(buffer, "%f", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_mixed) {
  const char buffer[] = "42 Hello 3.14";

  int real_int_value;
  char real_str_value[100];
  float real_float_value;

  int s21_int_value;
  char s21_str_value[100];
  float s21_float_value;

  sscanf(buffer, "%d %10s %f", &real_int_value, real_str_value,
         &real_float_value);
  s21_sscanf(buffer, "%d %10s %f", &s21_int_value, s21_str_value,
             &s21_float_value);

  ck_assert_int_eq(real_int_value, s21_int_value);
  ck_assert_str_eq(real_str_value, s21_str_value);
  ck_assert_float_eq_tol(real_float_value, s21_float_value, 0.001);
}
END_TEST

START_TEST(test_sscanf_char) {
  const char buffer[] = "H";
  char real_result;
  char s21_result;

  sscanf(buffer, "%c", &real_result);
  s21_sscanf(buffer, "%c", &s21_result);

  ck_assert_int_eq(real_result, s21_result);
}
END_TEST

START_TEST(test_sscanf_percent) {
  const char buffer[] = "100%";
  int real_value;
  int s21_value;

  sscanf(buffer, "%d%%", &real_value);
  s21_sscanf(buffer, "%d%%", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_unsigned) {
  const char buffer[] = "42";
  unsigned int real_value;
  unsigned int s21_value;

  sscanf(buffer, "%u", &real_value);
  s21_sscanf(buffer, "%u", &s21_value);

  ck_assert_uint_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_combined_unsigned) {
  const char buffer[] = "42 100";
  unsigned int r_value1, r_value2;
  unsigned int s_value1, s_value2;

  sscanf(buffer, "%u %u", &r_value1, &r_value2);
  s21_sscanf(buffer, "%u %u", &s_value1, &s_value2);

  ck_assert_uint_eq(r_value1, s_value1);
  ck_assert_uint_eq(r_value2, s_value2);
}
END_TEST

START_TEST(test_sscanf_n_characters_written) {
  const char buffer[] = "42";
  int r_value, r_num_chars;
  int s_value, s_num_chars;

  sscanf(buffer, "%d%n", &r_value, &r_num_chars);
  s21_sscanf(buffer, "%d%n", &s_value, &s_num_chars);

  ck_assert_int_eq(r_value, s_value);
  ck_assert_int_eq(r_num_chars, r_num_chars);
}
END_TEST

START_TEST(test_sscanf_octal) {
  const char buffer[] = "052";
  unsigned int real_value;
  unsigned int s21_value;

  sscanf(buffer, "%o", &real_value);
  s21_sscanf(buffer, "%o", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_long_octal) {
  const char buffer[] = "01234567";
  unsigned long real_value;
  unsigned long s21_value;

  sscanf(buffer, "%lo", &real_value);
  s21_sscanf(buffer, "%lo", &s21_value);

  ck_assert_int_eq(real_value, s21_value);  // Octal input
}
END_TEST

START_TEST(test_sscanf_combined_octal) {
  const char buffer[] = "052 070";
  unsigned int r_value1, r_value2;
  unsigned int s_value1, s_value2;

  sscanf(buffer, "%o %o", &r_value1, &r_value2);
  s21_sscanf(buffer, "%o %o", &s_value1, &s_value2);

  ck_assert_int_eq(r_value1, s_value1);
  ck_assert_int_eq(r_value2, s_value2);
}
END_TEST

START_TEST(test_sscanf_dynamic_width_decimal) {
  const char buffer[] = "12345";
  int real_value;
  int s21_value;

  sscanf(buffer, "%3d", &real_value);
  s21_sscanf(buffer, "%3d", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_dynamic_precision_float) {
  const char buffer[] = "3.14159";
  float real_value;
  float s21_value;

  sscanf(buffer, "%5f", &real_value);
  s21_sscanf(buffer, "%5f", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.0001);
}
END_TEST

START_TEST(test_sscanf_negative_width_decimal) {
  const char buffer[] = "12345";
  int real_value;
  int s21_value;

  sscanf(buffer, "%3d", &real_value);
  s21_sscanf(buffer, "%3d", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_short) {
  const char buffer[] = "12345";
  short real_value;
  short s21_value;

  sscanf(buffer, "%hd", &real_value);
  s21_sscanf(buffer, "%hd", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_plus_sign_decimal) {
  const char buffer[] = "+123";
  int real_value;
  int s21_value;

  sscanf(buffer, "%d", &real_value);
  s21_sscanf(buffer, "%d", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_negative_sign_decimal) {
  const char buffer[] = "-123";
  int real_value;
  int s21_value;

  sscanf(buffer, "%d", &real_value);
  s21_sscanf(buffer, "%d", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_space_sign_decimal) {
  const char buffer[] = " 123";
  int real_value;
  int s21_value;

  sscanf(buffer, "%d", &real_value);
  s21_sscanf(buffer, "%d", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_plus_sign_float) {
  const char buffer[] = "+3.14";
  float real_value;
  float s21_value;

  sscanf(buffer, "%f", &real_value);
  s21_sscanf(buffer, "%f", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_negative_sign_float) {
  const char buffer[] = "-3.14";
  float real_value;
  float s21_value;

  sscanf(buffer, "%f", &real_value);
  s21_sscanf(buffer, "%f", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_mixed_signs) {
  const char buffer[] = "+123 -456 78";
  int r_value1, r_value2, r_value3;
  int s_value1, s_value2, s_value3;

  sscanf(buffer, "%d %d %d", &r_value1, &r_value2, &r_value3);
  s21_sscanf(buffer, "%d %d %d", &s_value1, &s_value2, &s_value3);

  ck_assert_int_eq(r_value1, s_value1);
  ck_assert_int_eq(r_value2, s_value2);
  ck_assert_int_eq(r_value3, s_value3);
}
END_TEST

START_TEST(test_sscanf_octal_with_hash) {
  const char buffer[] = "052";
  unsigned int real_value;
  unsigned int s21_value;

  sscanf(buffer, "%o", &real_value);
  s21_sscanf(buffer, "%o", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_float_with_hash) {
  const char buffer[] = "3.14159";
  float real_value;
  float s21_value;

  sscanf(buffer, "%f", &real_value);
  s21_sscanf(buffer, "%f", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_float_with_hash_no_digits) {
  const char buffer[] = "3.";
  float real_value;
  float s21_value;

  sscanf(buffer, "%f", &real_value);
  s21_sscanf(buffer, "%f", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_suppress_assignment) {
  const char buffer[] = "12345 67890";
  int real_value;
  int s21_value;

  sscanf(buffer, "%*d %d", &real_value);
  s21_sscanf(buffer, "%*d %d", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_hex_with_hash) {
  const char buffer[] = "0x1A3";
  unsigned int real_value;
  unsigned int s21_value;

  sscanf(buffer, "%x", &real_value);
  s21_sscanf(buffer, "%x", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_float_with_precision) {
  const char buffer[] = "123.45678";
  float real_value;
  float s21_value;

  sscanf(buffer, "%7f", &real_value);
  s21_sscanf(buffer, "%7f", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_scientific_lowercase_e) {
  const char buffer[] = "3.14e+2";
  double real_value;
  double s21_value;

  sscanf(buffer, "%le", &real_value);
  s21_sscanf(buffer, "%le", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_scientific_uppercase_E) {
  const char buffer[] = "2.71E+3";
  double real_value;
  double s21_value;

  sscanf(buffer, "%lE", &real_value);
  s21_sscanf(buffer, "%lE", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_scientific_negative_exponent) {
  const char buffer[] = "6.022e-23";
  double real_value;
  double s21_value;

  sscanf(buffer, "%le", &real_value);
  s21_sscanf(buffer, "%le", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_scientific_zero_exponent) {
  const char buffer[] = "9.81E+0";
  double real_value;
  double s21_value;

  sscanf(buffer, "%lE", &real_value);
  s21_sscanf(buffer, "%lE", &s21_value);

  ck_assert_float_eq_tol(real_value, s21_value, 0.00001);
}
END_TEST

START_TEST(test_sscanf_integer_auto_base_decimal) {
  const char buffer[] = "123";
  int real_value;
  int s21_value;

  sscanf(buffer, "%i", &real_value);
  s21_sscanf(buffer, "%i", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_integer_auto_base_octal) {
  const char buffer[] = "0123";
  int real_value;
  int s21_value;

  sscanf(buffer, "%i", &real_value);
  s21_sscanf(buffer, "%i", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_integer_auto_base_hexadecimal) {
  const char buffer[] = "0x7B";
  int real_value;
  int s21_value;

  sscanf(buffer, "%i", &real_value);
  s21_sscanf(buffer, "%i", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_pointer) {
  char buffer[100];
  void *real_value;
  void *s21_value;

  sprintf(buffer, "%p", (void *)0x12345);

  sscanf(buffer, "%p", &real_value);
  s21_sscanf(buffer, "%p", &s21_value);

  ck_assert_ptr_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_integer_auto_base_negative) {
  const char buffer[] = "-456";
  int real_value;
  int s21_value;

  sscanf(buffer, "%i", &real_value);
  s21_sscanf(buffer, "%i", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_integer_auto_base_positive) {
  const char buffer[] = "+789";
  int real_value;
  int s21_value;

  sscanf(buffer, "%i", &real_value);
  s21_sscanf(buffer, "%i", &s21_value);

  ck_assert_int_eq(real_value, s21_value);
}
END_TEST

START_TEST(test_sscanf_long_double_basic) {
  const char buffer[] = "3.141592653589793238462643383279";
  long double real_value;
  long double s21_value;

  sscanf(buffer, "%Lf", &real_value);
  s21_sscanf(buffer, "%Lf", &s21_value);

  ck_assert_ldouble_eq_tol(real_value, s21_value, 1e-15);
}
END_TEST

START_TEST(test_sscanf_long_double_scientific) {
  const char buffer[] = "1.23e+20";
  long double real_value;
  long double s21_value;

  sscanf(buffer, "%Le", &real_value);
  s21_sscanf(buffer, "%Le", &s21_value);

  ck_assert_ldouble_eq_tol(real_value, s21_value, 1e-19);
}
END_TEST

START_TEST(test_sscanf_double_scientific) {
  const char buffer[] = "1.23e+04";
  double real_value;
  double s21_value;

  sscanf(buffer, "%le", &real_value);
  s21_sscanf(buffer, "%le", &s21_value);

  ck_assert_double_eq_tol(real_value, s21_value, 1e-05);
}
END_TEST

START_TEST(test_sscanf_long_double_negative) {
  const char buffer[] = "-12345.67890";
  long double real_value;
  long double s21_value;

  sscanf(buffer, "%Lf", &real_value);
  s21_sscanf(buffer, "%Lf", &s21_value);

  ck_assert_ldouble_eq_tol(real_value, s21_value, 1e-15);
}
END_TEST

START_TEST(test_sscanf_long_double_zero) {
  const char buffer[] = "0.0";
  long double real_value;
  long double s21_value;

  sscanf(buffer, "%Lf", &real_value);
  s21_sscanf(buffer, "%Lf", &s21_value);

  ck_assert_ldouble_eq_tol(real_value, s21_value, 1e-15);
}
END_TEST

START_TEST(test_sscanf_long_double_large) {
  const char buffer[] = "98765432109876543210.0";
  long double real_value;
  long double s21_value;

  sscanf(buffer, "%Lf", &real_value);
  s21_sscanf(buffer, "%Lf", &s21_value);

  ck_assert_ldouble_eq_tol(real_value, s21_value, 1e-25);
}
END_TEST

START_TEST(test_sscanf_long_double_small) {
  const char buffer[] = "1.2345678901234567890123456789e-30";
  long double real_value;
  long double s21_value;

  sscanf(buffer, "%Lf", &real_value);
  s21_sscanf(buffer, "%Lf", &s21_value);

  ck_assert_ldouble_eq_tol(real_value, s21_value, 1e-15);
}
END_TEST

START_TEST(test_sscanf_floating_g) {
  const char input[] = "123.456";
  double s21_num = 0.0;
  double real_num = 0.0;

  s21_sscanf(input, "%lg", &s21_num);
  sscanf(input, "%lg", &real_num);

  ck_assert_double_eq_tol(s21_num, real_num, 1e-6);
}
END_TEST

START_TEST(test_sscanf_floating_G) {
  const char input[] = "1.23456E2";
  double s21_num = 0.0;
  double real_num = 0.0;

  s21_sscanf(input, "%lG", &s21_num);
  sscanf(input, "%lG", &real_num);

  ck_assert_double_eq_tol(s21_num, real_num, 1e-6);
}
END_TEST

TCase *test_sscanf(void) {
  TCase *tc = tcase_create("sscanf");

  tcase_add_test(tc, test_sscanf_basic_string);
  tcase_add_test(tc, test_sscanf_integer);
  tcase_add_test(tc, test_sscanf_float);
  tcase_add_test(tc, test_sscanf_mixed);
  tcase_add_test(tc, test_sscanf_char);
  tcase_add_test(tc, test_sscanf_percent);
  tcase_add_test(tc, test_sscanf_unsigned);
  tcase_add_test(tc, test_sscanf_combined_unsigned);
  tcase_add_test(tc, test_sscanf_n_characters_written);
  tcase_add_test(tc, test_sscanf_octal);
  tcase_add_test(tc, test_sscanf_long_octal);
  tcase_add_test(tc, test_sscanf_combined_octal);
  tcase_add_test(tc, test_sscanf_dynamic_width_decimal);
  tcase_add_test(tc, test_sscanf_dynamic_precision_float);
  tcase_add_test(tc, test_sscanf_negative_width_decimal);
  tcase_add_test(tc, test_sscanf_short);
  tcase_add_test(tc, test_sscanf_plus_sign_decimal);
  tcase_add_test(tc, test_sscanf_plus_sign_float);
  tcase_add_test(tc, test_sscanf_negative_sign_float);
  tcase_add_test(tc, test_sscanf_mixed_signs);
  tcase_add_test(tc, test_sscanf_octal_with_hash);
  tcase_add_test(tc, test_sscanf_float_with_hash);
  tcase_add_test(tc, test_sscanf_float_with_hash_no_digits);
  tcase_add_test(tc, test_sscanf_space_sign_decimal);
  tcase_add_test(tc, test_sscanf_negative_sign_decimal);
  tcase_add_test(tc, test_sscanf_suppress_assignment);
  tcase_add_test(tc, test_sscanf_hex_with_hash);
  tcase_add_test(tc, test_sscanf_float_with_precision);
  tcase_add_test(tc, test_sscanf_scientific_lowercase_e);
  tcase_add_test(tc, test_sscanf_scientific_uppercase_E);
  tcase_add_test(tc, test_sscanf_scientific_negative_exponent);
  tcase_add_test(tc, test_sscanf_scientific_zero_exponent);
  tcase_add_test(tc, test_sscanf_integer_auto_base_decimal);
  tcase_add_test(tc, test_sscanf_integer_auto_base_octal);
  tcase_add_test(tc, test_sscanf_integer_auto_base_hexadecimal);
  tcase_add_test(tc, test_sscanf_pointer);
  tcase_add_test(tc, test_sscanf_integer_auto_base_negative);
  tcase_add_test(tc, test_sscanf_integer_auto_base_positive);
  tcase_add_test(tc, test_sscanf_long_double_basic);
  tcase_add_test(tc, test_sscanf_long_double_scientific);
  tcase_add_test(tc, test_sscanf_double_scientific);
  tcase_add_test(tc, test_sscanf_integer_auto_base_positive);
  tcase_add_test(tc, test_sscanf_long_double_negative);
  tcase_add_test(tc, test_sscanf_long_double_zero);
  tcase_add_test(tc, test_sscanf_long_double_large);
  tcase_add_test(tc, test_sscanf_long_double_small);
  tcase_add_test(tc, test_sscanf_floating_g);
  tcase_add_test(tc, test_sscanf_floating_G);

  return tc;
}
