#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int rows, int cols);
int input(double ***matrix, int *rows, int *cols);
void output(double det);
double det2(double **matrix);
double det3(double **matrix);

int input(double ***matrix, int *rows, int *cols) {
    int result = scanf("%d %d", rows, cols);
    if (result != 2 || *rows != *cols || *cols > 3 || *rows > 3 || *rows < 2 || *cols < 2) {
        return 0;
    } else {
        *matrix = (double **)malloc(*rows * sizeof(double *));
        for (int i = 0; i < *rows; i++) {
            (*matrix)[i] = (double *)malloc(*cols * sizeof(double));
        }

        for (int i = 0; i < *rows; i++) {
            for (int j = 0; j < *cols; j++) {
                result += scanf("%lf", &((*matrix)[i][j]));
            }
        }
        return result;
    }
}

double det2(double **matrix) {
    double result = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    return result;
}

double det3(double **matrix) {
    double det_1 = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    double det_2 = matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0];
    double det_3 = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
    double result = matrix[0][0] * det_1 - matrix[0][1] * det_2 + matrix[0][2] * det_3;
    return result;
}

double det(double **matrix, int rows, int cols) {
    if (rows == 2 && cols == rows)
        return det2(matrix);
    else if (rows == 3 && cols == rows)
        return det3(matrix);
    else
        return -1.0;
}

void output(double det) { printf("%.6lf", det); }

int main() {
    double **matrix;
    double result;
    int rows, cols;

    int input_result = input(&matrix, &rows, &cols);
    if (input_result == 2 + rows * cols && rows == cols && rows > 0 && cols > 0 && rows < 4 && cols < 4) {
        result = det(matrix, rows, cols);
        output(result);
    } else {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);  // Free each row (or sub-array)
        }
        free(matrix);
        printf("n/a");
    }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);  // Free each row (or sub-array)
    }
    free(matrix);
    return 0;
}
