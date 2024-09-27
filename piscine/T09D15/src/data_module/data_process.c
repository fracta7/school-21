#include "data_process.h"

#include <math.h>

#include "../data_libs/data_stat.h"

int normalization(double *data, int n) {
    int result = 1;
    double max_value = max(data, n);
    double min_value = min(data, n);
    double range = max_value - min_value;

    if (fabs(range - range) < EPS) {
        for (int i = 0; i < n; i++) {
            data[i] = (data[i] - min_value) / range;
        }
    } else {
        result = 0;
    }

    return result;
}

void sort(double *data, int n) {
    while (1) {
        int swapped = 0;
        for (int i = 1; i < n; i++) {
            if (data[i - 1] > data[i]) {
                int first = data[i - 1];
                int second = data[i];
                data[i - 1] = second;
                data[i] = first;
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}
