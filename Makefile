#-----------------------------------COLOR VARIABLE--------------------------------#

red_li=$ \033[1;31m
red_da=$ \033[0;31m
grn_li=$ \033[1;32m
grn_da=$ \033[0;32m
whi=$ \033[1;37m
end=$ \033[0m

#-----------------------------------Cross-Compiler--------------------------------#

CC = i686-elf-gcc
CFLAGS += -ffreestanding -nostdlib -O2

ASCC = i686-elf-as
ASFLAGS +=

QEMU = qemu-system-i386

#------------------------------------PATH/FILES-----------------------------------#

ISO = my-kernel.iso
CFG = grub.cfg

ISO_PATH = isodir
BOOT_PATH = $(ISO_PATH)/boot
GRUB_PATH = $(BOOT_PATH)/grub
ARCH_PATH = arch/i386
OBJ_PATH = $(shell pwd)/kernel/obj
LIB_PATH = libc/
LIB = libc.a
OBJ = obj/

BOOT_FILE = $(ARCH_PATH)/boot.s
GRUB_FILE = $(ARCH_PATH)/grub.cfg
LINK_FILE = $(ARCH_PATH)/linker.ld
OBJ_FILES = $(shell find $(OBJ_PATH) -type f -name "*.o")

BIN = kfs-1

#--------------------------------------RULES--------------------------------------#

all: build linker iso boot
	@echo Make has completed

build:
	@make -C libc/
	@make -C kernel/
	@$(ASCC) $(BOOT_FILE) -o $(OBJ_PATH)/boot.o

linker: build 
	@$(CC) -T $(LINK_FILE) -o $(BIN) $(CFLAGS) $(OBJ_FILES) -lgcc $(LIB_PATH)$(LIB)

iso: build linker
	@mkdir -pv $(GRUB_PATH)
	@cp $(BIN) $(BOOT_PATH)
	@cp $(GRUB_FILE) $(GRUB_PATH)
	@grub-file --is-x86-multiboot $(BOOT_PATH)/$(BIN)
	@grub-mkrescue -o $(ISO) $(ISO_PATH)

boot: build linker iso
	@$(QEMU) $(ISO)

		#ERROR
clean:
	@rm -rf kernel/$(OBJ)
	@rm -rf $(LIB_PATH)$(OBJ)

fclean: clean
	@rm -rf $(BIN) $(ISO_PATH) $(ISO)
	@rm -rf $(LIB_PATH)$(LIB)

re: fclean
	@make all

.PHONY: all clean fclean re build linker iso boot

