# colors
RED=\033[0;31m
ORANGE=\033[0;33m
YELLOW=\033[1;33m
GREEN=\033[0;32m
BLUE=\033[0;34m
INDIGO=\033[0;35m
VIOLET=\033[1;35m
RESET=\033[0m

# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
TFLAGS = -lcheck -lm -lsubunit -lpthread
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage -lgcov

# Source files and object files
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Unit test source files (in tests/ subfolder)
TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = tests/tests

# Static library
LIBRARY = s21_string.a

test: CFLAGS += $(COVERAGE_FLAGS)
test: TFLAGS += $(COVERAGE_FLAGS)
gcov_report: CFLAGS += $(COVERAGE_FLAGS)
gcov_report: TFLAGS += $(COVERAGE_FLAGS)

# Default target to build the library
all: print clean $(LIBRARY)

print:
	@echo -e "$(RED)╭────────────────────────────────────────────────────────╮$(RESET)"
	@echo -e "$(RED)│$(GREEN)     ________  ___   _______________  _____   ________  $(RED)│$(RESET)"
	@echo -e "$(RED)│$(GREEN)    / ___/__ \<  /  / ___/_  __/ __ \/  _/ | / / ____/  $(RED)│$(RESET)"
	@echo -e "$(RED)│$(GREEN)    \__ \__/ // /   \__ \ / / / /_/ // //  |/ / / __    $(RED)│$(RESET)"
	@echo -e "$(RED)│$(GREEN)   ___/ / __// /   ___/ // / / _, _// // /|  / /_/ /    $(RED)│$(RESET)"
	@echo -e "$(RED)│$(GREEN)  /____/____/_/   /____//_/ /_/ |_/___/_/ |_/\____/     $(RED)│$(RESET)"
	@echo -e "$(RED)╰────────────────────────────────────────────────────────╯$(RESET)"

# Target to run tests
test: print clean $(LIBRARY) $(TEST_OBJ)
	@echo -e "$(GREEN)[Test files have been compiled.]$(RESET)"
	@$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_TARGET) $(LIBRARY) $(TFLAGS)
	@echo -e "$(VIOLET)"
	@./$(TEST_TARGET)
	@echo -e "$(RESET)"

# Rule to create the static library
$(LIBRARY): print $(OBJ)
	@echo -e "$(YELLOW)[Building a static library...]$(RESET)"
	@ar rcs $@ $(OBJ)
	@echo -e "$(YELLOW)[Compiling source files...]$(RESET)"
	@ranlib $(LIBRARY)
	@echo -e "$(BLUE)[Cleaning up object files...]$(RESET)"
	@rm -rf *.o
	@echo -e "$(GREEN)[Static library has been compiled!]$(RESET)"

# Compilation of source files into object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -lm

# Add rule to compile test source files in the tests/ subfolder
tests/%.o: tests/%.c
	@$(CC) $(CFLAGS) $(TFLAGS) -c $< -o $@ -lm

# Generate gcov reports
gcov_report: print clean test
	@echo -e "$(YELLOW)[Collecting coverage data...]$(RESET)"
	@gcov $(SRC) tests/*.c > /dev/null 2>&1
	@lcov --capture --directory . --output-file coverage.info > /dev/null 2>&1
	@echo -e "$(YELLOW)[Generating HTML report...]$(RESET)"
	@echo -e "$(VIOLET)"
	@genhtml coverage.info --output-directory coverage --legend | grep -e "Overall coverage rate:" -e "lines......:" -e "functions..:"
	@echo -e "$(RESET)"
	@echo -e "$(BLUE)[Cleaning up junk...]$(RESET)"
	@rm -rf *.o tests/*.o
	@rm -rf *.gcno *.gcda *.gcov tests/*.gcda tests/*.gcno
	@echo -e "$(GREEN)[Opening up a browser with report...]$(RESET)"
	@xdg-open coverage/index.html > /dev/null 2>&1

# Clean target to remove generated files
clean: clean_junk
	@echo -e "$(BLUE)[Cleaning...]$(RESET)"
	@rm -rf $(LIBRARY) $(TEST_TARGET)
	@rm -rf coverage.info coverage/src coverage/*.png coverage/*.css coverage/*.html coverage/tests
	@echo -e "$(GREEN)[Project has been cleaned!]$(RESET)"

clean_junk:
	@rm -rf *.o tests/*.o
	@rm -rf *.gcno *.gcda *.gcov tests/*.gcda tests/*.gcno

# Rebuild everything
re: clean all

.PHONY: all clean clean_junk re gcov_report test print
