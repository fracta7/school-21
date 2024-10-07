#include "test_cases.h"

START_TEST(test_to_lower_basic) {
  printf("[Running tests for s21_to_lower...]\n");
  const char str[] = "HELLO WORLD!";
  const char expected[] = "hello world!";
  char *lower = s21_to_lower(str);
  ck_assert_str_eq(lower, expected);
  free(lower);
}
END_TEST

START_TEST(test_to_lower_with_num) {
  const char str[] = "HELLO123!@#WORLD!";
  const char expected[] = "hello123!@#world!";
  char *lower = s21_to_lower(str);
  ck_assert_str_eq(lower, expected);
  free(lower);
}
END_TEST

START_TEST(test_to_lower_mixed) {
  const char str[] = "HeLLo WOrLd!";
  const char expected[] = "hello world!";
  char *lower = s21_to_lower(str);
  ck_assert_str_eq(lower, expected);
  free(lower);
}
END_TEST

START_TEST(test_to_lower_empty) {
  const char str[] = "";
  const char expected[] = "";
  char *lower = s21_to_lower(str);
  ck_assert_str_eq(lower, expected);
  free(lower);
}
END_TEST

START_TEST(test_to_lower_no_alpha) {
  const char str[] = "1234567890-=!@#$%^&*()_+";
  const char expected[] = "1234567890-=!@#$%^&*()_+";
  char *lower = s21_to_lower(str);
  ck_assert_str_eq(lower, expected);
  free(lower);
}
END_TEST

START_TEST(test_to_lower_special) {
  const char str[] = "My\nname\tis\nKal\tEl";
  const char expected[] = "my\nname\tis\nkal\tel";
  char *lower = s21_to_lower(str);
  ck_assert_str_eq(lower, expected);
  free(lower);
}
END_TEST

TCase *test_to_lower(void) {
  TCase *tc = tcase_create("to_lower");

  tcase_add_test(tc, test_to_lower_basic);
  tcase_add_test(tc, test_to_lower_with_num);
  tcase_add_test(tc, test_to_lower_mixed);
  tcase_add_test(tc, test_to_lower_empty);
  tcase_add_test(tc, test_to_lower_no_alpha);
  tcase_add_test(tc, test_to_lower_special);
  return tc;
}
