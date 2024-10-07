#include "test_cases.h"

START_TEST(test_strerror_valid_error_codes) {
  printf("[Running tests for s21_strerror...]\n");
  for (int i = 0; i < 135; i++) {
    char *real_str = strerror(i);
    char *custom_str = s21_strerror(i);

    ck_assert_str_eq(custom_str, real_str);
  }
}
END_TEST

START_TEST(test_strerror_negative_error_code) {
  int errnum = -1;
  char *real_str = strerror(errnum);
  char *custom_str = s21_strerror(errnum);

  ck_assert_str_eq(custom_str, real_str);
}
END_TEST

START_TEST(test_strerror_large_error_code) {
  int errnum = 10000;
  char *real_str = strerror(errnum);
  char *custom_str = s21_strerror(errnum);

  ck_assert_str_eq(custom_str, real_str);
}
END_TEST

START_TEST(test_strerror_zero_error_code) {
  int errnum = 0;
  char *real_str = strerror(errnum);
  char *custom_str = s21_strerror(errnum);

  ck_assert_str_eq(custom_str, real_str);
}
END_TEST

START_TEST(test_strerror_boundary_error_code) {
  int errnum = 133;
  char *real_str = strerror(errnum);
  char *custom_str = s21_strerror(errnum);

  ck_assert_str_eq(custom_str, real_str);
}
END_TEST

TCase *test_strerror(void) {
  TCase *tc = tcase_create("strerror");

  tcase_add_test(tc, test_strerror_valid_error_codes);
  tcase_add_test(tc, test_strerror_negative_error_code);
  tcase_add_test(tc, test_strerror_large_error_code);
  tcase_add_test(tc, test_strerror_zero_error_code);
  tcase_add_test(tc, test_strerror_boundary_error_code);

  return tc;
}
