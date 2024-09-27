#include <stdio.h>

#define NMAX 10

int input(int *data, int *n);
void output(int *data, int n);
void squaring(int *data, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == n + 1 && n > 0 && n <= NMAX) {
        squaring(data, n);
        output(data, n);
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *data, int *n) {
    int result = 0;

    result = scanf("%d", n);
    for (int *p = data; p - data < *n; p++) {
        result = result + scanf("%d", p);
    }
    return result;
}

void output(int *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", data[i]);
        if (i != n - 1) printf(" ");
    }
}

void squaring(int *data, int n) {
    for (int i = 0; i < n; i++) {
        data[i] *= data[i];
    }
}
