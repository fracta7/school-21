#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define COLS 80
#define ROWS 25

void init(int (*state)[COLS]);             // initial game initializations
void draw(int (*state)[COLS], int speed);  // drawing logic
void input(int *speed);                    // simulation input control
void update(int (*state)[COLS]);           // game logic
int row_sub(int row);                      // calculations inside the closed system
int row_add(int row);
int col_sub(int col);
int col_add(int col);
int calculate_neighbors(int (*state)[COLS], int row, int col);  // calculates the number of neighbors
void reset_terminal_mode();
void set_conio_terminal_mode();  // for changing to non-canonical mode
int kbhit();                     // returns 1 when the keyboard is pressed

struct termios oldt, newt;

void reset_terminal_mode() { tcsetattr(0, TCSANOW, &oldt); }

void set_conio_terminal_mode() {
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newt);
    atexit(reset_terminal_mode);
}

int kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int row_sub(int row) { return (row - 1 + ROWS) % ROWS; }

int row_add(int row) { return (row + 1) % ROWS; }

int col_sub(int col) { return (col - 1 + COLS) % COLS; }

int col_add(int col) { return (col + 1) % COLS; }

int calculate_neighbors(int (*state)[COLS], int row, int col) {
    int neighbors = 0;

    neighbors += state[row_sub(row)][col_sub(col)];
    neighbors += state[row_sub(row)][col];
    neighbors += state[row_sub(row)][col_add(col)];
    neighbors += state[row][col_sub(col)];
    neighbors += state[row][col_add(col)];
    neighbors += state[row_add(row)][col_sub(col)];
    neighbors += state[row_add(row)][col];
    neighbors += state[row_add(row)][col_add(col)];

    return neighbors;
}

void init(int (*state)[COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (scanf("%d", &state[i][j]) != 1) {
                printf("n/a");
            }
        }
    }
}

void draw(int (*state)[COLS], int speed) {
    system("clear");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (state[i][j] == 1)
                printf("o");
            else if (state[i][j] == 0)
                printf(" ");
            if (j == COLS - 1) printf("\n");
        }
    }
    printf("\nSimulation Speed: %d FPS\n", 1000 / (speed / 1000));
    printf("'+' - Increases simulation speed\n'-' - Decreases simulation speed\n");
}

void update(int (*state)[COLS]) {
    int new_state[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = calculate_neighbors(state, i, j);

            // if cell was dead
            if (state[i][j] == 0) {
                if (neighbors == 3) {
                    new_state[i][j] = 1;
                } else {
                    new_state[i][j] = 0;
                }
                // if cell is alive
            } else if (state[i][j] == 1) {
                // if neighbors are less than 2 or more than 3
                // cell dies
                if (neighbors < 2 || neighbors > 3) {
                    new_state[i][j] = 0;
                } else {
                    new_state[i][j] = 1;
                }
            }
        }
    }

    // we overwrite the state with the new one
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            state[i][j] = new_state[i][j];
        }
    }
}

void input(int *speed) {
    if (kbhit()) {
        int ch;
        ch = getchar();
        if (ch == '+' && *speed > 5000) {
            *speed -= 5000;
        }
        if (ch == '-' && *speed < 150000) *speed += 5000;
    }
}

int main() {
    int state[ROWS][COLS];      // matrix to hold game state
    int speed = 50000;          // delay for each loop
    init(state);                // initialize the state by reading from stdin
    set_conio_terminal_mode();  // set terminal mode to non-canonical

    // main game loop
    while (1) {
        update(state);
        draw(state, speed);
        input(&speed);
        usleep(speed);
    }
    return 0;
}
