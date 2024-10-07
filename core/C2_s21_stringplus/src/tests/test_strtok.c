#include "test_cases.h"

START_TEST(test_strtok_basic) {
  printf("[Running tests for s21_strtok...]\n");
  char real_str[] = "hello world";
  char s21_str[] = "hello world";
  const char *delim = " ";

  char *real = strtok(real_str, delim);
  char *s21 = s21_strtok(s21_str, delim);
  ck_assert_str_eq(real, s21);

  real = strtok(NULL, delim);
  s21 = s21_strtok(NULL, delim);

  ck_assert_str_eq(real, s21);
}
END_TEST

START_TEST(test_strtok_multiple_delims) {
  char real_str[] = "hello, world. welcome to C";
  char s21_str[] = "hello, world. welcome to C";
  const char *delim = " ,.";

  char *real = strtok(real_str, delim);
  char *s21 = s21_strtok(s21_str, delim);

  while (real != NULL && s21 != NULL) {
    ck_assert_str_eq(real, s21);
    real = strtok(NULL, delim);
    s21 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strtok_consecutive) {
  char real_str[] = "hello,,,world...welcome   to   C";
  char s21_str[] = "hello,,,world...welcome   to   C";
  const char *delim = " ,.";

  char *real = strtok(real_str, delim);
  char *s21 = s21_strtok(s21_str, delim);

  while (real != NULL && s21 != NULL) {
    ck_assert_str_eq(real, s21);
    real = strtok(NULL, delim);
    s21 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strtok_single_no_delim) {
  char real_str[] = "helloworld!";
  char s21_str[] = "helloworld!";
  const char *delim = " ,.";

  char *real = strtok(real_str, delim);
  char *s21 = s21_strtok(s21_str, delim);

  while (real != NULL && s21 != NULL) {
    ck_assert_str_eq(real, s21);
    real = strtok(NULL, delim);
    s21 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strtok_single_delim) {
  char real_str[] = "!";
  char s21_str[] = "!";
  const char *delim = "!";

  char *real = strtok(real_str, delim);
  char *s21 = s21_strtok(s21_str, delim);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strtok_only_delim) {
  char real_str[] = "!@#$^!@$%^";
  char s21_str[] = "!@#$^!@$%^";
  const char *delim = "!@#$%^";

  char *real = strtok(real_str, delim);
  char *s21 = s21_strtok(s21_str, delim);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strtok_digit_delim) {
  char real_str[] = "Hello1There2General3Kenobi";
  char s21_str[] = "Hello1There2General3Kenobi";
  const char *delim = "123";

  char *real = strtok(real_str, delim);
  char *s21 = s21_strtok(s21_str, delim);

  while (real != NULL && s21 != NULL) {
    ck_assert_str_eq(real, s21);
    real = strtok(NULL, delim);
    s21 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strtok_empty_delim) {
  char real_str[] = "Hello There. General Kenobi";
  char s21_str[] = "Hello There. General Kenobi";
  const char *delim = "";

  char *real = strtok(real_str, delim);
  char *s21 = s21_strtok(s21_str, delim);

  while (real != NULL && s21 != NULL) {
    ck_assert_str_eq(real, s21);
    real = strtok(NULL, delim);
    s21 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strtok_empty) {
  char real_str[] = "";
  char s21_str[] = "";
  const char *delim = "";

  char *real = strtok(real_str, delim);
  char *s21 = s21_strtok(s21_str, delim);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

TCase *test_strtok(void) {
  TCase *tc = tcase_create("strtok");

  tcase_add_test(tc, test_strtok_basic);
  tcase_add_test(tc, test_strtok_multiple_delims);
  tcase_add_test(tc, test_strtok_consecutive);
  tcase_add_test(tc, test_strtok_single_no_delim);
  tcase_add_test(tc, test_strtok_single_delim);
  tcase_add_test(tc, test_strtok_only_delim);
  tcase_add_test(tc, test_strtok_digit_delim);
  tcase_add_test(tc, test_strtok_empty_delim);
  tcase_add_test(tc, test_strtok_empty);

  return tc;
}