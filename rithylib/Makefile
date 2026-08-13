FILE_C = isspecial.c \
		 fprintself.c \
		 strdupself.c \
		 strlen.c \
		 joinstr.c

NAME = rithylib.a

SRCS = srcs
OBJS = objs
INCLUDES = include

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES)
AR = ar rcs

SRC = $(addprefix $(SRCS)/, $(FILE_C))
OBJ = $(patsubst %.c, $(OBJS)/%.o, $(FILE_C))

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJS)/%.o: $(SRCS)/%.c | $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS) :
	mkdir -p $(OBJS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re