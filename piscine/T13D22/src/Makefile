CC = gcc -Werror -Wall -Wextra -std=c11

BUILD_DIR = ../build

SRCS = cipher.c

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: cipher

cipher: $(BUILD_DIR)/cipher.o
	$(CC) $(BUILD_DIR)/cipher.o -o $(BUILD_DIR)/cipher

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/cipher