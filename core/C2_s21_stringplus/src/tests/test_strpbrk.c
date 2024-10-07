#include "test_cases.h"

START_TEST(test_strpbrk_basic) {
  printf("[Running tests for s21_strpbrk...]\n");
  char str[] = "abcdef";
  char c[] = "c";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_multiple) {
  char str[] = "abcdef";
  char c[] = "cd";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_no_matching) {
  char str[] = "abcdef";
  char c[] = "xyz";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_empty_search) {
  char str[] = "abcdef";
  char c[] = "";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_empty_str) {
  char str[] = "";
  char c[] = "asd";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_empty) {
  char str[] = "";
  char c[] = "";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_null) {
  char str[] = "abcdef";
  char c[] = "\0";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_special) {
  char str[] = "Hello! World?";
  char c[] = "?!";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_first) {
  char str[] = "abcdef";
  char c[] = "a";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_last) {
  char str[] = "abcdef";
  char c[] = "";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strpbrk_multi) {
  char str[] = "abababba";
  char c[] = "ba";

  char *real = strpbrk(str, c);
  char *s21 = s21_strpbrk(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

TCase *test_strpbrk(void) {
  TCase *tc = tcase_create("strpbrk");

  tcase_add_test(tc, test_strpbrk_basic);
  tcase_add_test(tc, test_strpbrk_multiple);
  tcase_add_test(tc, test_strpbrk_no_matching);
  tcase_add_test(tc, test_strpbrk_empty_search);
  tcase_add_test(tc, test_strpbrk_empty_str);
  tcase_add_test(tc, test_strpbrk_empty);
  tcase_add_test(tc, test_strpbrk_null);
  tcase_add_test(tc, test_strpbrk_special);
  tcase_add_test(tc, test_strpbrk_first);
  tcase_add_test(tc, test_strpbrk_last);
  tcase_add_test(tc, test_strpbrk_multi);

  return tc;
}
