TARGET = bin/varredor

CC = gcc
CFLAGS = -O3 -Wall -Wextra -pthread -Iinclude
LDFLAGS = -pthread

SRC_DIR = src
BUILD_DIR = build

# SEQUENCIAL
# ARGS = 100000000 100000100 1 processo bloco

# BLOCOS + PROCESSOS
# ARGS = 100007273 8000000000 8 processo bloco
ARGS = 100007273 100007373 3 processo bloco

# CICLICO + PROCESSOS

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

default: run

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	@./$(TARGET) $(ARGS)

clean:
	rm -rf $(BUILD_DIR) bin

.PHONY: all run clean