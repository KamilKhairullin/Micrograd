# Compiler options
CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I. -Isrc

# Directories
BINDIR = bin
SRCDIR = src

# Source files
SOURCES = main.c $(shell find $(SRCDIR) -name '*.c')

# Object files
OBJECTS = $(SOURCES:%.c=$(BINDIR)/%.o)

# Executable
EXECUTABLE = $(BINDIR)/main

# Default target
all: $(EXECUTABLE)

# Compile source files into objects
$(BINDIR)/%.o: %.c | $(BINDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link objects into executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Create bin directory if it doesn't exist
$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/src:
	mkdir -p $(BINDIR)/src

# Clean target
clean:
	rm -rf $(BINDIR)

.PHONY: all clean
