BIN = kernel
CFG = grub.cfg
ISO_PATH = isodir
BOOT_PATH = $(ISO_PATH)/boot
GRUB_PATH = $(BOOT_PATH)/grub
ISO = my-kernel.iso

all: bootloader kernel linker iso
	@echo Make has completed

bootloader: boot.s
	@i686-elf-as boot.s -o boot.o

kernel: kernel.c
	@i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra 

linker: linker.ld boot.o kernel.o
	@i686-elf-gcc -T linker.ld -o kernel -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

iso: kernel
	@mkdir -pv $(GRUB_PATH)
	@cp $(BIN) $(BOOT_PATH)
	@cp $(CFG) $(GRUB_PATH)
	@grub-file --is-x86-multiboot $(BOOT_PATH)/$(BIN)
	@grub-mkrescue -o $(ISO) $(ISO_PATH)
	@qemu-system-i386 $(ISO)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(BIN) $(ISO_PATH) $(ISO)

re: fclean
	@make all

.PHONY: all clean fclean re
