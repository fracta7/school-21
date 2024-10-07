#include "test_cases.h"

START_TEST(test_strncat_basic1) {
  printf("[Running tests for s21_strncat...]\n");
  char s21_dest[15] = "Hello ";
  char real_dest[15] = "Hello ";
  const char src[] = "World!";
  size_t n = 3;

  s21_strncat(s21_dest, src, n);
  strncat(real_dest, src, n);

  ck_assert_int_eq(strcmp(s21_dest, real_dest), 0);
}
END_TEST

START_TEST(test_strncat_basic2) {
  char s21_dest[20] = "Hello ";
  char real_dest[20] = "Hello ";
  const char src[] = "World!";
  size_t n = 6;

  s21_strncat(s21_dest, src, n);
  strncat(real_dest, src, n);

  ck_assert_int_eq(strcmp(s21_dest, real_dest), 0);
}
END_TEST

START_TEST(test_strncat_basic3) {
  char s21_dest[20] = "Hello";
  char real_dest[20] = "Hello";
  const char src[] = ", World!";
  size_t n = 8;

  s21_strncat(s21_dest, src, n);
  strncat(real_dest, src, n);

  ck_assert_int_eq(strcmp(s21_dest, real_dest), 0);
}
END_TEST

START_TEST(test_strncat_empty1) {
  char s21_dest[20] = "Hello";
  char real_dest[20] = "Hello";
  const char src[] = "";
  size_t n = 2;

  s21_strncat(s21_dest, src, n);
  strncat(real_dest, src, n);

  ck_assert_int_eq(strcmp(s21_dest, real_dest), 0);
}
END_TEST

START_TEST(test_strncat_empty2) {
  char s21_dest[20] = "";
  char real_dest[20] = "";
  const char src[] = ", World!";
  size_t n = 8;

  s21_strncat(s21_dest, src, n);
  strncat(real_dest, src, n);

  ck_assert_int_eq(strcmp(s21_dest, real_dest), 0);
}
END_TEST

START_TEST(test_strncat_overlap) {
  char s21_dest[20] = "Hello";
  char real_dest[20] = "Hello";
  size_t n = 2;

  s21_strncat(s21_dest, s21_dest + 2, n);
  strncat(real_dest, real_dest + 2, n);

  ck_assert_int_eq(strcmp(s21_dest, real_dest), 0);
}
END_TEST

TCase *test_strncat(void) {
  TCase *tc = tcase_create("strncat");

  tcase_add_test(tc, test_strncat_basic1);
  tcase_add_test(tc, test_strncat_basic2);
  tcase_add_test(tc, test_strncat_basic3);
  tcase_add_test(tc, test_strncat_empty1);
  tcase_add_test(tc, test_strncat_empty2);
  tcase_add_test(tc, test_strncat_overlap);

  return tc;
}
