# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c11

# Target executable
TARGET = paroliere_srv

# Source directories
SRC_DIRS = .

# Find all source files
SRCS = $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything
rebuild: clean all

uninstall:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean rebuild uninstall