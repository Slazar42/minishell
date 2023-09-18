NAME = minishell

SRCS = lexer.c main.c utils.c env.c

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

OBJS = ${SRCS:.c=.o} $(LIBFT)

all : $(NAME)
LIBFT = libft/libft.a
$(LIBFT):
	make -C libft
libft: $(LIBFT)
libft_clean:
	make fclean -C libft
libft_re: libft_clean libft

$(NAME) : $(OBJS) $(LIBFT) minishell.h
		$(CC)   $(FLAGS) $(OBJS)  -o $(NAME) -I $(LIBFT) -lreadline
clean :
	rm -rf $(OBJS)

fclean : clean libft_clean
	rm -rf $(NAME)

re : fclean all
.PHONY = libft libft_clean libft_re