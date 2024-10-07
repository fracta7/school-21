#include "test_cases.h"

Suite *s21_string_suite(void) {
  Suite *s = suite_create("s21_string");

  suite_add_tcase(s, test_strlen());
  suite_add_tcase(s, test_memchr());
  suite_add_tcase(s, test_memcmp());
  suite_add_tcase(s, test_memcpy());
  suite_add_tcase(s, test_memset());
  suite_add_tcase(s, test_strchr());
  suite_add_tcase(s, test_strcspn());
  suite_add_tcase(s, test_strncat());
  suite_add_tcase(s, test_strncmp());
  suite_add_tcase(s, test_strncpy());
  suite_add_tcase(s, test_strpbrk());
  suite_add_tcase(s, test_strrchr());
  suite_add_tcase(s, test_strstr());
  suite_add_tcase(s, test_strtok());
  suite_add_tcase(s, test_to_upper());
  suite_add_tcase(s, test_to_lower());
  suite_add_tcase(s, test_insert());
  suite_add_tcase(s, test_trim());
  suite_add_tcase(s, test_strerror());
  suite_add_tcase(s, test_sprintf());
  suite_add_tcase(s, test_sscanf());

  return s;
}

// Main function to run the test suite
int main(void) {
  Suite *s = s21_string_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  // int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}