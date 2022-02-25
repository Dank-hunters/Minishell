NAME = Minishell

SRCS =	main.c \
		error.c \
		environment.c \
		initlst.c \
		parsing.c \
		split_pipes.c \
		split_args.c \
		builtins.c \
		display_utils.c \
		str_utils.c \
		str_utils2.c \
		lst_utils.c \
		dollar.c \
		norm_alloc.c

SRCS_DIR	= srcs

OBJS = $(SRCS:%.c=%.o)

INC_DIR = include

RDL = -L/usr/lib/ -lreadline

INC = $(INC_DIR)/minishell.h

FS = -fsanitize=address -g3

#FS  =  -Wall

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
