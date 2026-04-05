# =============================================
# 主 Makefile
# 功能：
#   - mybash：生成二进制，放到 bin/
#   - 其他模块（mysed, myfile, mywc, mytrans）：生成静态库 .a，放到 obj/xxx/，.o 放到 obj/xxx/（或 out/，但建议统一）
#   - 所有子模块 Makefile 应支持 OBJDIR 和 BINDIR 参数
# =============================================

PWD := $(shell pwd)

SUBDIRS := \
	mysed \
	myfile \
	mywc \
	mytrans

all: mybash

$(SUBDIRS):
	$(MAKE) -C src/$@ OBJDIR=$(PWD)/obj/$@

mybash: $(SUBDIRS)
	$(MAKE) -C src/mybash OBJDIR=$(PWD)/obj/mybash BINDIR=$(PWD)/bin LINKLIBS="-L$(PWD)/obj/mysed -L$(PWD)/obj/mywc -L$(PWD)/obj/mytrans -L$(PWD)/obj/myfile"

clean:
	$(MAKE) -C src/mysed clean
	$(MAKE) -C src/myfile clean
	$(MAKE) -C src/mywc clean
	$(MAKE) -C src/mytrans clean
	$(MAKE) -C src/mybash clean
	rm -rf obj bin