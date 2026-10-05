TARGET = bin/varredor

CC = gcc
CFLAGS = -O3 -Wall -Wextra -pthread -Iinclude
LDFLAGS = -pthread

SRC_DIR = src
BUILD_DIR = build
TEMP_DIR = temp
OUT_DIR = output

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

default: all

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p bin
	@$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(TEMP_DIR)
	@mkdir -p $(OUT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) $(ARGS)

clean:
	@rm -rf $(BUILD_DIR) $(TEMP_DIR) bin

.PHONY: default all run clean