/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

#define MAX_INPUT 10

int input(int *buffer, int *length);
void output(int *buffer, int length, int sum_v);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int buffer[MAX_INPUT];
    int numbers[MAX_INPUT];
    int length;
    int found_numbers;
    int sum_v;

    if (input(buffer, &length) <= MAX_INPUT + 1 && length > 0) {
        sum_v = sum_numbers(buffer, length);
        found_numbers = find_numbers(buffer, length, sum_v, numbers);

        if (found_numbers != 0) {
            output(numbers, found_numbers, sum_v);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }

    return 0;
}

int input(int *buffer, int *length) {
    int result = scanf("%d", length);

    for (int i = 0; i < *length; i++) {
        result += scanf("%d", &(buffer[i]));
    }

    return result;
}

void output(int *buffer, int length, int sum_v) {
    printf("%d\n", sum_v);

    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i != length - 1) printf(" ");
    }
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0) {
            if (buffer[i] % 2 == 0) {
                sum += buffer[i];
            }
        }
    }

    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *buffer, int length, int number, int *numbers) {
    int index = 0;  // indicates number of elements that has been saved

    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0) {
            if (number % buffer[i] == 0) {
                numbers[index] = buffer[i];
                index++;
            }
        }
    }
    return index;
}
