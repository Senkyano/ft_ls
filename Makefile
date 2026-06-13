#   NAME
NAME = ft_ls

#---------------#
#	includes
#---------------#
UTILS =		utils
INCLUDES =	include

#--------------------------------------#
#		Commande
#-----------------------#
RM = rm -fr
CC = gcc
FLAGS = -Wall -Werror -Wextra -g -I $(INCLUDES)
# FLAG_READLINE = -lreadline
# FLAG_PHILO = -lpthread -D_REENTRANT
# SANI_MEM = -fsanitize=address -fsanitize=leak -fsanitize=undefined
# SANI = -fsanitize=address -fsanitize=leak -fsanitize=undefined

#--------------------------------------#
#       directory
#-----------------------#
SRCS = srcs
OBJS = objs

#--------------------------------------#
#       Colors
#-----------------------#
C_B = \033[0;30m
C_R = \033[1;31m
C_G = \033[1;32m
C_Y = \033[0;33m
C_BU = \033[0;34m
C_M = \033[0;35m
C_C = \033[0;36m
C_W = \033[0;37m
RESET = \033[0m


#--------------------------------------#
#		File
#-----------------------#
FILE_C =	main.c parsing.c fprintself.c

SRC = $(addprefix $(SRCS)/, $(FILE_C))
OBJ = $(patsubst %.c, $(OBJS)/%.o, $(FILE_C))

# INIT_C = parsing

# SRC_INIT = $(addprefix $(SRCS)/$(INIT)/, $(INIT_C))
# OBJ_INIT = $(patsubst %.c, $(OBJS)/%.o, $(INIT_C))

#--------------------------------------#
#		Rules
#-----------------------#
all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJS)/%.o : $(SRCS)/%.c
	mkdir -p $(OBJS)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS)
	@echo "$(C_R)FILE '*.o' for $(NAME) deleted$(RESET)"

fclean :
	@$(RM) $(NAME)
	@$(RM) $(OBJS)
	@echo "$(C_W)FILE '*.o' for $(C_R)$(NAME) deleted$(RESET)"
	@echo "Projet $(C_R)$(NAME) deleted$(RESET)"

re : fclean all

.PHONY : re clean fclean all