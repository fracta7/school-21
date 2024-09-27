#ifndef SORT_IO_H
#define SORT_IO_H
#include <stdio.h>
#include <stdlib.h>

#include "state.h"

int input(char file_path[PATH_LENGTH], int *mode, struct state *new_state);
void output(const struct state *states, size_t num_states);

#endif