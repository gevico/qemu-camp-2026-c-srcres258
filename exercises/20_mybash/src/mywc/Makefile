CC = gcc
CFLAGS = -Wall -I../../include

LIBNAME := mywc
LIB := lib$(LIBNAME).a
OBJDIR ?= ./obj
LIB_PATH := $(OBJDIR)/$(LIB)

SRCS := mywc.c
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

all: $(LIB_PATH)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_PATH): $(OBJS)
	ar rcs $@ $(OBJS)

clean:
	$(RM) -r $(OBJDIR)
