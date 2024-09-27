#include <stdio.h>
#include <string.h>

#define PATH_LENGTH 255

int input(int *menu, char file_path[PATH_LENGTH]);
void file_print(const char file_path[PATH_LENGTH], char o_file_path[PATH_LENGTH], int *flag);
void append_file(const char file_path[PATH_LENGTH], const char content[PATH_LENGTH]);
void cipher_shift(char content[PATH_LENGTH], const int shift);
int write_file(const char file_path[PATH_LENGTH], char content[PATH_LENGTH]);
int read_file(const char file_path[PATH_LENGTH], char content[PATH_LENGTH]);

int main() {
    int menu;
    char file_path[PATH_LENGTH];
    char o_file_path[PATH_LENGTH];
    int flag = 0;
    while (1) {
        int input_result = input(&menu, file_path);
        if (strlen(file_path) != 0 && input_result != 0) {
            if (menu == 1) {
                file_print(file_path, o_file_path, &flag);
            } else if (menu == -1) {
                break;
            } else if (menu == 2) {
                if (flag) {
                    append_file(o_file_path, file_path);
                    file_print(o_file_path, o_file_path, &flag);
                } else {
                    printf("n/a\n");
                }
            } else if (menu == 3) {
                char file_content[PATH_LENGTH];
                int read_result = read_file(file_path, file_content);
                int shift = 0;
                cipher_shift(file_content, shift);
                write_file(file_path, file_content);
            } else {
                printf("n/a\n");
                continue;
            }
        } else {
            printf("n/a\n");
            continue;
        }
    }
    return 0;
}

int input(int *menu, char file_path[PATH_LENGTH]) {
    int result = scanf("%d", menu);
    if (*menu == 1 || *menu == 2) {
        result += scanf("%99s", file_path);
    } else if (*menu == -1) {
        return -1;
    }
    return result;
}

void file_print(const char file_path[PATH_LENGTH], char o_file_path[PATH_LENGTH], int *flag) {
    char file_content[PATH_LENGTH];
    int read_result = read_file(file_path, file_content);
    if (read_result == 2) {
        *flag = 0;
        printf("n/a\n");
    } else {
        *flag = 1;
        int is_empty = 1;
        strcpy(o_file_path, file_path);
        printf("%s\nn/", file_content);
        if (read_result == 1) {
            printf("n/a\n");
        }
    }
}

void append_file(const char file_path[PATH_LENGTH], const char content[PATH_LENGTH]) {
    FILE *file_ptr;
    file_ptr = fopen(file_path, "a");
    fprintf(file_ptr, "%s", content);
    fclose(file_ptr);
}

void cipher_shift(char content[PATH_LENGTH], int shift) {
    int len = strlen(content);
    for (int i = 0; i < len; i++) {
        int result = shift + content[i];
        if (result < 127 && result > 32) {
            if (content[i] < 127 && content[i] > 32) content[i] = content[i] + shift;
        } else {
            result -= 126;
            if (content[i] < 127 && content[i] > 32) content[i] = result;
        }
    }
}

int read_file(const char file_path[PATH_LENGTH], char content[PATH_LENGTH]) {
    int result = 0;
    FILE *file_ptr;
    file_ptr = fopen(file_path, "r");
    if (file_ptr == NULL) {
        result = 2;
    } else {
        int is_empty = 1;
        while (fgets(content, PATH_LENGTH, file_ptr) != NULL) {
            is_empty = 0;
            result = 0;
        }
        if (is_empty) {
            result = 1;
        }
        fclose(file_ptr);
    }
    return result;
}

int write_file(const char file_path[PATH_LENGTH], char content[PATH_LENGTH]) {
    int result = 0;
    FILE *file_ptr;
    file_ptr = fopen(file_path, "w");
    if (file_ptr == NULL) {
        result = 1;
    } else {
        frpintf(file_ptr, "%s", content);
    }
    return 0;
}