NAME = Minishell

SRCS =	main.c \
		utils.c \
		initlst.c \
		builtins.c

SRCS_DIR	= srcs

OBJS = $(SRCS:%.c=%.o)

INC_DIR = include

RDL = -L/usr/lib/ -lreadline

INC = $(INC_DIR)/minishell.h

FS = -fsanitize=address -g3

CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)


CC = gcc 
%.o : 	$(SRCS_DIR)/%.c $(INC)
	$(CC) $(FS) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME) :		$(OBJS)	
			$(CC) $(FS) $(CFLAGS) $(OBJS) $(RDL) -o $(NAME)

clean:
				rm -f $(OBJS)
fclean:		
				rm -f $(OBJS)
				rm -f $(NAME)

re:				fclean all

.PHONY:		all clean fclean re
