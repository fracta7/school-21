#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

#define PADDLE_SIZE 3
#define BALL_SIZE 1

int player1_pos = HEIGHT / 2 - PADDLE_SIZE / 2;
int player2_pos = HEIGHT / 2 - PADDLE_SIZE / 2;
int ball_x = WIDTH / 2;
int ball_y = HEIGHT / 2;
int ball_dir_x = -1;
int ball_dir_y = -1;
int player1_score = 0;
int player2_score = 0;

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

int getch() {
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

void draw() {
    system("clear");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1) {
                printf("|");
            } else if (y == 0 || y == HEIGHT - 1) {
                printf("-");
            } else if (x == 1 && y >= player1_pos && y < player1_pos + PADDLE_SIZE) {
                printf("|");
            } else if (x == WIDTH - 2 && y >= player2_pos && y < player2_pos + PADDLE_SIZE) {
                printf("|");
            } else if (x == ball_x && y == ball_y) {
                printf("O");
            } else if (x == WIDTH / 2) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Player 1: %d\t\t\t\t\t\t\t\t\t\tPlayer 2: %d\n", player1_score, player2_score);
}

void update_ball() {
    ball_x += ball_dir_x;
    ball_y += ball_dir_y;

    if (ball_y <= 1 || ball_y >= HEIGHT - 2) {
        ball_dir_y = -ball_dir_y;
    }

    if (ball_x == 2 && ball_y >= player1_pos && ball_y < player1_pos + PADDLE_SIZE) {
        ball_dir_x = -ball_dir_x;
    } else if (ball_x == WIDTH - 3 && ball_y >= player2_pos && ball_y < player2_pos + PADDLE_SIZE) {
        ball_dir_x = -ball_dir_x;
    } else if (ball_x <= 0) {
        player2_score++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
        ball_dir_x = -ball_dir_x;
    } else if (ball_x >= WIDTH - 1) {
        player1_score++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
        ball_dir_x = -ball_dir_x;
    }
}

void update_paddle(int player, int direction) {
    if (player == 1) {
        if (direction == -1 && player1_pos > 1) {
            player1_pos--;
        } else if (direction == 1 && player1_pos < HEIGHT - PADDLE_SIZE - 1) {
            player1_pos++;
        }
    } else if (player == 2) {
        if (direction == -1 && player2_pos > 1) {
            player2_pos--;
        } else if (direction == 1 && player2_pos < HEIGHT - PADDLE_SIZE - 1) {
            player2_pos++;
        }
    }
}

int main() {
    set_conio_terminal_mode();
    while (1) {
        if (player1_score == 21 || player2_score == 21) {
            draw();
            printf("Player %d wins!\n", player1_score == 21 ? 1 : 2);
            break;
        }
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a' || ch == 'A') {
                update_paddle(1, -1);
            } else if (ch == 'z' || ch == 'Z') {
                update_paddle(1, 1);
            } else if (ch == 'k' || ch == 'K') {
                update_paddle(2, -1);
            } else if (ch == 'm' || ch == 'M') {
                update_paddle(2, 1);
            } else if (ch == ' ') {
                continue;
            }
        }
        update_ball();
        draw();
        usleep(50000);  // 50 milliseconds
    }
    return 0;
}
