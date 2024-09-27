#include "data_io.h"

#include <stdio.h>
#include <stdlib.h>

int input(double **data, int *n) {
    int result = scanf("%d", n);
    if (result != 1) return 0;
    *data = (double *)malloc(*n * sizeof(double));
    if (*data == NULL) return 0;
    for (int i = 0; i < *n; i++) {
        result += scanf("%lf", &(*data)[i]);
    }
    return result;
}
void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2lf", data[i]);
        if (i != n - 1) printf(" ");
    }
}
