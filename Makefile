NAME = minishell

SRCS = minishell.c lexer.c

CC = gcc

CFLAGS = -Wall -Werror -Wextra 

OBJS = ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lreadline
clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all