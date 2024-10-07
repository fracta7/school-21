#include <string.h>

#include "test_cases.h"

START_TEST(test_memcmp_identical1) {
  printf("[Running tests for s21_memcmp...]\n");
  const char *str1 = "Hello, world!";
  const char *str2 = "Hello, world!";
  size_t n = 13;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_identical2) {
  const char *str1 = "abcdef";
  const char *str2 = "abcdef";
  size_t n = 6;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_small_diff1) {
  const char *str1 = "apple";
  const char *str2 = "apPle";
  size_t n = 5;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_small_diff2) {
  const char *str1 = "Hello, World!";
  const char *str2 = "Hello, world!";
  size_t n = 13;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_small_diff3) {
  const char *str1 = "abcdef";
  const char *str2 = "abcdeg";
  size_t n = 6;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_small_diff4) {
  const char *str1 = "foo";
  const char *str2 = "food";
  size_t n = 4;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_empty1) {
  const char *str1 = "";
  const char *str2 = "";
  size_t n = 1;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_empty2) {
  const char *str1 = "test";
  const char *str2 = "";
  size_t n = 1;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_empty3) {
  const char *str1 = "abcd\0ef";
  const char *str2 = "abcd\0gh";
  size_t n = 8;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_varied1) {
  const char *str1 = "abcdef";
  const char *str2 = "abc";
  size_t n = 3;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_varied2) {
  const char *str1 = "12345678";
  const char *str2 = "1234";
  size_t n = 4;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_special1) {
  const char *str1 = "abc\x01";
  const char *str2 = "abc\x02";
  size_t n = 4;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

START_TEST(test_memcmp_special2) {
  const char *str1 = "a\nb\nc";
  const char *str2 = "a\nb\nd";
  size_t n = 5;

  int real = s21_normalize(memcmp(str1, str2, n));
  int s21 = s21_normalize(memcmp(str1, str2, n));

  ck_assert_int_eq(real, s21);
}
END_TEST

TCase *test_memcmp(void) {
  TCase *tc = tcase_create("memcmp");

  tcase_add_test(tc, test_memcmp_identical1);
  tcase_add_test(tc, test_memcmp_identical2);
  tcase_add_test(tc, test_memcmp_small_diff1);
  tcase_add_test(tc, test_memcmp_small_diff2);
  tcase_add_test(tc, test_memcmp_small_diff3);
  tcase_add_test(tc, test_memcmp_small_diff4);
  tcase_add_test(tc, test_memcmp_empty1);
  tcase_add_test(tc, test_memcmp_empty2);
  tcase_add_test(tc, test_memcmp_empty3);
  tcase_add_test(tc, test_memcmp_varied1);
  tcase_add_test(tc, test_memcmp_varied2);
  tcase_add_test(tc, test_memcmp_special1);
  tcase_add_test(tc, test_memcmp_special2);

  return tc;
}
