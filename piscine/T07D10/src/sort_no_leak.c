#include <stdio.h>
#include <stdlib.h>

int input(int **data, int *length);
void output(int *data, int length);
void bubble_sort(int *data, int length);

int main() {
    int *data;
    int length;

    int input_result = input(&data, &length);

    if (input_result == length + 1) {
        bubble_sort(data, length);
        output(data, length);
        free(data);
    } else {
        free(data);
        printf("n/a");
    }
    return 0;
}

int input(int **data, int *length) {
    int result = scanf("%d", length);
    *data = (int *)malloc(*length * sizeof(int));
    if (*data == NULL) {
        printf("n/a");
        exit(1);
    }
    for (int i = 0; i < *length; i++) {
        result += scanf("%d", &((*data)[i]));
    }

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

void bubble_sort(int *data, int length) {
    int swapped = 0;

    while (1) {
        swapped = 0;
        for (int i = 1; i < length; i++) {
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
