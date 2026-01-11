
# --- Config ---
CC      := gcc
CSTD    := -std=c11
WARN    := -Wall -Wextra -Wpedantic
OPT     := -O2
DBG     := -g
INCS    := -Iinclude

# --- Paths ---
SRC_DIR := src
BLD_DIR := build
BIN     := $(BLD_DIR)/app

# --- Files ---
SRCS    := $(wildcard $(SRC_DIR)/*.c)
OBJS    := $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(SRCS))

# --- Flags ---
CFLAGS  := $(CSTD) $(WARN) $(OPT) $(INCS)
LDFLAGS :=

# --- Default target ---
all: $(BIN)

# Link
$(BIN): $(OBJS)
	@mkdir -p $(BLD_DIR)
	$(CC) $(OBJS) -o $(BIN) $(LDFLAGS)

# Compile each .c -> .o
$(BLD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN)

debug: CFLAGS := $(CSTD) $(WARN) -O0 $(DBG) $(INCS)
debug: clean all

clean:
	rm -rf $(BLD_DIR)

.PHONY: all run debug clean
