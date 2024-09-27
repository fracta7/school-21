#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door *doors);
void output(struct door *doors);
void sort_struct(struct door *doors);
void bubble_sort(int *data);

int main() {
    struct door doors[DOORS_COUNT];
    initialize_doors(doors);
    sort_struct(doors);
    output(doors);

    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door *doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void output(struct door *doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        printf("%d, %d", doors[i].id, doors[i].status);
        if (i != DOORS_COUNT - 1) printf("\n");
    }
}

void sort_struct(struct door *doors) {
    int door_ids[DOORS_COUNT];
    for (int i = 0; i < DOORS_COUNT; i++) {
        door_ids[i] = doors[i].id;
    }
    bubble_sort(door_ids);
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = door_ids[i];
        doors[i].status = 0;
    }
}

void bubble_sort(int *data) {
    while (1) {
        int swapped = 0;
        for (int i = 1; i < DOORS_COUNT; i++) {
            if (data[i - 1] > data[i]) {
                int first = data[i - 1];
                int second = data[i];
                data[i - 1] = second;
                data[i] = first;
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}
