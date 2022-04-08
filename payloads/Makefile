CROSS_COMPILER ?= ~/tools/cross/gcc-linaro-5.3.1-2016.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
CC      = $(CROSS_COMPILER)gcc
OBJCOPY = $(CROSS_COMPILER)objcopy
XXD = xxd
AFLAGS  = -nostdlib
CFLAGS  = -O3 -nostdlib
LDFLAGS = -Wl,--build-id=none

SRCS := $(wildcard *.S)
SRCC := $(wildcard *.c)
PRGS := $(patsubst %.S,%,$(SRCS)) $(patsubst %.c,%,$(SRCC))
PRG_SUFFIX=.h
BINS := $(patsubst %,%$(PRG_SUFFIX),$(PRGS))

all: $(BINS)

%.elf: %.S
	$(CC) $(AFLAGS) $(LDFLAGS) -o $@ $^

%.elf: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.bin: %.elf
	$(OBJCOPY) -O binary -j .text $< $@

%.h: %.bin
	$(XXD) -i $^ $@

.PHONY: clean
clean:
	rm $(BINS)
