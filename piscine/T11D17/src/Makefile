CC = gcc
FLAGS = -Wall -Werror -Wextra

BUILD_DIR = ../build

# source files
DMANAGER_MODULE_C = dmanager_module.c
LIST_TEST_C = list_test.c
LIST_C = list.c

# object files
DMANAGER_MODULE_O = $(BUILD_DIR)/dmanager_module.o
LIST_TEST_O = $(BUILD_DIR)/list_test.o
LIST_O = $(BUILD_DIR)/list.o

# libs
LIB_LIST = $(BUILD_DIR)/liblist.a

# targets
QUEST_1 = $(BUILD_DIR)/Quest_1
QUEST_2 = $(BUILD_DIR)/Quest_2

all: door_struct list_tests

door_struct: $(DMANAGER_MODULE_O)
	$(CC) $(FLAGS) $(DMANAGER_MODULE_O) -o $(QUEST_1)

list_tests: $(LIST_TEST_O) $(LIST_O)
	$(CC) $(FLAGS) $(LIST_O) $(LIST_TEST_O) -o $(QUEST_2)

$(DMANAGER_MODULE_O): $(DMANAGER_MODULE_C)
	$(CC) $(FLAGS) -c $(DMANAGER_MODULE_C) -o $(DMANAGER_MODULE_O)

$(LIST_O): $(LIST_C)
	$(CC) $(FLAGS) -c $(LIST_C) -o $(LIST_O)

$(LIST_TEST_O) : $(LIST_TEST_C)
	$(CC) $(FLAGS) -c $(LIST_TEST_C) -o $(LIST_TEST_O)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.a $(BUILD_DIR)/*.so $(BUILD_DIR)/Quest_*
