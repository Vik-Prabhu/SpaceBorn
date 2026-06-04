# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -O2 -g
DEPFLAGS := -MMD -MP

# Output and target names
OBJDIR := obj
TARGET := main

# Source files and derived object/dependency files
SRCS := main.c tasks.c mutex.c priority_sch.c spsc_q.c
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Targets that are not real files
.PHONY: all build run clean

# Default target
all: $(TARGET)

# Build the whole project
build: $(TARGET)

# Build and run the program
run: build
	./$(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Create the object directory if missing
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile each .c into a .o and generate a .d file
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Remove only object and dependency files
clean:
	rm -f $(OBJS) $(DEPS)

# Include dependency files if they exist
-include $(DEPS)
