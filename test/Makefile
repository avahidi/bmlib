#
#

BASE = ..

CFLAGS += -fno-builtin #  -nostdlib # -nodefaultlibs
CFLAGS += -Wno-pointer-to-int-cast
CFLAGS += -I$(BASE)/src/config/
CFLAGS += -I$(BASE)/src/

LFLAGS += -L$(BASE)/build/
LFLAGS += -lbm

all: build/test.exe


build/test.exe: src/*.c build Makefile
	gcc  $(CFLAGS) src/*.c $(LFLAGS) -o $@
	objdump -d $@ > $@.dis

show: build/test.exe
	less $<.dis

test: build/test.exe
	build/test.exe


build:
	mkdir build

clean:
	rm -rf build
