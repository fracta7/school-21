#include "test_cases.h"

START_TEST(test_strlen_basic) {
  printf("[Running tests for s21_strlen...]\n");
  const char *test_str = "Hello, world!";

  ck_assert_uint_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_strlen_empty) {
  const char *test_str = "";

  ck_assert_uint_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_strlen_new_line) {
  const char *test_str = "Hello\nWorld!";

  ck_assert_uint_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_strlen_middle_null) {
  const char *test_str = "Hello\0World!";
  ck_assert_uint_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

TCase *test_strlen(void) {
  TCase *tc = tcase_create("strlen");
  tcase_add_test(tc, test_strlen_basic);
  tcase_add_test(tc, test_strlen_empty);
  tcase_add_test(tc, test_strlen_new_line);
  tcase_add_test(tc, test_strlen_middle_null);
  return tc;
}