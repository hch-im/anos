#################################################
#	Make boot loader.
#################################################

all: bootloader.bin
	@echo "--------------------------------------"
	@echo "Successfully generate bootloader.bin"
	@echo "--------------------------------------"

bootloader.bin: boot_loader.asm
	@echo "--------------------------------------"
	@echo "Generate bootloader.bin"
	@echo "--------------------------------------"	
	nasm $< -f bin -o $@

clean:
	@echo "--------------------------------------"
	@echo "Clean boot subdirectory"
	@echo "--------------------------------------"	
	rm *.bin

.PHONY: all	bootloader.bin clean