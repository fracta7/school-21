#include "test_cases.h"

START_TEST(test_strncpy_exact) {
  printf("[Running tests for s21_strncpy...]\n");
  const char str[] = "Hello";
  char real_dest[6];
  char s21_dest[6];
  size_t n = 5;

  s21_strncpy(s21_dest, str, n);
  strncpy(real_dest, str, n);
  ck_assert_int_eq(strncmp(real_dest, s21_dest, n), 0);
}
END_TEST

START_TEST(test_strncpy_partial) {
  const char str[] = "HelloWorld";
  char real_dest[6];
  char s21_dest[6];
  size_t n = 5;

  s21_strncpy(s21_dest, str, n);
  strncpy(real_dest, str, n);
  ck_assert_int_eq(strncmp(real_dest, s21_dest, n), 0);
}
END_TEST

START_TEST(test_strncpy_short_src) {
  const char str[] = "Hi";
  char real_dest[6];
  char s21_dest[6];
  size_t n = 5;

  s21_strncpy(s21_dest, str, n);
  strncpy(real_dest, str, n);
  ck_assert_int_eq(strncmp(real_dest, s21_dest, n), 0);
}
END_TEST

START_TEST(test_strncpy_n_zero) {
  const char str[] = "HelloWorld";
  char real_dest[6];
  char s21_dest[6];
  size_t n = 0;

  s21_strncpy(s21_dest, str, n);
  strncpy(real_dest, str, n);
  ck_assert_int_eq(strncmp(real_dest, s21_dest, n), 0);
}
END_TEST

START_TEST(test_strncpy_empty_src) {
  const char str[] = "";
  char real_dest[6];
  char s21_dest[6];
  size_t n = 5;

  s21_strncpy(s21_dest, str, n);
  strncpy(real_dest, str, n);
  ck_assert_int_eq(strncmp(real_dest, s21_dest, n), 0);
}
END_TEST

START_TEST(test_strncpy_special) {
  const char str[] = "Hello\nWorld\t";
  char real_dest[13];
  char s21_dest[13];
  size_t n = 13;

  s21_strncpy(s21_dest, str, n);
  strncpy(real_dest, str, n);
  ck_assert_int_eq(strncmp(real_dest, s21_dest, n), 0);
}
END_TEST

TCase *test_strncpy(void) {
  TCase *tc = tcase_create("strncpy");

  tcase_add_test(tc, test_strncpy_exact);
  tcase_add_test(tc, test_strncpy_partial);
  tcase_add_test(tc, test_strncpy_short_src);
  tcase_add_test(tc, test_strncpy_n_zero);
  tcase_add_test(tc, test_strncpy_empty_src);
  tcase_add_test(tc, test_strncpy_special);

  return tc;
}
