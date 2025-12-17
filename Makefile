export BIN := $(abspath bin)
export SRC := $(abspath src)
export ASM := nasm
export ASMFLAG = -f bin
export CC = gcc
export CCFLAGS = -g

makefiles := $(SRC)/bootloader $(SRC)/kernel tools

.PHONY: all scaffold make_all

all: scaffold $(BIN)/main_floppy.img

# Scaffold folders
scaffold:
	@mkdir -p $(BIN)

# Main image
$(BIN)/main_floppy.img: make_all
	@echo "Building image..."
	@dd if=/dev/zero of=$(BIN)/main_floppy.img bs=512 count=2880
	@mkfs.fat -F 12 -n "TVOS" $(BIN)/main_floppy.img
	@dd if=$(BIN)/bootloader.bin of=$(BIN)/main_floppy.img conv=notrunc
	@mcopy -i $(BIN)/main_floppy.img $(BIN)/kernel.bin "::kernel.bin"
	@mcopy -i $(BIN)/main_floppy.img test.txt "::test.txt"

# Make all makefiles
make_all:
	@$(foreach word,$(makefiles), \
		$(MAKE) -s -j12 -C $(word) --no-print-directory;)

# Launch
launch:
	@qemu-system-i386 -fda $(BIN)/main_floppy.img

