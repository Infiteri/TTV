.PHONY: all header done

all: header $(BIN)/stage1.bin done

header:
	echo "Building bootloader stage1..."

done:
	echo "Built bootloader stage1..."
	@echo $0

$(BIN)/stage1.bin: stage1.asm
	echo "Compiling stage1.asm..."
	@$(ASM) $(ASMFLAGS) stage1.asm -o $(BIN)/stage1.bin
