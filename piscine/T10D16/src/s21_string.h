#ifndef S21_STRING_H
#define S21_STRING_H
#include <stdio.h>
#include <stdlib.h>

size_t s21_strlen(const char *data);
int s21_strcmp(const char *string1, const char *string2);
char *s21_strcpy(char *n_string, const char *o_string);
char *s21_strcat(char *string1, const char *string2);
char *s21_strchr(const char *string, int search);

#endif
