#include <stdio.h>

int fibonacci(int n);

int main() {
    int input;

    if ((scanf("%d", &input)) == 1) {
        if (input < 0) {
            printf("n/a");
            return 0;
        }

        int result = fibonacci(input);
        printf("%d", result);
    } else {
        printf("n/a");
    }

    return 0;
}

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return (fibonacci(n - 1) + fibonacci(n - 2));
    }
}
