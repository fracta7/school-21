CC = gcc -Wall -Werror -Wextra

BUILD_DIR = ../build

STATE_SORT_C = state_sort.c
SORT_IO_C = sort_io.c
STATE_C = state.c
SEARCH_LIB_C = search_lib.c
STATE_SEARCH_C = state_search.c

STATE_SORT_O = $(BUILD_DIR)/state_sort.o
SORT_IO_O = $(BUILD_DIR)/sort_io.o
STATE_O = $(BUILD_DIR)/state.o
SEARCH_LIB_O = $(BUILD_DIR)/search_lib.o
STATE_SEARCH_O = $(BUILD_DIR)/state_search.o

all: state_sort state_search

state_sort: $(STATE_SORT_O) $(SORT_IO_O) $(STATE_O)
	$(CC) $(STATE_SORT_O) $(SORT_IO_O) $(STATE_O) -o $(BUILD_DIR)/Quest_1

state_search: $(STATE_O) $(SEARCH_LIB_O) $(STATE_SEARCH_O)
	$(CC) $(STATE_O) $(SEARCH_LIB_O) $(STATE_SEARCH_O) -o $(BUILD_DIR)/Quest_2

$(STATE_SORT_O): $(STATE_SORT_C)
	$(CC) -c $(STATE_SORT_C) -o $(STATE_SORT_O)

$(SORT_IO_O): $(SORT_IO_C)
	$(CC) -c $(SORT_IO_C) -o $(SORT_IO_O)

$(STATE_O): $(STATE_C)
	$(CC) -c $(STATE_C) -o $(STATE_O)

$(SEARCH_LIB_O): $(STATE_SEARCH_C)
	$(CC) -c $(SEARCH_LIB_C) -o $(SEARCH_LIB_O)

$(STATE_SEARCH_O): $(STATE_SEARCH_C)
	$(CC) -c $(STATE_SEARCH_C) -o $(STATE_SEARCH_O)

clean:
	rm -rf $(BUILD_DIR)*.o $(BUILD_DIR)/Quest_*