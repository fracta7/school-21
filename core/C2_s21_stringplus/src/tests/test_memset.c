#include "test_cases.h"

START_TEST(test_memset_basic) {
  printf("[Running tests for s21_memset...]\n");
  char s21_buf[10] = {'\0'};
  char real_buf[10] = {'\0'};
  char c = 'A';
  size_t n = 5;

  s21_memset(s21_buf, c, n);
  memset(real_buf, c, n);

  ck_assert_int_eq(memcmp(s21_buf, real_buf, 10), 0);
}
END_TEST

START_TEST(test_memset_basic2) {
  char s21_buf[8];
  char real_buf[8];
  char c = '\0';
  size_t n = 8;

  s21_memset(s21_buf, c, n);
  memset(real_buf, c, n);

  ck_assert_int_eq(memcmp(s21_buf, real_buf, n), 0);
}
END_TEST

START_TEST(test_memset_basic3) {
  char s21_buf[6];
  char real_buf[6];
  char c = '\x01';
  size_t n = 6;

  s21_memset(s21_buf, c, n);
  memset(real_buf, c, n);

  ck_assert_int_eq(memcmp(s21_buf, real_buf, n), 0);
}
END_TEST

START_TEST(test_memset_partial) {
  char s21_buf[15] = "Hello, World!";
  char real_buf[15] = "Hello, World!";
  char c = 'x';
  size_t n = 7;

  s21_memset(s21_buf, c, n);
  memset(real_buf, c, n);

  ck_assert_int_eq(memcmp(s21_buf, real_buf, n), 0);
}
END_TEST

START_TEST(test_memset_empty) {
  char s21_buf[5] = "abcd";
  char real_buf[5] = "abcd";
  char c = 'Z';
  size_t n = 0;

  s21_memset(s21_buf, c, n);
  memset(real_buf, c, n);

  ck_assert_int_eq(memcmp(s21_buf, real_buf, n), 0);
}
END_TEST

TCase *test_memset(void) {
  TCase *tc = tcase_create("memset");

  tcase_add_test(tc, test_memset_basic);
  tcase_add_test(tc, test_memset_basic2);
  tcase_add_test(tc, test_memset_basic3);
  tcase_add_test(tc, test_memset_partial);
  tcase_add_test(tc, test_memset_empty);

  return tc;
}