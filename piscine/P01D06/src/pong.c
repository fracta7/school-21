#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25
#define RACKET_SIZE 3
#define WIN_SCORE 21

typedef struct {
    int x;
    int y;
    int dir_x;
    int dir_y;
} Ball;

typedef struct {
    int racket_y;
    int score;
} Player;

// Function prototypes
void init_game(Ball *ball, Player *left_player, Player *right_player, int *step_by_step_mode);
void draw(Ball ball, Player left_player, Player right_player);
void input(Player *left_player, Player *right_player, int *step_by_step_mode);
void logic(Ball *ball, Player *left_player, Player *right_player, int *step_by_step_mode);
void end_game(int winner);

// Function definitions
void init_game(Ball *ball, Player *left_player, Player *right_player, int *step_by_step_mode) {
    ball->x = WIDTH / 2;
    ball->y = HEIGHT / 2;
    ball->dir_x = 1;
    ball->dir_y = 1;
    left_player->racket_y = HEIGHT / 2 - RACKET_SIZE / 2;
    left_player->score = 0;
    right_player->racket_y = HEIGHT / 2 - RACKET_SIZE / 2;
    right_player->score = 0;
    *step_by_step_mode = 0;
}

void draw(Ball ball, Player left_player, Player right_player) {
    system("clear");  // clear the terminal
    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0) printf("|");
            if (x == WIDTH - 1) printf("|");

            if (x == ball.x && y == ball.y)
                printf("O");  // we draw the ball
            else if (x == 1 && y >= left_player.racket_y && y < left_player.racket_y + RACKET_SIZE)
                printf("|");
            else if (x == WIDTH - 2 && y >= right_player.racket_y && y < right_player.racket_y + RACKET_SIZE)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");

    printf("Score: Left Player %d - Right Player %d\n", left_player.score, right_player.score);
}

void input(Player *left_player, Player *right_player, int *step_by_step_mode) {
    char key = getchar();
    if (key == 'a' && left_player->racket_y > 0) left_player->racket_y--;
    if (key == 'z' && left_player->racket_y < HEIGHT - RACKET_SIZE) left_player->racket_y++;
    if (key == 'k' && right_player->racket_y > 0) right_player->racket_y--;
    if (key == 'm' && right_player->racket_y < HEIGHT - RACKET_SIZE) right_player->racket_y++;
    if (key == ' ') *step_by_step_mode = !*step_by_step_mode;
}

void logic(Ball *ball, Player *left_player, Player *right_player, int *step_by_step_mode) {
    if (!*step_by_step_mode) {
        ball->x += ball->dir_x;
        ball->y += ball->dir_y;

        if (ball->y <= 0 || ball->y >= HEIGHT - 1) ball->dir_y = -ball->dir_y;

        if (ball->x <= 1) {
            if (ball->y >= left_player->racket_y && ball->y < left_player->racket_y + RACKET_SIZE) {
                ball->dir_x = -ball->dir_x;
            } else {
                right_player->score++;
                ball->x = WIDTH / 2;
                ball->y = HEIGHT / 2;
            }
        }

        if (ball->x >= WIDTH - 2) {
            if (ball->y >= right_player->racket_y && ball->y < right_player->racket_y + RACKET_SIZE) {
                ball->dir_x = -ball->dir_x;
            } else {
                left_player->score++;
                ball->x = WIDTH / 2;
                ball->y = HEIGHT / 2;
            }
        }

        if (left_player->score >= WIN_SCORE) end_game(1);
        if (right_player->score >= WIN_SCORE) end_game(2);
    }
}

void end_game(int winner) {
    printf("Player %d wins! Congratulations!\n", winner);
    exit(0);
}

int main() {
    Ball ball;
    Player left_player, right_player;
    int step_by_step_mode;

    init_game(&ball, &left_player, &right_player, &step_by_step_mode);

    while (1) {
        draw(ball, left_player, right_player);
        input(&left_player, &right_player, &step_by_step_mode);
        logic(&ball, &left_player, &right_player, &step_by_step_mode);
    }

    return 0;
}
