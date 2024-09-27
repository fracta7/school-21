#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int input(int ***d_matrix, int (*s_matrix)[MAX_SIZE], int *mode, int *row, int *col);
void output_dynamic(int **matrix, int row, int col);
void output_static(int (*s_matrix)[MAX_SIZE], int row, int col);
int matrix_input_static(int (*s_matrix)[MAX_SIZE], int row, int col);
int matrix_input_dynamic1(int ***d_matrix, int row, int col);
int matrix_input_dynamic2(int ***d_matrix, int row, int col);
int matrix_input_dynamic3(int ***d_matrix, int row, int col);
int dynamic_input(int **d_matrix, int row, int col);
void d_max_row(int **matrix, int row, int col, int *result);
void d_min_col(int **matrix, int row, int col, int *result);
void s_max_row(int (*s_matrix)[MAX_SIZE], int row, int col, int *result);
void s_min_col(int (*s_matrix)[MAX_SIZE], int row, int col, int *result);
void output_array(int *max, int *min, int row, int col);

int input(int ***d_matrix, int (*s_matrix)[MAX_SIZE], int *mode, int *row, int *col) {
    int result = scanf("%d", mode);
    result += scanf("%d", row);
    result += scanf("%d", col);

    if (*mode == 1) {
        result += matrix_input_static(s_matrix, *row, *col);
    } else if (*mode == 2) {
        result += matrix_input_dynamic1(d_matrix, *row, *col);
    } else if (*mode == 3) {
        result += matrix_input_dynamic2(d_matrix, *row, *col);
    } else if (*mode == 4) {
        result += matrix_input_dynamic3(d_matrix, *row, *col);
    } else {
        return 0;
    }
    return result;
}

void output_dynamic(int **d_matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d", d_matrix[i][j]);
            if (j != col - 1)
                printf(" ");
            else if (j == col - 1 && i != row - 1)
                printf("\n");
        }
    }
}

void output_static(int (*s_matrix)[MAX_SIZE], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d", s_matrix[i][j]);
            if (j != col - 1)
                printf(" ");
            else if (j == col - 1 && i != row - 1)
                printf("\n");
        }
    }
}

int matrix_input_static(int (*s_matrix)[MAX_SIZE], int row, int col) {
    int result = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result += scanf("%d", &(s_matrix[i][j]));
            if (result != 1) {
                printf("n/a");
                exit(1);
            }
        }
    }
    return result;
}

int dynamic_input(int **d_matrix, int row, int col) {
    int result = 0;
    for (int i = 0; i < row; i++) {
        for (int k = 0; k < col; k++) {
            if (scanf("%d", &(d_matrix[i][k])) != 1) {
                return 0;
            } else
                result++;
        }
    }
    return result;
}

int matrix_input_dynamic1(int ***d_matrix, int row, int col) {
    int result = 0;
    *d_matrix = (int **)malloc(row * sizeof(int *));
    if (*d_matrix == NULL) {
        return 0;
    }
    for (int i = 0; i < row; i++) {
        (*d_matrix)[i] = (int *)malloc(col * sizeof(int));
        if ((*d_matrix)[i] == NULL) return 0;
    }

    result += dynamic_input(*d_matrix, row, col);
    return result;
}

int matrix_input_dynamic2(int ***d_matrix, int row, int col) {
    int result = 0;
    *d_matrix = (int **)calloc(row, sizeof(int *));
    if (*d_matrix == NULL) return 0;
    for (int i = 0; i < col; i++) {
        (*d_matrix)[i] = (int *)calloc(col, sizeof(int));
        if (*d_matrix == NULL) return 0;
    }
    result += dynamic_input(*d_matrix, row, col);
    return result;
}

int matrix_input_dynamic3(int ***d_matrix, int row, int col) {
    int result = 0;
    *d_matrix = (int **)malloc(1 * sizeof(int *));
    if (*d_matrix == NULL) return 0;
    (*d_matrix)[0] = (int *)malloc(1 * sizeof(int));
    if ((*d_matrix)[0] == NULL) return 0;

    *d_matrix = (int **)realloc(*d_matrix, (row) * sizeof(int *));
    if (*d_matrix == NULL) return 0;
    for (int i = 1; i < col; i++) {
        (*d_matrix)[i] = (int *)malloc(col * sizeof(int));
    }
    result += dynamic_input(*d_matrix, row, col);
    return result;
}

void d_max_row(int **d_matrix, int row, int col, int *result) {
    int max = 0;
    for (int i = 0; i < row; i++) {
        max = d_matrix[i][0];
        for (int j = 0; j < col; j++) {
            if (d_matrix[i][j] > max) result[i] = d_matrix[i][j];
        }
    }
}

void d_min_col(int **d_matrix, int row, int col, int *result) {
    int min = d_matrix[0][0];
    for (int i = 0; i < col; i++) {
        min = d_matrix[0][i];
        for (int k = 0; k < row; k++) {
            if (d_matrix[i][k] < min) result[k] = d_matrix[i][k];
        }
    }
}

void s_max_row(int (*s_matrix)[MAX_SIZE], int row, int col, int *result) {
    int max = s_matrix[0][0];
    for (int i = 0; i < row; i++) {
        max = s_matrix[i][0];
        for (int j = 0; j < col; j++) {
            if (s_matrix[i][j] > max) result[i] = s_matrix[i][j];
        }
    }
}

void s_min_col(int (*s_matrix)[MAX_SIZE], int row, int col, int *result) {
    int min = s_matrix[0][0];
    for (int i = 0; i < col; i++) {
        min = s_matrix[0][i];
        for (int k = 0; k < row; k++) {
            if (s_matrix[i][k] < min) result[k] = s_matrix[i][k];
            if (k == col - 1) min = 0;
        }
    }
}

void output_array(int *max, int *min, int row, int col) {
    for (int i = 0; i < row; i++) {
        printf("%d", max[i]);
        if (i != row - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < col; i++) {
        printf("%d", min[i]);
        if (i != col - 1) printf(" ");
    }
}

int main() {
    int **d_matrix;
    int *max_row;
    int *min_col;
    int s_matrix[MAX_SIZE][MAX_SIZE];
    int mode, row, col;
    int result = input(&d_matrix, s_matrix, &mode, &row, &col);
    max_row = (int *)malloc(row * sizeof(int));
    min_col = (int *)malloc(col * sizeof(int));
    if (max_row == NULL || min_col == NULL) {
        printf("n/a");
        return 0;
    }
    if (result == row * col + 3) {
        if (mode == 1) {
            output_static(s_matrix, row, col);
            printf("\n");
            s_max_row(s_matrix, row, col, max_row);
            s_min_col(s_matrix, row, col, min_col);
            output_array(max_row, min_col, row, col);
        } else if (mode == 2 || mode == 3 || mode == 4) {
            output_dynamic(d_matrix, row, col);
            printf("\n");
            d_max_row(d_matrix, row, col, max_row);
            d_min_col(d_matrix, row, col, min_col);
            output_array(max_row, min_col, row, col);
        } else {
            printf("n/a");
            free(d_matrix);
            free(max_row);
            free(min_col);
            return 0;
        }
    } else {
        free(d_matrix);
        free(max_row);
        free(min_col);
        printf("n/a");
    }
    free(d_matrix);
    free(max_row);
    free(min_col);
    return 0;
}
