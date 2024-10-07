#include "test_cases.h"

START_TEST(test_trim_basic) {
  printf("[Running tests for s21_trim...]\n");
  const char str[] = " hello world ";
  const char trim[] = " ";
  const char expected[] = "hello world";

  char *result = s21_trim(str, trim);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_trim_multiple_spaces) {
  const char str[] = "    hello world    ";
  const char trim[] = " ";
  const char expected[] = "hello world";

  char *result = s21_trim(str, trim);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_trim_special_chars) {
  const char str[] = "--==hello world==--";
  const char trim[] = "-=";
  const char expected[] = "hello world";

  char *result = s21_trim(str, trim);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_trim_leading_spaces) {
  const char str[] = "    hello world";
  const char trim[] = " ";
  const char expected[] = "hello world";

  char *result = s21_trim(str, trim);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_trim_trailing_spaces) {
  const char str[] = "hello world    ";
  const char trim[] = " ";
  const char expected[] = "hello world";

  char *result = s21_trim(str, trim);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_trim_all_chars) {
  const char str[] = "abcabcabc";
  const char trim[] = "abc";
  const char expected[] = "";

  char *result = s21_trim(str, trim);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_trim_no_trim_chars) {
  const char str[] = "hello world";
  const char trim[] = "";
  const char expected[] = "hello world";

  char *result = s21_trim(str, trim);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_trim_empty_string) {
  const char str[] = "";
  const char trim[] = " ";
  const char expected[] = "";

  char *result = s21_trim(str, trim);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_trim_empty) {
  const char str[] = "";
  const char trim[] = "";
  const char expected[] = "";

  char *result = s21_trim(str, trim);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_trim_null_source) {
  char *result = s21_trim(NULL, " ");
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_trim_null_trim_chars) {
  const char str[] = "hello world";
  char *result = s21_trim(str, NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

TCase *test_trim(void) {
  TCase *tc = tcase_create("trim");

  tcase_add_test(tc, test_trim_basic);
  tcase_add_test(tc, test_trim_multiple_spaces);
  tcase_add_test(tc, test_trim_special_chars);
  tcase_add_test(tc, test_trim_leading_spaces);
  tcase_add_test(tc, test_trim_trailing_spaces);
  tcase_add_test(tc, test_trim_all_chars);
  tcase_add_test(tc, test_trim_no_trim_chars);
  tcase_add_test(tc, test_trim_empty_string);
  tcase_add_test(tc, test_trim_empty);
  tcase_add_test(tc, test_trim_null_source);
  tcase_add_test(tc, test_trim_null_trim_chars);

  return tc;
}
