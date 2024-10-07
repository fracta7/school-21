#include "test_cases.h"

START_TEST(test_insert_basic) {
  printf("[Running tests for s21_insert...]\n");
  const char src[] = "Hello world.";
  const char str[] = "beautiful ";
  const char expected[] = "Hello beautiful world.";
  const size_t n = 6;

  char *result = s21_insert(src, str, n);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_insert_start) {
  const char src[] = "world";
  const char str[] = "hello ";
  const char expected[] = "hello world";
  const size_t n = 0;

  char *result = s21_insert(src, str, n);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_insert_end) {
  const char src[] = "hello";
  const char str[] = " world";
  const char expected[] = "hello world";
  const size_t n = 5;

  char *result = s21_insert(src, str, n);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_insert_empty_str) {
  const char src[] = "hello";
  const char str[] = "";
  const char expected[] = "hello";
  const size_t n = 5;

  char *result = s21_insert(src, str, n);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_insert_empty_src) {
  const char src[] = "";
  const char str[] = "hello";
  const char expected[] = "hello";
  const size_t n = 0;

  char *result = s21_insert(src, str, n);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

START_TEST(test_insert_null_src) {
  const char *src = NULL;
  const char str[] = "hello";
  const size_t n = 5;

  char *result = s21_insert(src, str, n);

  ck_assert_ptr_eq(result, NULL);

  free(result);
}
END_TEST

START_TEST(test_insert_null_str) {
  const char *src = "hello";
  const char *str = NULL;
  const size_t n = 9;

  char *result = s21_insert(src, str, n);

  ck_assert_ptr_eq(result, NULL);

  free(result);
}
END_TEST

START_TEST(test_insert_null) {
  const char *src = NULL;
  const char *str = NULL;
  const size_t n = 1235;

  char *result = s21_insert(src, str, n);

  ck_assert_ptr_eq(result, NULL);

  free(result);
}
END_TEST

TCase *test_insert(void) {
  TCase *tc = tcase_create("insert");

  tcase_add_test(tc, test_insert_basic);
  tcase_add_test(tc, test_insert_start);
  tcase_add_test(tc, test_insert_end);
  tcase_add_test(tc, test_insert_empty_str);
  tcase_add_test(tc, test_insert_empty_src);
  tcase_add_test(tc, test_insert_null_src);
  tcase_add_test(tc, test_insert_null_str);
  tcase_add_test(tc, test_insert_null);

  return tc;
}
