#include <string.h>

#include "search_lib.h"

int main() {
    char file_path[PATH_LENGTH];
    int day, month, year;

    int input_result = input_search(file_path, &year, &month, &day);

    if (input_result == 4 && strlen(file_path) != 0 && year >= 0 && day > 0 && month > 0) {
        int result = search_by_date(file_path, day, month, year);
        printf("%d", result);
    } else {
        printf("n/a");
    }
    return 0;
}