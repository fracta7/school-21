#include "test_cases.h"

START_TEST(test_to_upper_basic) {
  printf("[Running tests for s21_to_upper...]\n");
  const char str[] = "hello world!";
  const char expected[] = "HELLO WORLD!";
  char *upper = s21_to_upper(str);
  ck_assert_str_eq(upper, expected);
  free(upper);
}
END_TEST

START_TEST(test_to_upper_with_num) {
  const char str[] = "hello123!@#world!";
  const char expected[] = "HELLO123!@#WORLD!";
  char *upper = s21_to_upper(str);
  ck_assert_str_eq(upper, expected);
  free(upper);
}
END_TEST

START_TEST(test_to_upper_mixed) {
  const char str[] = "HeLLo WOrLd!";
  const char expected[] = "HELLO WORLD!";
  char *upper = s21_to_upper(str);
  ck_assert_str_eq(upper, expected);
  free(upper);
}
END_TEST

START_TEST(test_to_upper_empty) {
  const char str[] = "";
  const char expected[] = "";
  char *upper = s21_to_upper(str);
  ck_assert_str_eq(upper, expected);
  free(upper);
}
END_TEST

START_TEST(test_to_upper_no_alpha) {
  const char str[] = "1234567890-=!@#$%^&*()_+";
  const char expected[] = "1234567890-=!@#$%^&*()_+";
  char *upper = s21_to_upper(str);
  ck_assert_str_eq(upper, expected);
  free(upper);
}
END_TEST

START_TEST(test_to_upper_special) {
  const char str[] = "My\nname\tis\nKal\tEl";
  const char expected[] = "MY\nNAME\tIS\nKAL\tEL";
  char *upper = s21_to_upper(str);
  ck_assert_str_eq(upper, expected);
  free(upper);
}
END_TEST

TCase *test_to_upper(void) {
  TCase *tc = tcase_create("to_upper");

  tcase_add_test(tc, test_to_upper_basic);
  tcase_add_test(tc, test_to_upper_with_num);
  tcase_add_test(tc, test_to_upper_mixed);
  tcase_add_test(tc, test_to_upper_empty);
  tcase_add_test(tc, test_to_upper_no_alpha);
  tcase_add_test(tc, test_to_upper_special);

  return tc;
}
