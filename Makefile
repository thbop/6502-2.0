CC=gcc
ASM=ca65
LDASM=ld65

BUILD_DIR=build
SRC_DIR=src
SRC_6502=$(SRC_DIR)/6502
SRC_KATTER65=$(SRC_DIR)/Katter65


.PHONY: all clean 6502 bios Katter65

all: clean 6502 bios Katter65

6502: $(BUILD_DIR)/6502.exe
$(BUILD_DIR)/6502.exe: $(BUILD_DIR)/6502.exe
	$(CC) $(SRC_6502)/6502.c -o $(BUILD_DIR)/6502.exe


bios: $(BUILD_DIR)/bios.bin
$(BUILD_DIR)/bios.bin:
	$(ASM) $(SRC_KATTER65)/bios.s -o $(BUILD_DIR)/bios.o
	$(LDASM) -C $(SRC_KATTER65)/linker.cfg $(BUILD_DIR)/bios.o -o $(BUILD_DIR)/bios.bin


Katter65: $(BUILD_DIR)/Katter65.img
$(BUILD_DIR)/Katter65.img:
	dd if=/dev/zero of=$(BUILD_DIR)/Katter65.img bs=512 count=2880
	$(ASM) $(SRC_KATTER65)/bootloader.s -o $(BUILD_DIR)/boot.o
	$(ASM) $(SRC_KATTER65)/main.s -o $(BUILD_DIR)/Katter65.o
	$(LDASM) -C $(SRC_KATTER65)/linker.cfg $(BUILD_DIR)/Katter65.o $(BUILD_DIR)/boot.o -o $(BUILD_DIR)/Katter65.bin
	dd if=$(BUILD_DIR)/Katter65.bin of=$(BUILD_DIR)/Katter65.img conv=notrunc


clean:
	rm -rf $(BUILD_DIR)/*

