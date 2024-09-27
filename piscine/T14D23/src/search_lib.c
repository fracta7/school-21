#include "search_lib.h"

int search_by_date(const char file_path[PATH_LENGTH], int search_day, int search_month, int search_year) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        return -1;  // Indicate error opening file
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the entire file
    struct state *states = malloc(file_size);
    if (states == NULL) {
        fclose(file);
        return -1;  // Indicate memory allocation error
    }

    // Read the entire file into memory
    size_t read_size = fread(states, 1, file_size, file);
    fclose(file);

    // Check if the read size matches the file size
    if ((long)read_size != file_size) {
        free(states);
        return -1;  // Indicate read error
    }

    // Calculate the number of states
    size_t num_states = file_size / sizeof(struct state);

    // Search for the matching date
    for (size_t i = 0; i < num_states; i++) {
        if (states[i].day == search_day && states[i].month == search_month && states[i].year == search_year) {
            int code = states[i].code;
            free(states);
            return code;
        }
    }

    // Free allocated memory and indicate no match found
    free(states);
    return -1;
}

int input_search(char file_path[PATH_LENGTH], int *year, int *month, int *day) {
    int result = scanf("%255s", file_path);
    result += scanf("%2d.%2d.%4d", day, month, year);
    return result;
}