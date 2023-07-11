#-----------------------------------COLOR VARIABLE--------------------------------#

red_li=$ \033[1;31m
red_da=$ \033[0;31m
grn_li=$ \033[1;32m
grn_da=$ \033[0;32m
whi=$ \033[1;37m
end=$ \033[0m

#-----------------------------------Cross-Compiler--------------------------------#

CC = i686-elf-gcc
CFLAGS += -ffreestanding -nostdlib -c
NAME = kernel

#------------------------------------PATH/FILES-----------------------------------#

INC_PATH = ./includes/
SRC_PATH = ./src/
OBJ_PATH = ./obj/

KRL_FILES = kernel tty keyboard
INC_FILES = kernel.h

SRC_FILES = $(KRL_FILES:%=%.c)
OBJ_FILES = $(KRL_FILES:%=%.o)

OBJ = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))

#--------------------------------------RULES--------------------------------------#

all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -I $(INC_PATH) $< -o $@
	@echo "Compilation of $(whi)$(notdir $<)$(grn_da) done.$(end)"

$(NAME): $(OBJ_PATH) $(OBJ)

clean:
	@rm -R $(OBJ_PATH)
	@echo "$(red_li)Objects files of $(notdir $(NAME))$(red_da) removed.$(end)"

re: clean
	@make all -s

.PHONY: all clean re