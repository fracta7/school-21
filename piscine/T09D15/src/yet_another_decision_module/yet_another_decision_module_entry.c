#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "decision.h"

int main() {
    double *data;
    int n;

    int input_result = input(&data, &n);

    if (input_result == 1 + n && n > 0) {
        if (make_decision(data, n))
            printf("YES");
        else
            printf("NO");
    } else {
        printf("n/a");
    }
    if (data != NULL) free(data);
    return 0;
}
