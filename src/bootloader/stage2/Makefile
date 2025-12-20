BIN?=bin/
ASM?=nasm
ASMFLAGS?=-f obj
CC16?=/usr/bin/watcom/binl64/wcc
CFLAGS16?=-4 -d3 -s -wx -ms -zl -zq -za99
LD16?=/usr/bin/watcom/binl64/wlink

SOURCES_C=$(wildcard *.c)
SOURCES_ASM=$(wildcard *.asm)
OBJECTS_C=$(patsubst %.c,$(BIN)/stage2/c/%.obj,$(SOURCES_C))
OBJECTS_ASM=$(patsubst %.asm,$(BIN)/stage2/asm/%.obj,$(SOURCES_ASM))

.PHONY: all stage2 clean always header done

all: header stage2 done

header:
	@echo "Building stage2..."

done:
	@echo "Built stage2..."

stage2: $(BIN)/stage2.bin

$(BIN)/stage2.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	@echo "Linking..."
	@$(LD16) NAME $(BIN)/stage2.bin FILE \{ $(OBJECTS_ASM) $(OBJECTS_C) \} OPTION MAP=$(BIN)/stage2.map @linker.lnk

$(BIN)/stage2/c/%.obj: %.c always
	@echo "Compiling    $<"
	@$(CC16) $(CFLAGS16) -fo=$@ $<

$(BIN)/stage2/asm/%.obj: %.asm always
	@echo "Compiling    $<"
	@$(ASM) $(ASMFLAGS) -o $@ $<

always:
	@mkdir -p $(BIN)/stage2/c
	@mkdir -p $(BIN)/stage2/asm

