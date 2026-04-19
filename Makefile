CC = gcc
AS = nasm
CFLAGS = -Wall -Wextra -O2 -Iinclude
ASFLAGS = -f elf64
LDFLAGS = -lncurses --no-pie

SRC_DIR = src
ASM_DIR = asm
OBJ_DIR = obj
INC_DIR = include

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(ASM_DIR)/*.asm)

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES)) \
            $(patsubst $(ASM_DIR)/%.asm, $(OBJ_DIR)/%.o, $(ASM_FILES))

TARGET = pong

.PHONY: all clean init

all: init $(TARGET)

init:
	@mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(ASM_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)