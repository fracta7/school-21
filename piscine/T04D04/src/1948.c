#include <stdio.h>

int divide(int a, int b, int return_remainder);
int is_prime_finder(int n);
int largest_prime_divisor(int n);

int main() {
    int input;

    // take input from user
    if ((scanf("%d", &input)) == 1) {
        if (input < 0) input = input * -1;
        int result = largest_prime_divisor(input);

        // if return value is 0 or 1,
        // we print "n/a"
        // in other cases we print the number
        if (result == 0 || result == 1) {
            printf("n/a");
        } else {
            printf("%d", result);
        }
    } else {
        // print "n/a" in case input error
        printf("n/a");
    }

    return 0;
}

int divide(int a, int b, int return_remainder) {
    int result;
    int remainder;

    remainder = a;
    result = 0;

    while (remainder >= b) {
        remainder -= b;
        result++;
    }
    if (return_remainder == 0) {
        return result;
    } else {
        return remainder;
    }
}

int is_prime_number(int n) {
    int i;
    int flag;

    // if 0 or 1, we raise the flag
    if (i == 0 || n == 1) {
        flag = 1;
    }

    for (i = 2; i <= divide(n, 2, 0); ++i) {
        if (divide(n, i, 1) == 0) {
            flag = 1;
            break;
        }
    }

    // if flag was raised, we return true, indicating
    // it is a prime number
    if (flag == 0) {
        return 1;
    } else {
        return 0;
    }
}

int largest_prime_divisor(int n) {
    int divisor;
    int index;

    index = n / 2;
    divisor = 0;

    // we start from the highest given number
    // and substract 1 and check for remainder
    // and for prime numbers at the same time
    while (index > 0) {
        if (divide(n, index, 1) == 0 && is_prime_number(index) == 1) {
            divisor = index;
            // we return the first prime number
            return divisor;
        }
        // if there is no prime number,
        // we substract 1 from given number
        index--;
    }

    return divisor;
}
