.PHONY: all header done

all: header $(BIN)/kernel.bin done

header:
	echo "Building kernel..."

done:
	echo "Built kernel..."
	@echo $0

$(BIN)/kernel.bin: main.asm
	echo "Compiling main.asm..."
	@$(ASM) $(ASMFLAGS) main.asm -o $(BIN)/kernel.bin
