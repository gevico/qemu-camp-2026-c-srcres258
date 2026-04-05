CC = gcc
CFLAGS = -Wall -I../../include

TARGET := mybash
BINDIR ?= ./bin
OBJDIR ?= ./obj
LINKLIBS ?= -L../../obj/mysed -L../../obj/myfile -L../../obj/mywc -L../../obj/mytrans

SRCS := main.c
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

TARGET_PATH := $(BINDIR)/$(TARGET)

all: $(TARGET_PATH)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_PATH): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LINKLIBS) -lmysed -lmyfile -lmywc -lmytrans

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(TARGET_PATH)
