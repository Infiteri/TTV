include build/Config.mk
include build/Toolchain.mk

makefiles := $(SRC)/bootloader/stage1 $(SRC)/bootloader/stage2 $(SRC)/kernel tools

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
	@dd if=$(BIN)/stage1.bin of=$(BIN)/main_floppy.img conv=notrunc
	@mcopy -i $(BIN)/main_floppy.img $(BIN)/stage2.bin "::stage2.bin"
	@mcopy -i $@ $(BIN)/kernel.bin "::kernel.bin"
	@mcopy -i $(BIN)/main_floppy.img test.txt "::test.txt"

# Make all makefiles
make_all:
	@$(foreach word,$(makefiles), \
		$(MAKE) -s -j12 -C $(word) --no-print-directory;)

# Launch
launch:
	@qemu-system-i386 -fda $(BIN)/main_floppy.img

