CC = gcc
FLAGS = -Wall -Werror -Wextra -ggdb3

BUILD_DIR = ../build

# source files
STRING_C = s21_string.c
STRING_TEST_C = s21_string_test.c

# object files
STRING_O = $(BUILD_DIR)/s21_string.o
STRING_TEST_O = $(BUILD_DIR)/s21_string_test.o
STRLEN_O = $(BUILD_DIR)/s21_strlen_test.o
STRCMP_O = $(BUILD_DIR)/s21_strcmp_test.o
STRCPY_O = $(BUILD_DIR)/s21_strcpy_test.o
STRCAT_O = $(BUILD_DIR)/s21_strcat_test.o
STRCHR_O = $(BUILD_DIR)/s21_strchr_test.o

# target files
QUEST_1_EXEC = $(BUILD_DIR)/Quest_1
QUEST_2_EXEC = $(BUILD_DIR)/Quest_2
QUEST_3_EXEC = $(BUILD_DIR)/Quest_3
QUEST_4_EXEC = $(BUILD_DIR)/Quest_4
QUEST_5_EXEC = $(BUILD_DIR)/Quest_5

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests

# quest 1
strlen_tests: $(STRING_O) $(STRLEN_O)
	$(CC) $(FLAGS) $(STRING_O) $(STRLEN_O) -DSTRLEN_TESTS -o $(QUEST_1_EXEC)

# quest 2
strcmp_tests : $(STRING_O) $(STRCMP_O)
	$(CC) $(FLAGS) $(STRING_O) $(STRCMP_O) -DSTRCMP_TESTS -o $(QUEST_2_EXEC)

# quest 3
strcpy_tests : $(STRING_O) $(STRCPY_O)
	$(CC) $(FLAGS) $(STRING_O) $(STRCPY_O) -DSTRCPY_TESTS -o $(QUEST_3_EXEC)

# quest 4
strcat_tests : $(STRING_O) $(STRCAT_O)
	$(CC) $(FLAGS) $(STRING_O) $(STRCAT_O) -DSTRCAT_TESTS -o $(QUEST_4_EXEC)

# quest 5
strchr_tests : $(STRING_O) $(STRCHR_O)
	$(CC) $(FLAGS) $(STRING_O) $(STRCHR_O) -DSTRCHR_TESTS -o $(QUEST_5_EXEC)

$(STRING_O): $(STRING_C)
	$(CC) $(FLAGS) -c $(STRING_C)  -o $(STRING_O)

$(STRING_TEST_O): $(STRING_TEST_C)
	$(CC) $(FLAGS) -c $(STRING_TEST_C) -o $(STRING_TEST_O)

$(STRLEN_O) : $(STRING_TEST_C)
	$(CC) $(FLAGS) -c $(STRING_TEST_C) -DSTRLEN_TESTS -o $(STRLEN_O)

$(STRCMP_O) : $(STRING_TEST_C)
	$(CC) $(FLAGS) -c $(STRING_TEST_C) -DSTRCMP_TESTS -o $(STRCMP_O)

$(STRCPY_O) : $(STRING_TEST_C)
	$(CC) $(FLAGS) -c $(STRING_TEST_C) -DSTRCPY_TESTS -o $(STRCPY_O)

$(STRCAT_O) : $(STRING_TEST_C)
	$(CC) $(FLAGS) -c $(STRING_TEST_C) -DSTRCAT_TESTS -o $(STRCAT_O)

$(STRCHR_O) : $(STRING_TEST_C)
	$(CC) $(FLAGS) -c $(STRING_TEST_C) -DSTRCHR_TESTS -o $(STRCHR_O)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.a $(BUILD_DIR)/*.so $(BUILD_DIR)/Quest_*
