CC := gcc
CFLAGS := -Wall -Wextra -O2 -g
DEPFLAGS := -MMD -MP

OBJDIR := obj
TARGET := main

SRCS := main.c tasks.c mutex.c priority_sch.c spsc_q.c
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all run clean

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

-include $(DEPS)
