#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "data_process.h"

int main() {
    double *data;
    int n;

    // Don`t forget to allocate memory !

    int input_result = input(&data, &n);
    if (input_result == n + 1) {
        if (normalization(data, n)) {
            output(data, n);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
    if (data != NULL) free(data);

    return 0;
}
