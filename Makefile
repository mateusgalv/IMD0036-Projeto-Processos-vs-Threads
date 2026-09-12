TARGET = bin/varredor

CC = gcc
CFLAGS = -O3 -Wall -Wextra -pthread -Iinclude
LDFLAGS = -pthread

SRC_DIR = src
BUILD_DIR = build
TEMP_DIR = temp
OUT_DIR = output

# A = 100007273 -> B = 8000000000

# SEQUENCIAL
# ARGS = 100 200 1
# ARGS = 100007273 8000000000 1


# ARGS = 100007273 8000000000 2 processo bloco processo_bloco_w2.txt
# ARGS = 100007273 8000000000 4 processo bloco processo_bloco_w4.txt
# ARGS = 100007273 8000000000 8 processo bloco processo_bloco_w8.txt


# ARGS = 100007273 8000000000 2 processo ciclico processo_ciclico_w2.txt
# ARGS = 100007273 8000000000 4 processo ciclico processo_ciclico_w4.txt
ARGS = 100007273 8000000000 8 processo ciclico processo_ciclico_w8.txt


# ARGS = 100007273 8000000000 2 thread bloco thread_bloco_w2.txt
# ARGS = 100007273 8000000000 4 thread bloco thread_bloco_w4.txt
# ARGS = 100007273 8000000000 8 thread bloco thread_bloco_w8.txt


# ARGS = 100007273 8000000000 2 thread ciclico thread_ciclico_w2.txt
# ARGS = 100007273 8000000000 4 thread ciclico thread_ciclico_w4.txt
# ARGS = 100007273 8000000000 8 thread ciclico thread_ciclico_w8.txt


SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

default: run

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

.PHONY: all run clean