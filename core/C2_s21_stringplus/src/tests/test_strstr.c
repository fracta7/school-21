#include "test_cases.h"

START_TEST(test_strstr_basic) {
  printf("[Running tests for s21_strstr...]\n");
  const char haystack[] = "Hello World!";
  const char needle[] = "Hello";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strstr_basic2) {
  const char haystack[] = "This is a test string";
  const char needle[] = "test";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strstr_last_with_special) {
  const char haystack[] = "This\tis\ta\ttest\nstring";
  const char needle[] = "string";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strstr_not_found) {
  const char haystack[] = "This is a test string!";
  const char needle[] = "StRiNg";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  const char haystack[] = "My name is Mario";
  const char needle[] = "";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
  const char haystack[] = "";
  const char needle[] = "Barry Allen";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strstr_full_match) {
  const char haystack[] = "Barry\tAllen\n";
  const char needle[] = "Barry\tAllen\n";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strstr_longer_needle) {
  const char haystack[] = "This is a";
  const char needle[] = "This is a test";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strstr_full_special) {
  const char haystack[] = "!@#$%^&*()";
  const char needle[] = "$%^&";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strstr_case_sensitive) {
  const char haystack[] = "Hello World!";
  const char needle[] = "hello";

  char *real = strstr(haystack, needle);
  char *s21 = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

TCase *test_strstr(void) {
  TCase *tc = tcase_create("strstr");

  tcase_add_test(tc, test_strstr_basic);
  tcase_add_test(tc, test_strstr_basic2);
  tcase_add_test(tc, test_strstr_last_with_special);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_empty_haystack);
  tcase_add_test(tc, test_strstr_full_match);
  tcase_add_test(tc, test_strstr_longer_needle);
  tcase_add_test(tc, test_strstr_full_special);
  tcase_add_test(tc, test_strstr_case_sensitive);

  return tc;
}
