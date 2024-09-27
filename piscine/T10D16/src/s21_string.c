#include "s21_string.h"

size_t s21_strlen(const char *data) {
    int length = 0;
    while (data[length] != '\0') {  // we keep iterating until we reach NULL character
        length++;
    }
    return length;
}

int s21_strcmp(const char *string1, const char *string2) {
    while (*string1 && (*string1 == *string2)) {
        string1++;
        string2++;
    }
    return *(char *)string1 - *(char *)string2;
}

char *s21_strcpy(char *n_string, const char *o_string) {
    int string_length = s21_strlen(o_string);
    for (int i = 0; i < string_length; i++) {
        n_string[i] = o_string[i];
    }
    n_string[string_length] = '\0';
    return n_string;
}

char *s21_strcat(char *string1, const char *string2) {
    int len1 = s21_strlen(string1);
    int len2 = s21_strlen(string2);
    char *new_string = (char *)malloc((len1 + len2 + 1) * sizeof(char));
    for (int i = 0; i < len1; i++) {
        new_string[i] = string1[i];
    }
    for (int i = 0; i < len2; i++) {
        new_string[i + len1] = string2[i];
    }
    new_string[len1 + len2] = '\0';
    return new_string;
}

char *s21_strchr(const char *string, int search) {
    int len = s21_strlen(string);
    int flag = 0;
    int index = 0;
    while (index < len) {
        if (string[index] == search) {
            flag = 1;
            break;
        } else {
            index++;
        }
    }
    if (flag) {
        char *new_string = (char *)malloc((len - index + 1) * sizeof(char));
        for (int i = 0; string[index + i] != '\0'; i++) {
            new_string[i] = string[i + index];
        }
        new_string[len - index] = '\0';

        return new_string;
    } else {
        return NULL;
    }
}
