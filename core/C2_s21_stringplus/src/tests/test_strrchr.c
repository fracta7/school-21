#include "test_cases.h"

START_TEST(test_strrchr_basic) {
  printf("[Running tests for s21_strrchr...]\n");
  const char str[] = "Hello World";
  const char c = 'w';

  char *real = strrchr(str, c);
  char *s21 = s21_strrchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strrchr_multi) {
  const char str[] = "Banana";
  const char c = 'a';

  char *real = strrchr(str, c);
  char *s21 = s21_strrchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strrchr_multi_middle) {
  const char str[] = "abcabcabc";
  const char c = 'b';

  char *real = strrchr(str, c);
  char *s21 = s21_strrchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strrchr_not_found) {
  const char str[] = "Hello World";
  const char c = 'z';

  char *real = strrchr(str, c);
  char *s21 = s21_strrchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strrchr_last) {
  const char str[] = "Alice in Wonderland";
  const char c = 'd';

  char *real = strrchr(str, c);
  char *s21 = s21_strrchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strrchr_first) {
  const char str[16] = "Charlie Johnson";
  const char c = 'C';

  char *real = strrchr(str, c);
  char *s21 = s21_strrchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strrchr_special) {
  const char str[26] = "Charlie\tJohnson\nJohn\tCena";
  const char c = '\t';

  char *real = strrchr(str, c);
  char *s21 = s21_strrchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strrchr_empty_str) {
  const char str[] = "";
  const char c = 'a';

  char *real = strrchr(str, c);
  char *s21 = s21_strrchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

START_TEST(test_strrchr_null) {
  const char str[] = "abc";
  const char c = '\0';

  char *real = strrchr(str, c);
  char *s21 = s21_strrchr(str, c);

  ck_assert_ptr_eq(real, s21);
}
END_TEST

TCase *test_strrchr(void) {
  TCase *tc = tcase_create("strrchr");

  tcase_add_test(tc, test_strrchr_basic);
  tcase_add_test(tc, test_strrchr_multi);
  tcase_add_test(tc, test_strrchr_multi_middle);
  tcase_add_test(tc, test_strrchr_not_found);
  tcase_add_test(tc, test_strrchr_last);
  tcase_add_test(tc, test_strrchr_first);
  tcase_add_test(tc, test_strrchr_special);
  tcase_add_test(tc, test_strrchr_empty_str);
  tcase_add_test(tc, test_strrchr_null);

  return tc;
}
