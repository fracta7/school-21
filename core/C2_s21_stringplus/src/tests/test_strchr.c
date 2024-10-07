#include "test_cases.h"

START_TEST(test_strchr_basic1) {
  printf("[Running tests for s21_strchr...]\n");
  char str[14] = "Hello, World!";
  char c = 'o';

  char *real = strchr(str, c);
  char *s21 = s21_strchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strchr_non_existent) {
  char str[14] = "Hello, World!";
  char c = 'z';

  char *real = strchr(str, c);
  char *s21 = s21_strchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strchr_empty) {
  char str[1] = "";
  char c = 'a';

  char *real = strchr(str, c);
  char *s21 = s21_strchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strchr_null) {
  char str[14] = "Hello, World!";
  char c = '\0';

  char *real = strchr(str, c);
  char *s21 = s21_strchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strchr_first) {
  char str[14] = "Hello, World!";
  char c = 'H';

  char *real = strchr(str, c);
  char *s21 = s21_strchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strchr_multiple) {
  char str[7] = "banana";
  char c = 'a';

  char *real = strchr(str, c);
  char *s21 = s21_strchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

TCase *test_strchr(void) {
  TCase *tc = tcase_create("strchr");

  tcase_add_test(tc, test_strchr_basic1);
  tcase_add_test(tc, test_strchr_non_existent);
  tcase_add_test(tc, test_strchr_empty);
  tcase_add_test(tc, test_strchr_null);
  tcase_add_test(tc, test_strchr_first);
  tcase_add_test(tc, test_strchr_multiple);

  return tc;
}