#ifndef SEARCH_LIB_H
#define SEARCH_LIB_H

#include "state.h"

int search_by_date(const char file_path[PATH_LENGTH], int search_day, int search_month, int search_year);
int input_search(char file_path[PATH_LENGTH], int *year, int *month, int *day);

#endif