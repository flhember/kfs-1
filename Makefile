BIN = kernel
CFG = grub.cfg
ISO_PATH = iso
BOOT_PATH = $(ISO_PATH)/boot
GRUB_PATH = $(BOOT_PATH)/grub

all: bootloader kernel linker iso
	@echo Make has completed

bootloader: boot.asm
	@nasm -f elf32 boot.asm -o boot.o

kernel: kernel.c
	@gcc -m32 -c kernel.c -o kernel.o

linker: linker.ld boot.o kernel.o
	@ld -m elf_i386 -T linker.ld -o kernel boot.o kernel.o

iso: kernel
	@mkdir -pv $(GRUB_PATH)
	@cp $(BIN) $(BOOT_PATH)
	@cp $(CFG) $(GRUB_PATH)
	@grub-file --is-x86-multiboot $(BOOT_PATH)/$(BIN)
	@grub-mkrescue -o my-kernel.iso $(ISO_PATH)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(BIN) *iso

re: fclean
	@make all

.PHONY: all clean fclean re
