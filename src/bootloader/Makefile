.PHONY: all header done

all: header $(BIN)/bootloader.bin done

header:
	echo "Building bootloader..."

done:
	echo "Built bootloader..."
	@echo $0

$(BIN)/bootloader.bin: main.asm
	echo "Compiling main.asm..."
	@$(ASM) $(ASMFLAGS) main.asm -o $(BIN)/bootloader.bin
