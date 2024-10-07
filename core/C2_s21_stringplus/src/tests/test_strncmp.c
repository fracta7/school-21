#include "test_cases.h"

START_TEST(test_strncmp_basic1) {
  printf("[Running tests for s21_strncmp...]\n");
  const char str1[] = "Hello";
  const char str2[] = "Hello";
  size_t n = 5;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_strncmp_basic2) {
  const char str1[] = "Hello World!";
  const char str2[] = "Hello, World!";
  size_t n = 8;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_strncmp_basic3) {
  const char str1[] = "Apple";
  const char str2[] = "Banana";
  size_t n = 5;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_strncmp_diff1) {
  const char str1[11] = "Testing323";
  const char str2[11] = "Testing";
  size_t n = 10;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_strncmp_diff2) {
  const char str1[11] = "Testing";
  const char str2[11] = "Testing123";
  size_t n = 10;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_strncmp_diff_case) {
  const char str1[] = "HELLO";
  const char str2[] = "hello";
  size_t n = 5;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_strncmp_empty) {
  const char str1[] = "";
  const char str2[] = "";
  size_t n = 1;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_strncmp_one_empty) {
  const char str1[6] = "Hello";
  const char str2[6] = "";
  size_t n = 5;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_strncmp_partial) {
  const char str1[] = "abcdef";
  const char str2[] = "abcxyz";
  size_t n = 3;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

START_TEST(test_strncmp_special) {
  const char str1[] = "abc\n";
  const char str2[] = "abc\t";
  size_t n = 4;

  int s21 = s21_normalize(s21_strncmp(str1, str2, n));
  int real = s21_normalize(strncmp(str1, str2, n));

  ck_assert_int_eq(s21, real);
}
END_TEST

TCase *test_strncmp(void) {
  TCase *tc = tcase_create("strncmp");

  tcase_add_test(tc, test_strncmp_basic1);
  tcase_add_test(tc, test_strncmp_basic2);
  tcase_add_test(tc, test_strncmp_basic3);
  tcase_add_test(tc, test_strncmp_diff1);
  tcase_add_test(tc, test_strncmp_diff2);
  tcase_add_test(tc, test_strncmp_diff_case);
  tcase_add_test(tc, test_strncmp_empty);
  tcase_add_test(tc, test_strncmp_one_empty);
  tcase_add_test(tc, test_strncmp_partial);
  tcase_add_test(tc, test_strncmp_special);

  return tc;
}
