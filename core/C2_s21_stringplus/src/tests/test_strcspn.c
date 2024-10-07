#include "test_cases.h"

START_TEST(test_strcspn_not_found) {
  printf("[Running tests for s21_strcspn...]\n");
  const char str1[] = "hello";
  const char str2[] = "xyz";
  size_t s21 = s21_strcspn(str1, str2);
  size_t real = strcspn(str1, str2);
  ck_assert_uint_eq(s21, real);
}
END_TEST

START_TEST(test_strcspn_single) {
  const char str1[] = "hello";
  const char str2[] = "e";
  size_t s21 = s21_strcspn(str1, str2);
  size_t real = strcspn(str1, str2);
  ck_assert_uint_eq(s21, real);
}
END_TEST

START_TEST(test_strcspn_double) {
  const char str1[] = "World";
  const char str2[] = "ld";
  size_t s21 = s21_strcspn(str1, str2);
  size_t real = strcspn(str1, str2);
  ck_assert_uint_eq(s21, real);
}
END_TEST

START_TEST(test_strcspn_empty) {
  const char str1[] = "example";
  const char str2[] = "";
  size_t s21 = s21_strcspn(str1, str2);
  size_t real = strcspn(str1, str2);
  ck_assert_uint_eq(s21, real);
}
END_TEST

START_TEST(test_strcspn_first_empty) {
  const char str1[] = "";
  const char str2[] = "avc";
  size_t s21 = s21_strcspn(str1, str2);
  size_t real = strcspn(str1, str2);
  ck_assert_uint_eq(s21, real);
}
END_TEST

START_TEST(test_strcspn_found) {
  const char str1[] = "School 21";
  const char str2[] = "S";
  size_t s21 = s21_strcspn(str1, str2);
  size_t real = strcspn(str1, str2);
  ck_assert_uint_eq(s21, real);
}
END_TEST

START_TEST(test_strcspn_found_diff) {
  const char str1[] = "abcdef";
  const char str2[] = "xycd";
  size_t s21 = s21_strcspn(str1, str2);
  size_t real = strcspn(str1, str2);
  ck_assert_uint_eq(s21, real);
}
END_TEST

START_TEST(test_strcspn_special) {
  const char str1[] = "abc!@#";
  const char str2[] = "!@";
  size_t s21 = s21_strcspn(str1, str2);
  size_t real = strcspn(str1, str2);
  ck_assert_uint_eq(s21, real);
}
END_TEST

TCase *test_strcspn(void) {
  TCase *tc = tcase_create("strcspn");

  tcase_add_test(tc, test_strcspn_not_found);
  tcase_add_test(tc, test_strcspn_single);
  tcase_add_test(tc, test_strcspn_double);
  tcase_add_test(tc, test_strcspn_empty);
  tcase_add_test(tc, test_strcspn_first_empty);
  tcase_add_test(tc, test_strcspn_found);
  tcase_add_test(tc, test_strcspn_found_diff);
  tcase_add_test(tc, test_strcspn_special);

  return tc;
}
