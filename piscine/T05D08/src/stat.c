#include <stdio.h>
#define NMAX 10

int input(int *data, int *n);
void output(int *data, int n);
int max(int *data, int n);
int min(int *data, int n);
double mean(int *data, int n);
double variance(int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == n + 1 && n <= NMAX && n > 0) {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(n));
    } else
        printf("n/a");
    return 0;
}

int input(int *data, int *n) {
    int result = 0;

    result = scanf("%d", n);
    for (int *p = data; p - data < *n; p++) {
        result += scanf("%d", p);
    }
    return result;
}

void output(int *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", data[i]);
        if (i != n - 1)
            printf(" ");
        else
            printf("\n");
    }
}

int max(int *data, int n) {
    int max_number = data[0];
    for (int i = 0; i < n; i++) {
        if (max_number < data[i]) max_number = data[i];
    }
    return max_number;
}

int min(int *data, int n) {
    int min_number = data[0];

    for (int i = 0; i < n; i++) {
        if (min_number > data[i]) min_number = data[i];
    }
    return min_number;
}

double mean(int *data, int n) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        result += data[i];
    }
    result /= n;
    return result;
}

double variance(int n) { return (n * n - 1.0) / 12.0; }

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}
