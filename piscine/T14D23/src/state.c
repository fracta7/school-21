#include "state.h"

struct state *read_states(const char *file_path, size_t *num_states) {
    // Open the binary file
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    // Find the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Calculate the number of `struct state` elements
    *num_states = file_size / sizeof(struct state);

    // Allocate memory for the array of `struct state`
    struct state *states = malloc(*num_states * sizeof(struct state));
    if (states == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // Read the file into the array
    size_t read_count = fread(states, sizeof(struct state), *num_states, file);
    if (read_count != *num_states) {
        perror("Failed to read data");
        free(states);
        fclose(file);
        return NULL;
    }

    // Close the file
    fclose(file);

    return states;
}

int compare_states(const void *a, const void *b) {
    const struct state *stateA = (const struct state *)a;
    const struct state *stateB = (const struct state *)b;

    if (stateA->year != stateB->year) {
        return stateA->year - stateB->year;
    } else if (stateA->month != stateB->month) {
        return stateA->month - stateB->month;
    } else if (stateA->day != stateB->day) {
        return stateA->day - stateB->day;
    } else if (stateA->hour != stateB->hour) {
        return stateA->hour - stateB->hour;
    } else if (stateA->minute != stateB->minute) {
        return stateA->minute - stateB->minute;
    } else {
        return stateA->second - stateB->second;
    }
}

void sort_states(struct state *states, size_t num_states) {
    qsort(states, num_states, sizeof(struct state), compare_states);
}

void append_state(const char *file_path, struct state new_entry) {
    FILE *file = fopen(file_path, "ab");
    if (file == NULL) {
        printf("n/a");
    } else {
        if (fwrite(&new_entry, sizeof(struct state), 1, file) != 1) {
            printf("n/a");
        }
        fclose(file);
    }
}