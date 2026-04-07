PWD := $(shell pwd)

SUBDIRS := mysed myfile mywc mytrans

all: mybash

$(SUBDIRS):
	$(MAKE) -s -C src/$@ OBJDIR=$(PWD)/obj/$@

mybash: $(SUBDIRS)
	$(MAKE) -s -C src/mybash BINDIR=$(PWD)/bin OBJDIR=$(PWD)/obj/mybash LINKLIBS="-L$(PWD)/obj/mysed -L$(PWD)/obj/myfile -L$(PWD)/obj/mywc -L$(PWD)/obj/mytrans"

clean:
	$(MAKE) -s -C src/mybash clean BINDIR=$(PWD)/bin OBJDIR=$(PWD)/obj/mybash
	$(MAKE) -s -C src/mysed clean OBJDIR=$(PWD)/obj/mysed
	$(MAKE) -s -C src/myfile clean OBJDIR=$(PWD)/obj/myfile
	$(MAKE) -s -C src/mywc clean OBJDIR=$(PWD)/obj/mywc
	$(MAKE) -s -C src/mytrans clean OBJDIR=$(PWD)/obj/mytrans
	$(RM) -r $(PWD)/obj $(PWD)/bin

.PHONY: all $(SUBDIRS) mybash clean
