#
#

CROSS_COMPILE ?=

CONFIG ?= src/config # location of bmconfig.h
DIR = src $(CONFIG)

#
SRC_C = $(foreach d,$(DIR),$(wildcard $(d)/*.c))
SRC_S = $(foreach d,$(DIR),$(wildcard $(d)/*.S))
SRC_H = $(foreach d,$(DIR),$(wildcard $(d)/*.h))

OBJ_C = $(patsubst src/%.c,build/%.o,$(SRC_C))
OBJ_S = $(patsubst src/%.S,build/%.o,$(SRC_S))

CFLAGS += -nostartfiles -nostdlib -ffreestanding
CFLAGS += -Os -fno-common
CFLAGS += $(foreach d,$(DIR),-I $(d))
CFLAGS += $(UFLAGS)

#
all: build/libbm.a
	ls -l build/libbm.a

build/libbm.a: $(OBJ_C) $(OBJ_S) Makefile
	@echo AR $@
	@$(CROSS_COMPILE)ar rcs $@ $(OBJ_C) $(OBJ_S)

build/%.o: src/%.c Makefile build $(SRC_H)
	@echo GCC $<
	@$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@

build/%.dis: build/%.a
	@echo OBJDUMP $<
	@$(CROSS_COMPILE)objdump -d $< > $@

show: build/libbm.dis
	less $<

stats: build/libbm.a
	@size -t $<
#

test: all
	make -C test test

#

build:
	mkdir build

clean:
	rm -rf build
	make -C test clean
