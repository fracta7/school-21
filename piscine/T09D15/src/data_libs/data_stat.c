#include "data_stat.h"

#include <math.h>

double max(const double *data, int n) {
    double max = 0;
    for (int i = 0; i < n; i++) {
        if (data[i] > max) max = data[i];
    }
    return max;
}

double min(const double *data, int n) {
    double min = 0;
    for (int i = 0; i < n; i++) {
        if (data[i] < min) min = data[i];
    }
    return min;
}

double mean(const double *data, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    double mean = sum / n;
    return mean;
}

double variance(const double *data, int n) {
    double mean_v = mean(data, n);
    double variance = 0;
    for (int i = 0; i < n; i++) {
        variance += pow((data[i] - mean_v), 2) / (n - 1);
    }
    return variance;
}
