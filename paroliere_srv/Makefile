# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c11

# Target executable
TARGET = main

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

# Phony targets
.PHONY: all clean rebuild