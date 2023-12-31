NAME = minishell

SRCS = lexer.c main.c utils.c env.c ./execution/builtin_utils.c ./execution/builtin/ft_pwd.c \
		./execution/builtin/ft_echo.c ./execution/builtin/ft_cd.c ./execution/execution.c \
		./execution/builtin/ft_export.c  ./execution/builtin/ft_unset.c ./execution/builtin/ft_extit.c \
		./execution/builtin/export_utils.c ./execution/find_path.c ./execution/redirection.c \
		./execution/path_utils.c  lexer_2.c lexer_3.c lexer_4.c lexer_5.c \
		./execution/exex_utils.c utils_2.c utils_3.c utils_4.c utils_5.c lexer_6.c \

CC = cc

CFLAGS = -Wall -Werror -Wextra 
GG = -lreadline 
LDFLAGS="-L/Users/yberrim/.brew/opt/readline/lib"
CPPFLAGS="-I/Users/yberrim/.brew/opt/readline/include"
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
		$(CC) $(CFLAGS) $(OBJS)  -o $(NAME) -I $(LIBFT) ${GG} $(LDFLAGS) $(CPPFLAGS)
clean :
	rm -rf $(OBJS)

fclean : clean libft_clean
	rm -rf $(NAME)

re : fclean all
.PHONY = libft libft_clean libft_re all clean fclean re