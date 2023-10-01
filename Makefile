NAME = minishell

SRCS = lexer.c main.c utils.c env.c ./execution/builtin_utils.c ./execution/builtin/ft_pwd.c \
		./execution/builtin/ft_echo.c ./execution/builtin/ft_cd.c ./execution/execution.c \
		./execution/builtin/ft_export.c  ./execution/builtin/ft_unset.c ./execution/builtin/ft_extit.c \
		./lexer_2.c lexer_3.c lexer_4.c lexer_5.c utils_2.c utils_3.c \

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address -g
LDFLAGS = -lreadline 
RLFLGS = -L/Users/slazar/.brew/opt/readline/lib -lreadline #-fsanitize=address
RLOFLGS = -L/Users/slazar/.brew/opt/readline/include
OBJS = ${SRCS:.c=.o} $(LIBFT)

all : $(NAME)
LIBFT = my_libft/libft.a
$(LIBFT):
	make -C my_libft
libft: $(LIBFT)
libft_clean:
	make fclean -C my_libft
libft_re: libft_clean my_libft

$(NAME) : $(OBJS) $(LIBFT) minishell.h
		$(CC) -fsanitize=address -g $(FLAGS) $(OBJS)  -o $(NAME) -I $(LIBFT) $(RLFLGS) $(LDFLAGS)
clean :
	rm -rf $(OBJS)

fclean : clean libft_clean
	rm -rf $(NAME)

re : fclean all
.PHONY = libft libft_clean libft_re