/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/
#include <math.h>
#include <stdio.h>

#define N_MAX 30

int ideal_number(int *data, int n, double mean_v, double three_sigma);
double mean(int *data, int n);
double variance(int n);
int input(int *data, int *n);
void output(int *data, int n);
double three_sigma(double mean_v, double variance_v);

double mean(int *data, int n) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        result += data[i];
    }
    result /= n;
    return result;
}

int input(int *data, int *n) {
    int result = 0;

    result = scanf("%d", n);
    for (int *p = data; p - data < *n; p++) {
        result += scanf("%d", p);
    }
    return result;
}

double variance(int n) { return (n * n - 1.0) / 12.0; }

double three_sigma(double mean_v, double variance_v) {
    double result = mean_v + 3 * sqrt(variance_v);
    return result;
}

int ideal_number(int *data, int n, double mean_v, double three_sigma) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        int j = data[i];
        if (j % 2 == 0 && j >= mean_v && j <= three_sigma && j != 0) {
            result = j;
        }
    }
    return result;
}

int main() {
    int n, result, data[N_MAX];
    double mean_v, variance_v, three_sigma_v;
    if (input(data, &n) == n + 1 && n <= N_MAX && n > 0) {
        mean_v = mean(data, n);
        variance_v = variance(n);
        three_sigma_v = three_sigma(mean_v, variance_v);
        result = ideal_number(data, n, mean_v, three_sigma_v);
        printf("%d", result);
    } else
        printf("n/a");
    return 0;
}
