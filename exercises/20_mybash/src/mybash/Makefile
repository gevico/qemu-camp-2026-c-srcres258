# src/mybash/Makefile

CC = gcc
CFLAGS = -Wall -I../../include

TARGET := mybash
BINDIR ?= ./bin
OBJDIR ?= ./obj
LINKLIBS ?= -L../../obj/mysed -L../../obj/mywc -L../../obj/mytrans -L../../obj/myfile

SRCS := main.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

TARGET_PATH := $(BINDIR)/$(TARGET)

all: $(TARGET_PATH)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I../../include -c $< -o $@

$(BINDIR):
	@mkdir -p $(BINDIR)

$(TARGET_PATH): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LINKLIBS) -lmywc -lmytrans -lmysed -lmyfile

clean:
	@rm -rf $(OBJDIR)/*.o $(TARGET_PATH)