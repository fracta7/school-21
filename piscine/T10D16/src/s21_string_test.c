#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();

int main() {
#ifdef STRLEN_TESTS
    s21_strlen_test();
#endif

#ifdef STRCMP_TESTS
    s21_strcmp_test();
#endif

#ifdef STRCPY_TESTS
    s21_strcpy_test();
#endif

#ifdef STRCAT_TESTS
    s21_strcat_test();
#endif

#ifdef STRCHR_TESTS
    s21_strchr_test();
#endif

    return 0;
}

// quest 1
void s21_strlen_test() {
    const char *test_strings[] = {
        "Hello",
        "Rigney Sandy",
        "",
        "a\nc",
    };
    const int expected_results[] = {5, 12, 0, 3};
    printf("str_len_test:\n");
    for (int i = 0; i < 4; i++) {
        int result = s21_strlen(test_strings[i]);
        printf("input: %s\n", test_strings[i]);
        printf("result: %d\n", result);
        printf("test result: ");
        if (result == expected_results[i])
            printf("SUCCESS\n\n");
        else
            printf("FAIL\n\n");
    }
    printf("---------\n\n");
}

// quest 2
void s21_strcmp_test() {
    const char *test_strings[] = {
        "Hello",
        "Rigney Sandy",
        "",
        "a\nc",
    };
    const int index1[] = {0, 2, 3, 3};
    const int index2[] = {1, 2, 3, 2};
    const int expected_results[] = {-10, 0, 0, 97};
    printf("strcmp_test:\n");
    for (int i = 0; i < 4; i++) {
        const char *str1 = test_strings[index1[i]];
        const char *str2 = test_strings[index2[i]];
        int result = s21_strcmp(str1, str2);
        printf("input: %s\n", test_strings[i]);
        printf("result: %d\n", result);
        printf("test result: ");
        if (result == expected_results[i])
            printf("SUCCESS\n\n");
        else
            printf("FAIL\n\n");
    }
    printf("---------\n\n");
}

void s21_strcpy_test() {
    const char *test_strings[] = {
        "Hello",
        "Rigney Sandy",
        "",
        "a\nc",
    };
    char *copied_strings[4];
    for (int i = 0; i < 4; i++) {
        copied_strings[i] = (char *)malloc((s21_strlen(test_strings[i]) + 1) * sizeof(char));
    }
    printf("strcpy_test:\n");
    for (int i = 0; i < 4; i++) {
        char *result = s21_strcpy(copied_strings[i], test_strings[i]);
        printf("input: %s\n", test_strings[i]);
        printf("result: %s\n", result);
        printf("test result: ");
        if (s21_strcmp(result, test_strings[i]) == 0)
            printf("SUCCESS\n\n");
        else
            printf("FAIL\n\n");
    }
    for (int i = 0; i < 4; i++) {
        free(copied_strings[i]);
    }
    printf("---------\n\n");
}

void s21_strcat_test() {
    const char *test_strings[] = {
        "Hello",
        "Rigney Sandy",
        "",
        "a\nc",
    };

    char *new_strings[] = {"a\nc", "", "Rigney Sandy", "Hello"};
    const char *expected_results[] = {"a\ncHello", "Rigney Sandy", "Rigney Sandy", "Helloa\nc"};
    printf("strcat_test:\n");
    for (int i = 0; i < 4; i++) {
        char *result = s21_strcat(new_strings[i], test_strings[i]);
        printf("input: %s %s\n", new_strings[i], test_strings[i]);
        printf("result: %s\n", result);
        printf("test result: ");
        if (s21_strcmp(result, expected_results[i]) == 0)
            printf("SUCCESS\n\n");
        else
            printf("FAIL\n\n");
        free(result);
    }
    printf("---------\n\n");
}

void s21_strchr_test() {
    const char *test_strings[] = {
        "Hello",
        "Rigney Sandy",
        "",
        "a\nc",
    };
    const char test_chars[] = {'e', ' ', 'a', 'c'};
    const char *expected_results[] = {"ello", " Sandy", "", "c"};
    printf("strchr_test:\n");
    for (int i = 0; i < 4; i++) {
        char *result = s21_strchr(test_strings[i], test_chars[i]);
        if (result == NULL) result = "";
        printf("input: %s %c\n", test_strings[i], test_chars[i]);
        printf("result: %s\n", result);
        printf("test result: ");

        if (s21_strcmp(result, expected_results[i]) == 0)
            printf("SUCCESS\n\n");
        else
            printf("FAIL\n\n");
        if (result != NULL && s21_strcmp(result, "") != 0) free(result);
    }
    printf("---------\n\n");
}
