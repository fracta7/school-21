#include <stdio.h>

#define MAX_INPUT 10

int input(int *buffer, int *length, int *shift);
void output(int *buffer, int length);
void array_shift(int *buffer, int length, int shift);

int main() {
    int buffer[MAX_INPUT];
    int length;
    int shift;

    if (input(buffer, &length, &shift) <= MAX_INPUT + 2 && length > 0) {
        if (shift != 0) {
            array_shift(buffer, length, shift);
            output(buffer, length);
        } else
            output(buffer, length);
    } else {
        printf("n/a");
    }

    return 0;
}

int input(int *buffer, int *length, int *shift) {
    int result = scanf("%d", length);

    for (int i = 0; i < *length; i++) {
        result += scanf("%d", &(buffer[i]));
    }

    result += scanf("%d", shift);

    return result;
}

void output(int *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", data[i]);
        if (i != length - 1) {
            printf(" ");
        }
    }
}

void array_shift(int *buffer, int length, int shift) {
    int flag = 0;  // indicates if shift is negative

    if (shift < 0) {  // we shift right if negative
        flag = 1;
        shift *= -1;
    }

    for (int i = 0; i < shift; i++) {
        int first = buffer[0];
        if (flag == 0) {
            for (int j = 0; j < length; j++) {
                if (j != length - 1)
                    buffer[j] = buffer[j + 1];
                else
                    buffer[j] = first;
            }
        } else {
            int last = buffer[length - 1];
            for (int j = length - 1; j >= 0; j--) {
                if (j != 0)
                    buffer[j] = buffer[j - 1];
                else
                    buffer[0] = last;
            }
        }
    }
}
