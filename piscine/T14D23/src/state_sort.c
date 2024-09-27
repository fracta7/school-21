#include <string.h>

#include "sort_io.h"
#include "state.h"

int main() {
    char file_path[PATH_LENGTH];
    size_t num_states;
    struct state new_state;
    int mode;
    int input_result = input(file_path, &mode, &new_state);
    if (input_result == 2 && strlen(file_path) != 0 && mode >= 0 && mode <= 2) {
        struct state *states = read_states(file_path, &num_states);
        if (states == NULL) {
            printf("n/a");
        } else {
            if (mode == 0) {
                output(states, num_states);
            } else if (mode == 1) {
                sort_states(states, num_states);
                output(states, num_states);
            } else {
                append_state(file_path, new_state);
                free(states);
                states = read_states(file_path, &num_states);
                sort_states(states, num_states);
                output(states, num_states);
            }
            free(states);
        }
    } else {
        printf("n/a");
    }
    return 0;
}