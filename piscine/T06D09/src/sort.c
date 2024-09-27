#include <stdio.h>

#define INPUT_SIZE 10

int input(int *data);
void output(int *data);
void bubble_sort(int *data);

int main() {
    int data[INPUT_SIZE];

    if (input(data) == INPUT_SIZE) {
        bubble_sort(data);
        output(data);
    } else {
        printf("n/a");
    }

    return 0;
}

int input(int *data) {
    int result = 0;

    for (int i = 0; i < INPUT_SIZE; i++) {
        result += scanf("%d", &(data[i]));
    }

    return result;
}

void output(int *data) {
    for (int i = 0; i < INPUT_SIZE; i++) {
        printf("%d", data[i]);
        if (i != INPUT_SIZE - 1) {
            printf(" ");
        }
    }
}

void bubble_sort(int *data) {
    int swapped = 0;

    while (1) {
        swapped = 0;
        for (int i = 1; i < INPUT_SIZE; i++) {
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
