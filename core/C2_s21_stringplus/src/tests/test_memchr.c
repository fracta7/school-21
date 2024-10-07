#include "test_cases.h"

START_TEST(test_memchr_found) {
  printf("[Running tests for s21_memchr...]\n");
  char str[] = "Hello, world!";
  ck_assert_ptr_eq(s21_memchr(str, 'w', sizeof(str)),
                   memchr(str, 'w', sizeof(str)));
}
END_TEST

START_TEST(test_memchr_not_found) {
  char str[] = "Hello, world!";
  ck_assert_ptr_eq(s21_memchr(str, 'x', sizeof(str)),
                   memchr(str, 'x', sizeof(str)));
}
END_TEST

START_TEST(test_memchr_null_terminator) {
  char str[] = "Hello, world!";
  ck_assert_ptr_eq(s21_memchr(str, '\0', sizeof(str)),
                   memchr(str, '\0', sizeof(str)));
}
END_TEST

START_TEST(test_memchr_empty_string) {
  char str[] = "";
  ck_assert_ptr_eq(s21_memchr(str, 'a', sizeof(str)),
                   memchr(str, 'a', sizeof(str)));
}
END_TEST

START_TEST(test_memchr_binary_data) {
  unsigned char buf[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  ck_assert_ptr_eq(s21_memchr(buf, 0x03, sizeof(buf)),
                   memchr(buf, 0x03, sizeof(buf)));
}
END_TEST

TCase *test_memchr(void) {
  TCase *tc = tcase_create("memchr");

  tcase_add_test(tc, test_memchr_found);
  tcase_add_test(tc, test_memchr_not_found);
  tcase_add_test(tc, test_memchr_null_terminator);
  tcase_add_test(tc, test_memchr_empty_string);
  tcase_add_test(tc, test_memchr_binary_data);

  return tc;
}