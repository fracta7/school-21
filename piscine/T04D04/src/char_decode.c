#include <stdio.h>

void decode(char input);
void encode(char input);

int main(char *argv[]) {
    if (argv[1] == '0') {
        char input[10];
        if ((scanf("%c", input)) == 1) {
            int i;

            i = 0;
            while (i < sizeof(input)) {
                decode(input[i]);
                printf(" ");
            }
        } else {
            printf("n/a");
        }
    } else if (argv[1] == '1') {
    } else {
        printf("n/a");
    }

    return 0;
}

void decode(char input) { printf("%c", input); }

void encode(char input) { printf("%x", input); }
