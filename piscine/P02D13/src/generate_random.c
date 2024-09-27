#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLS 80
#define ROWS 25

int biased_random();
void init(int (*state)[COLS]);

void init(int (*state)[COLS]) {
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            state[i][j] = biased_random();
        }
    }
}

int biased_random() {
    // Generate a random float between 0 and 1
    float rand_val = (float)rand() / RAND_MAX;

    // Adjust the threshold to favor 0 slightly more than 1
    float threshold = 0.9;  // 90% chance to be 0, 10% chance to be 1

    // Return 0 if rand_val is less than the threshold, otherwise return 1
    return (rand_val < threshold) ? 0 : 1;
}

int main() {
    int state[ROWS][COLS];
    init(state);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d", state[i][j]);
            if (j != COLS - 1) printf(" ");
            if (j == COLS - 1 && i != ROWS - 1) printf("\n");
        }
    }
}
