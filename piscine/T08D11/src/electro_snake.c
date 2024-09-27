#include <stdio.h>
#include <stdlib.h>
/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int rows, int cols, int ***result_matrix);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **matrix, int rows, int cols, int ***result_matrix);
int input(int ***matrix, int *rows, int *cols);
void output(int **matrix, int rows, int cols);
void sort_array(int *array, int length);

int input(int ***matrix, int *rows, int *cols) {
    int result = scanf("%d %d", rows, cols);
    if (result != 2) return 0;

    *matrix = (int **)calloc(*rows, sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = (int *)calloc(*cols, sizeof(int));
    }

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            result += scanf("%d", &((*matrix)[i][j]));
        }
    }
    return result;
}

void output(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j != cols - 1) printf(" ");
            if (j == cols - 1 && i != rows - 1) printf("\n");
        }
    }
}

void sort_vertical(int **matrix, int rows, int cols, int ***result_matrix) {
    // int current_row = 0;
    int *sorted_array = (int *)malloc(rows * cols * sizeof(int));
    int array_length = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sorted_array[array_length] = matrix[i][j];
            array_length++;
        }
    }
    sort_array(sorted_array, array_length);

    *result_matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        (*result_matrix)[i] = (int *)malloc(cols * sizeof(int));
    }

    int index = 0;
    for (int i = 0; i < cols; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < rows; j++) {
                (*result_matrix)[j][i] = sorted_array[index++];
            }
        } else {
            for (int j = rows - 1; j >= 0; j--) {
                (*result_matrix)[j][i] = sorted_array[index++];
            }
        }
    }
    free(sorted_array);
}

void sort_array(int *array, int length) {
    int swapped = 0;

    while (1) {
        swapped = 0;
        for (int i = 1; i < length; i++) {
            if (array[i - 1] > array[i]) {
                int first = array[i - 1];
                int second = array[i];
                array[i - 1] = second;
                array[i] = first;
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}

void sort_horizontal(int **matrix, int rows, int cols, int ***result_matrix) {
    // int current_col = 0;
    int *sorted_array = (int *)malloc(rows * cols * sizeof(int));
    int array_length = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sorted_array[array_length] = matrix[i][j];
            array_length++;
        }
    }
    sort_array(sorted_array, array_length);

    int index = 0;
    for (int i = 0; i < rows; i++) {
        if (i % 2 != 0) {
            for (int j = cols - 1; j >= 0; j--) {
                (*result_matrix)[i][j] = sorted_array[index++];
            }
        } else {
            for (int j = 0; j < cols; j++) {
                (*result_matrix)[i][j] = sorted_array[index++];
            }
        }
    }
    free(sorted_array);
}

int main() {
    int **matrix, **result;
    int rows, cols;

    int input_result = input(&matrix, &rows, &cols);

    if (input_result > 0 && input_result == rows * cols + 2 && rows > 0 && cols > 0) {
        sort_vertical(matrix, rows, cols, &result);
        output(result, rows, cols);
        printf("\n\n");

        sort_horizontal(matrix, rows, cols, &result);
        output(result, rows, cols);
    } else {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);  // Free each row (or sub-array)
        }
        free(matrix);
        for (int i = 0; i < rows; i++) {
            free(result[i]);  // Free each row (or sub-array)
        }
        free(result);
        printf("n/a");
    }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);  // Free each row (or sub-array)
    }
    free(matrix);
    for (int i = 0; i < rows; i++) {
        free(result[i]);  // Free each row (or sub-array)
    }
    free(result);

    return 0;
}
