TARGET_ASMFLAGS += -f elf
TARGET_CFLAGS   += -ffreestanding -nostdlib -I$(SRC) -I$(SRC)/lib
TARGET_LIBS     += -lgcc
TARGET_LINKFLAGS+= -T linker.ld -nostdlib

SOURCES_C   := $(wildcard *.c)
SOURCES_ASM := $(wildcard *.asm)

OBJECTS_C   := $(patsubst %.c,$(BIN)/stage2/c/%.obj,$(SOURCES_C))
OBJECTS_ASM := $(patsubst %.asm,$(BIN)/stage2/asm/%.obj,$(SOURCES_ASM))

.PHONY: all stage2 clean header done

all: header stage2 done

header:
	@echo "Building bootloader stage2..."

done:
	@echo "Built bootloader stage2..."
	@echo $0

stage2: $(BIN)/stage2.bin

$(BIN)/stage2.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	@echo "Linking stage2..."
	@$(TARGET_LD) $(TARGET_LINKFLAGS) \
		-Wl,-Map=$(BIN)/stage2.map \
		-o $@ $^ $(TARGET_LIBS)

$(BIN)/stage2/c/%.obj: %.c | $(BIN)/stage2/c
	@echo "Compiling     $<"
	@$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ $<

$(BIN)/stage2/asm/%.obj: %.asm | $(BIN)/stage2/asm
	@echo "Compiling     $<"
	@$(TARGET_ASM) $(TARGET_ASMFLAGS) -o $@ $<

$(BIN)/stage2/c:
	@mkdir -p $@

$(BIN)/stage2/asm:
	@mkdir -p $@
