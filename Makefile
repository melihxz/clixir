# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS =

# Source files
SRC = src/lexer.c src/parser.c src/token.c src/utils.c src/main.c
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = clixir

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Print compiler and linker flags
info:
	@echo "Compiler: $(CC)"
	@echo "Compiler flags: $(CFLAGS)"
	@echo "Linker flags: $(LDFLAGS)"
