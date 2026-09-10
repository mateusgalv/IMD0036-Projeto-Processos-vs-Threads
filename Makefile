TARGET = bin/varredor

CC = gcc
CFLAGS = -O3 -Wall -Wextra -pthread -Iinclude
LDFLAGS = -pthread

SRC_DIR = src
BUILD_DIR = build
TEMP_DIR = temp

# // A = 100.007.273 -> B = 8.000.000.000
# SEQUENCIAL
ARGS = 100 200 1
# ARGS = 6 6 1
# ARGS = 100007273 8000000000 1

# BLOCOS + PROCESSOS
# ARGS = 100007273 500000000 7 processo bloco
# ARGS = 100007273 100007373 7 processo bloco

# BLOCOS + THREADS
# ARGS = 100007273 1000000000 8 thread bloco teste
# ARGS = 100007273 1000000000 8 thread bloco

# CICLICO + PROCESSOS
# ARGS = 100007273 8000000000 8 processo ciclico
# ARGS = 100007273 100007373 7 processo ciclico


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
	@$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) $(ARGS)

clean:
	@rm -rf $(BUILD_DIR) $(TEMP_DIR) bin

.PHONY: all run clean