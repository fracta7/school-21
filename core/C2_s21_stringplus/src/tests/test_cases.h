#ifndef TEST_CASES_H
#define TEST_CASES_H

#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

TCase *test_strlen(void);
TCase *test_memchr(void);
TCase *test_memcmp(void);
TCase *test_memcpy(void);
TCase *test_memset(void);
TCase *test_strchr(void);
TCase *test_strcspn(void);
TCase *test_strncat(void);
TCase *test_strncmp(void);
TCase *test_strncpy(void);
TCase *test_strpbrk(void);
TCase *test_strrchr(void);
TCase *test_strstr(void);
TCase *test_strtok(void);
TCase *test_to_upper(void);
TCase *test_to_lower(void);
TCase *test_insert(void);
TCase *test_trim(void);
TCase *test_strerror(void);
TCase *test_sprintf(void);
TCase *test_sscanf(void);

#endif