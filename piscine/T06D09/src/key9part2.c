#include <stdio.h>

#define LEN 100

int input(int *buff1, int *len1, int *buff2, int *len2);
void output(int *buff1, int len1, int *buff2, int len2);
void sum(int *buff1, int len1, int *buff2, int *result, int *result_length);
int sub(int *buff1, int len1, int *buff2, int *result, int *result_length);
void array_shift(int *buffer, int length);

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод:
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод:
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/
int main() {
    int buff1[LEN];
    int buff2[LEN];
    int result_sum[LEN];
    int result_sub[LEN];
    int len1;
    int len2;
    int result_length_sum = 0;
    int result_length_sub = 0;

    for (int i = 0; i < LEN; i++) {
        buff1[i] = 0;
        buff2[i] = 0;
    }

    input(buff1, &len1, buff2, &len2);

    if (len1 != 0 && len2 != 0) {
        array_shift(buff1, len1);
        array_shift(buff2, len2);
        sum(buff1, len1, buff2, result_sum, &result_length_sum);
        if (sub(buff1, len1, buff2, result_sub, &result_length_sub) == 0) {
            output(result_sum, result_length_sum, result_sub, result_length_sub);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }

    return 0;
}

int input(int *buff1, int *len1, int *buff2, int *len2) {
    int ch1;
    int ch2;
    int i = 0;
    int j = 0;

    while ((ch1 = getchar()) != '\n' && ch1 != EOF && i < LEN - 1) {
        if (ch1 >= '0' && ch1 <= '9') buff1[i++] = ch1 - '0';
    }

    while ((ch2 = getchar()) != '\n' && ch2 != EOF && j < LEN - 1) {
        if (ch2 >= '0' && ch2 <= '9') buff2[j++] = ch2 - '0';
    }

    *len1 = i;
    *len2 = j;

    int result = i + j;

    return result;
}

void output(int *buff1, int len1, int *buff2, int len2) {
    int shift1 = LEN - len1;
    int shift2 = LEN - len2;

    for (int i = shift1; i < LEN; i++) {
        printf("%d", buff1[i]);
        if (i != LEN - 1) printf(" ");
        if (i == LEN - 1) printf("\n");
    }

    for (int i = shift2; i < LEN; i++) {
        printf("%d", buff2[i]);
        if (i != LEN - 1) printf(" ");
    }
}

void array_shift(int *buffer, int length) {
    int shift = LEN - length;

    for (int i = LEN - 1; i >= shift; i--) {
        buffer[i] = buffer[i - shift];
    }

    for (int i = 0; i < shift; i++) {
        buffer[i] = 0;
    }
    /*
    for (int i = 0; i < shift; i++) {
        for (int j = LEN - 1; j >= 0; j--) {
            if (j != 0) buffer[j] = buffer[j - 1];
            else buffer[0] = 0;
        }
    }
    */
}

void sum(int *buff1, int len1, int *buff2, int *result, int *result_length) {
    int extra = 0;
    for (int i = LEN - 1; i >= LEN - len1; i--) {
        int result_v = buff1[i] + buff2[i] + extra;
        if (extra != 0) extra--;
        if (result_v > 9) {
            extra++;
            (*result_length)++;
            result_v -= 10;
            result[i] = result_v;
        } else {
            (*result_length)++;
            result[i] = result_v;
        }
    }
}

int sub(int *buff1, int len1, int *buff2, int *result, int *result_length) {
    int borrow = 0;
    for (int i = LEN - 1; i >= LEN - len1; i--) {
        if (borrow != 0) borrow--;
        if ((buff1[i] - borrow) < buff2[i] && i != LEN - len1) {
            result[i] = (buff1[i] - borrow) + 10 - buff2[i];
            if (buff1[i - 1] == 0)
                buff1[i - 1] = 9;
            else
                buff1[i - 1] = buff1[i - 1] - 1;
            (*result_length)++;
            borrow++;
        } else if (buff1[i] > buff2[i]) {
            result[i] = buff1[i] - borrow - buff2[i];
            (*result_length)++;
        } else if ((buff1[i] - borrow) == buff2[i]) {
            result[i] = 0;
            (*result_length)++;
        } else if ((buff1[i] - borrow) < buff2[i] && i == LEN - len1)
            return 1;
    }
    for (int i = LEN - len1; i < LEN; i++) {
        if (result[i] == 0)
            (*result_length)--;
        else
            break;
    }
    return 0;
}
