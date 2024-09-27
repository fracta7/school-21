#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <stdlib.h>

#define PATH_LENGTH 256

struct state {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
};

struct state *read_states(const char *file_path, size_t *num_states);
int compare_states(const void *a, const void *b);
void sort_states(struct state *states, size_t num_states);
void append_state(const char *file_path, struct state new_entry);

#endif