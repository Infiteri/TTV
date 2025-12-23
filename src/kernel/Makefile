TARGET_ASMFLAGS += -f elf
TARGET_CFLAGS   += -ffreestanding -nostdlib -I. -I$(SRC)
TARGET_LIBS     += -lgcc
TARGET_LINKFLAGS+= -T linker.ld -nostdlib

BIN ?= bin

HEADERS_C := \
	$(wildcard *.h) \
	$(wildcard */*.h) \
	$(wildcard */*/*.h) \
	$(wildcard */*/*/*.h)

SOURCES_C := \
	$(wildcard *.c) \
	$(wildcard */*.c) \
	$(wildcard */*/*.c) \
	$(wildcard */*/*/*.c) \
	arch/i686/isr_gen.c

OBJECTS_C := $(patsubst %.c,$(BIN)/kernel/c/%.obj,$(SOURCES_C))

HEADERS_ASM := \
	$(wildcard *.inc) \
	$(wildcard */*.inc) \
	$(wildcard */*/*.inc) \
	$(wildcard */*/*/*.inc) \
	arch/i686/isr_gen.inc

SOURCES_ASM := \
	$(wildcard *.asm) \
	$(wildcard */*.asm) \
	$(wildcard */*/*.asm) \
	$(wildcard */*/*/*.asm)

OBJECTS_ASM := $(patsubst %.asm,$(BIN)/kernel/asm/%.obj,$(SOURCES_ASM))

DIRS := $(sort $(dir $(OBJECTS_C) $(OBJECTS_ASM)))

$(DIRS):
	@mkdir -p $@


.PHONY: all kernel clean header done

all: header kernel done

header:
	@echo "Building kernel..."

done:
	@echo "Built kernel..."
	@echo $0

kernel: $(DIRS) $(BIN)/kernel.bin

$(BIN)/kernel.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	@echo "Linking kernel..."
	@$(TARGET_LD) $(TARGET_LINKFLAGS) \
		-Wl,-Map=$(BIN)/kernel.map \
		-o $@ $^ $(TARGET_LIBS)

$(BIN)/kernel/c/%.obj: %.c $(HEADERS_C) | $(BIN)/kernel/c
	@echo "Compiling     $<"
	@$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ $<

$(BIN)/kernel/asm/%.obj: %.asm $(HEADERS_ASM) | $(BIN)/kernel/asm
	@echo "Compiling     $<"
	@$(TARGET_ASM) $(TARGET_ASMFLAGS) -o $@ $<

arch/i686/isr_gen.c arch/i686/isr_gen.inc:
	$(ROOT)/build/GenerateIsrs.sh $(ROOT)/src/kernel/arch/i686/isr_gen.c $(ROOT)/src/kernel/arch/i686/isr_gen.inc

