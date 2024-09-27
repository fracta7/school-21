# Compiler and flags
CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -ggdb3
CCF = $(CC) $(FLAGS)

# sources
SRC = $(wildcard *.c)
LIB_FILE_C = ../common/lib_file.c

# object files
OBJ = $(SRC:.c=.o)
LIB_FILE = ../common/lib_file.o

TARGET = s21_cat

all: clean s21_cat

s21_cat: $(OBJ) $(LIB_FILE)
	$(CCF) $(OBJ) $(LIB_FILE) -o $(TARGET)

%.o: %.c
	$(CCF) -c $< -o $@

$(LIB_FILE): $(LIB_FILE_C)
	$(CCF) -c $(LIB_FILE_C) -o $(LIB_FILE)

clean:
	rm -rf *.o $(LIB_FILE) $(TARGET)

re: clean all

test: all
	chmod +x run_tests.sh
	./run_tests.sh

.PHONY: clean re all
