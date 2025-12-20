TARGET_ASMFLAGS += -f elf
TARGET_CFLAGS   += -ffreestanding -nostdlib -I.
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
	$(wildcard */*/*/*.c)

OBJECTS_C := $(patsubst %.c,$(BIN)/kernel/c/%.obj,$(SOURCES_C))

HEADERS_ASM := \
	$(wildcard *.inc) \
	$(wildcard */*.inc) \
	$(wildcard */*/*.inc) \
	$(wildcard */*/*/*.inc)

SOURCES_ASM := \
	$(wildcard *.asm) \
	$(wildcard */*.asm) \
	$(wildcard */*/*.asm) \
	$(wildcard */*/*/*.asm)

OBJECTS_ASM := $(patsubst %.asm,$(BIN)/kernel/asm/%.obj,$(SOURCES_ASM))

.PHONY: all kernel clean always header done

all: header kernel done

header:
	@echo "Building kernel..."

done:
	@echo "Built kernel."

kernel: $(BIN)/kernel.bin

$(BIN)/kernel.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	@echo "Linking kernel..."
	@$(TARGET_LD) $(TARGET_LINKFLAGS) \
		-Wl,-Map=$(BIN)/kernel.map \
		-o $@ $^ $(TARGET_LIBS)

$(BIN)/kernel/c/%.obj: %.c $(HEADERS_C) always
	@echo "Compiling     $<"
	@$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ $<

$(BIN)/kernel/asm/%.obj: %.asm $(HEADERS_ASM) always
	@echo "Compiling     $<"
	@$(TARGET_ASM) $(TARGET_ASMFLAGS) -o $@ $<

always:
	@mkdir -p $(BIN)/kernel/c
	@mkdir -p $(BIN)/kernel/asm


