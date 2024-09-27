#include "sort_io.h"

int input(char file_path[PATH_LENGTH], int *mode, struct state *new_state) {
    int result = scanf("%255s", file_path);
    result += scanf("%d", mode);
    if (*mode == 2) {
        result += scanf("%d", &(new_state->year));
        result += scanf("%d", &(new_state->month));
        result += scanf("%d", &(new_state->day));
        result += scanf("%d", &(new_state->hour));
        result += scanf("%d", &(new_state->minute));
        result += scanf("%d", &(new_state->second));
        result += scanf("%d", &(new_state->status));
        if (new_state->status != 0 && new_state->status != 1) result = 0;
        result += scanf("%d", &(new_state->code));
    }
    return result;
}

void output(const struct state *states, size_t num_states) {
    for (size_t i = 0; i < num_states; i++) {
        printf("%4d ", states[i].year);
        printf("%2d ", states[i].month);
        printf("%2d ", states[i].day);
        printf("%2d ", states[i].hour);
        printf("%2d ", states[i].minute);
        printf("%2d ", states[i].second);
        printf("%1d ", states[i].status);
        printf("%3d\n", states[i].code);
    }
}
