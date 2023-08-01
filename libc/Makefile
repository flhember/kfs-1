#-----------------------------------COLOR VARIABLE--------------------------------#

red_li=$ \033[1;31m
red_da=$ \033[0;31m
grn_li=$ \033[1;32m
grn_da=$ \033[0;32m
whi=$ \033[1;37m
end=$ \033[0m

#-----------------------------------Cross-Compiler--------------------------------#

CC = i686-elf-gcc
CFLAGS += 
ARCC = i686-elf-ar
ARFLAGS +=

NAME = libc.a
#------------------------------------PATH/FILES-----------------------------------#

INC_PATH = ./includes/
SRC_PATH = ./src/
OBJ_PATH = ./obj/

SRC = strlen strcmp memset memcpy memsetw

SRC_FILES = $(SRC:%=%.c)
OBJ_FILES = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))

OBJ = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))

#--------------------------------------RULES--------------------------------------#

all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_FILES): $(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c -I $(INC_PATH) $< -o $@
	@echo "Compilation of $(whi)$(notdir $<)$(grn_da) done.$(end)"

$(NAME): $(OBJ_PATH) $(OBJ_FILES)
	@$(ARCC) $(ARFLAGS) $(NAME) $(OBJ_FILES)
	@echo "$(grn_li)$(notdir $(NAME))$(grn_da) done.$(end)"

clean:
	@rm -Rf $(OBJ_PATH)

fclean: clean
	@rm -Rf $(NAME)
	@echo "$(red_li)$(notdir $(NAME))$(red_da) removed.$(end)"

re: fclean
	@make all

.PHONY: all clean fclean re