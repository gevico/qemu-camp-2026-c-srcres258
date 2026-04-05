PWD := $(shell pwd)

SUBDIRS := mysed myfile mywc mytrans

all: mybash

$(SUBDIRS):
	$(MAKE) -C src/$@ OBJDIR=$(PWD)/obj/$@

mybash: $(SUBDIRS)
	$(MAKE) -C src/mybash BINDIR=$(PWD)/bin OBJDIR=$(PWD)/obj/mybash LINKLIBS="-L$(PWD)/obj/mysed -L$(PWD)/obj/myfile -L$(PWD)/obj/mywc -L$(PWD)/obj/mytrans"

clean:
	$(MAKE) -C src/mybash clean BINDIR=$(PWD)/bin OBJDIR=$(PWD)/obj/mybash
	$(MAKE) -C src/mysed clean OBJDIR=$(PWD)/obj/mysed
	$(MAKE) -C src/myfile clean OBJDIR=$(PWD)/obj/myfile
	$(MAKE) -C src/mywc clean OBJDIR=$(PWD)/obj/mywc
	$(MAKE) -C src/mytrans clean OBJDIR=$(PWD)/obj/mytrans
	$(RM) -r $(PWD)/obj $(PWD)/bin

.PHONY: all $(SUBDIRS) mybash clean
