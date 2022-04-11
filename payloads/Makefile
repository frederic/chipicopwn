CROSS_COMPILER ?= ~/tools/cross/gcc-linaro-5.3.1-2016.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
CC      = $(CROSS_COMPILER)gcc
OBJCOPY = $(CROSS_COMPILER)objcopy
XXD = xxd
DD = dd
AFLAGS  = -nostdlib
CFLAGS  = -O3 -nostdlib
LDFLAGS = -Wl,--build-id=none

SRCS := $(wildcard *.S)
SRCC := $(wildcard *.c)
PRGS := $(patsubst %.S,%,$(SRCS)) $(patsubst %.c,%,$(SRCC))
PRG_SUFFIX=.h
BINS := $(patsubst %,%$(PRG_SUFFIX),$(PRGS))

all: $(BINS)

%.bin: %.S
	$(CC) $(AFLAGS) $(LDFLAGS) -o $@ $<
	$(OBJCOPY) -O binary -j .text $@

%.bin: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
	$(OBJCOPY) -O binary -j .text $@
	$(DD) if=./RA.bin of=$@ bs=1 seek=568 conv=notrunc

%.h: %.bin
	$(XXD) -i $< $@

.PHONY: clean
clean:
	rm $(BINS)
