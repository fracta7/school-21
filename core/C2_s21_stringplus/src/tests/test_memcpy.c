#include "test_cases.h"

START_TEST(test_memcpy_basic1) {
  printf("[Running tests for s21_memcpy...]\n");
  const char s21_src[] = "Hello, world!";
  char s21_dest[50];
  char real_dest[50];

  s21_memcpy(s21_dest, s21_src, sizeof(s21_src));
  memcpy(real_dest, s21_src, sizeof(s21_src));

  ck_assert_str_eq(s21_dest, real_dest);
}
END_TEST

START_TEST(test_memcpy_basic2) {
  const char src[] = "123456789";
  char real_dest[50];
  char s21_dest[50];
  size_t n = 5;
  s21_memcpy(s21_dest, src, n);
  memcpy(real_dest, src, n);

  ck_assert_str_eq(s21_dest, real_dest);
}
END_TEST

START_TEST(test_memcpy_with_null) {
  const char src[] = "abc\0def";
  char real_dest[50];
  char s21_dest[50];
  size_t n = 7;
  s21_memcpy(s21_dest, src, n);
  memcpy(real_dest, src, n);

  ck_assert_int_eq(memcmp(s21_dest, real_dest, n), 0);
}
END_TEST

START_TEST(test_memcpy_special) {
  const char src[] = "abc\x01\x02\x03";
  char real_dest[50];
  char s21_dest[50];
  size_t n = 6;
  s21_memcpy(s21_dest, src, n);
  memcpy(real_dest, src, n);

  ck_assert_int_eq(memcmp(s21_dest, real_dest, n), 0);
}
END_TEST

START_TEST(test_memcpy_empty) {
  const char src[] = "";
  char real_dest[50];
  char s21_dest[50];
  size_t n = 1;
  s21_memcpy(s21_dest, src, n);
  memcpy(real_dest, src, n);

  ck_assert_int_eq(memcmp(s21_dest, real_dest, n), 0);
}
END_TEST

START_TEST(test_memcpy_overwrite) {
  const char src[] = "abcd";
  char real_dest[50] = "xxxx";
  char s21_dest[50] = "xxxx";
  size_t n = 4;
  s21_memcpy(s21_dest, src, n);
  memcpy(real_dest, src, n);

  ck_assert_int_eq(memcmp(s21_dest, real_dest, n), 0);
}
END_TEST

TCase *test_memcpy(void) {
  TCase *tc = tcase_create("memcpy");

  tcase_add_test(tc, test_memcpy_basic1);
  tcase_add_test(tc, test_memcpy_basic2);
  tcase_add_test(tc, test_memcpy_with_null);
  tcase_add_test(tc, test_memcpy_special);
  tcase_add_test(tc, test_memcpy_empty);
  tcase_add_test(tc, test_memcpy_overwrite);

  return tc;
}
