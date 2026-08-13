#   NAME
NAME = ft_ls

#---------------#
#   includes & libs
#---------------#
INCLUDES = include

# 1. Emplacements de ta librairie
LIB_DIR  = rithylib
LIB_NAME = rithylib.a
LIB_A    = $(LIB_DIR)/$(LIB_NAME)

#--------------------------------------#
#       Commande
#-----------------------#
RM = rm -fr
CC = gcc

# 2. Flags d'inclusion des headers (-I) et de liaison de la lib (-L et -l)
# Note: -l:rithylib.a permet de lier directement le fichier .a sans renommage "lib"
FLAGS = -Wall -Werror -Wextra -g -I $(INCLUDES) -I $(LIB_DIR)/include
LDFLAGS = -L $(LIB_DIR) -l:$(LIB_NAME)

#--------------------------------------#
#       directory
#-----------------------#
SRCS = srcs
OBJS = objs

#--------------------------------------#
#       Colors
#-----------------------#
C_R   = \033[1;31m
C_G   = \033[1;32m
C_W   = \033[0;37m
RESET = \033[0m

#--------------------------------------#
#       File
#-----------------------#
FILE_C = main.c parsing.c exploringfile.c printinfols.c

OBJ = $(patsubst %.c, $(OBJS)/%.o, $(FILE_C))

#--------------------------------------#
#       Rules
#-----------------------#
all : $(NAME)

$(NAME) : $(LIB_A) $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo "$(C_G)Compilation de $(NAME) réussie !$(RESET)"

$(LIB_A) :
	@make -C $(LIB_DIR)

$(OBJS)/%.o : $(SRCS)/%.c
	@mkdir -p $(OBJS)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	@make -C $(LIB_DIR) clean
	@$(RM) $(OBJS)
	@echo "$(C_R)FILE '*.o' for $(NAME) deleted$(RESET)"

fclean : clean
	@make -C $(LIB_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(C_W)FILE '$(NAME)' deleted$(RESET)"

re : fclean all

.PHONY : re clean fclean all