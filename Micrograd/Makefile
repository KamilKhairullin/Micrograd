# Compiler options
CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I. -Isrc -Itests

# Directories
BINDIR = bin
SRCDIR = src
TESTDIR = test

# Source files
SOURCES = main.c $(shell find $(SRCDIR) -name '*.c')
TESTSOURCES = $(shell find $(TESTDIR) -name '*.c')

# Object files
SRC_OBJ = $(SOURCES:%.c=$(BINDIR)/%.o)
TEST_OBJ = $(TESTSOURCES:%.c=$(BINDIR)/%.o)

# Executable
EXECUTABLE = $(BINDIR)/main
TEST_EXECUTABLE = $(BINDIR)/test_runner

# Default target
all: $(EXECUTABLE)
	./$(EXECUTABLE)

# Test target
test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Compile source files into objects
$(BINDIR)/%.o: %.c | $(BINDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link objects into executable
$(EXECUTABLE): $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) -o $@

# Link test objects into executable
$(TEST_EXECUTABLE): $(TEST_OBJ) $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) $(TEST_OBJ) -o $@


# Create bin directory if it doesn't exist
$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/src:
	mkdir -p $(BINDIR)/src

# Clean target
clean:
	rm -rf $(BINDIR)

.PHONY: all clean test
