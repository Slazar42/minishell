/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:15:30 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 04:36:04 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell.h"
# include "my_libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int						g_exit_status;

enum					e_state
{
	IN_DQUOTE,
	IN_SQUOTE,
	ESCAPED,
	GENERAL,
};

enum					e_token
{
	HERE_DOC,
	D_REDIR_OUT,
	WORD,
	WHITE_SPACE = ' ',
	TAB = '\t',
	NEW_LINE = '\n',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	QOUTE = '\'',
	ESCAPE = '\\',
	PIPE_LINE = '|',
	REDIR_OUT = '>',
	REDIR_IN = '<',
};
/*-----------yy---------*/
typedef enum
{
	OUT_NONE,
	WRITEOUT,
	APPENDOUT
}						out_redirs;

typedef enum
{
	IN_NONE,
	READIN,
	HEREDOC
}						in_redirs;

typedef struct s_redir
{
	char *in_file;  // linked list or array of strings
	char *out_file; // linked list or array of strings
	char *app_file; // linked list or array of strings
}						t_redir;

/*-----------yy---------*/
typedef struct envirement
{
	char				*name;
	char				*value;
	struct envirement	*next;
	struct envirement	*prev;
}						t_env;

// typedef struct c {
//     char** argv;
//     int in;
//     int out;
//     int has_pipe;

//     // redirections l8r
// } c

// ls -la > ok.txt > ok2.txt > ok3.txt | cat -e
typedef struct s_cmd
{
	char **cmd; // argv: {"cat", "-e", NULL"}
	char				*cmd_path;
	int argc;     // 2
	int fd_in;    // 0
	int fd_out;   // 1
	int has_pipe; // 0
	int					child_pid;
	// >> ola >
	out_redirs out_redir_type; // out_redir = WRITEOUT
								// << ola <
	in_redirs in_redir_type;   // 0
	char *in_file;             // NULL
	char *out_file;            // ok3.txt
	int					herdoc_fd;
	t_env *env; // envierement
	struct s_cmd		*next;
}						t_cmd;

typedef struct t_node
{
	char				*content;
	enum e_token		type;
	enum e_state		state;
	int					len;
	struct t_node		*prev;
	struct t_node		*next;
}						t_node;
/*-----------yy------------*/

typedef struct s_lexer
{
	t_node				*head;
	t_node				*tail;
	int					size;
}						t_lexer;

void					join_quotes(t_lexer *lx);
int						is_buildin(t_cmd *cmd);
void					free_double(char **str);
char					**lincke_list_toaraay(t_env *env);
int						ft_pwd(int fd_out);
int						ft_echo(t_cmd *cmd, int fd_out);
int						execution_builtin(t_cmd *cmd, int i);
char					*ft_genv(t_env *env, char *str);
int						ft_export(t_cmd *cmd);
int						ft_cd(t_cmd *cmd, int fd);
char					**lincke_list_toaraay(t_env *env);
int						ft_unset(t_cmd *cmd);
size_t					ft_envsize(t_env *env);
int						execution_proto(t_cmd *cmd, char **env);
int						ft_exit(t_cmd *cmd);
void					add_new_var(t_env *env, char **var);
int						check_if_exist(t_cmd *cmd, char **var);
char					*find_abs_path(t_env *env, char *cmd);
char					*ft_genv(t_env *env, char *str);
char					**check_invalid_var(char *str);
void					check_redirections(t_cmd *cmd);
char					*ft_genv(t_env *env, char *str);

/*-----------------utils-------------------*/
char					*ft_strdup_2(char *str, int start, int finish);
int						ft_strcmp(char *s1, char *s2);
int						if_token(char c);
void					boucle_norm(t_node **cur, t_cmd **cmd, int *i, int *j);
int						ft_count_cmd(t_lexer *lx);
int						check_space(char *line);
void					ft_initialisation(t_lexer *lx);
void					setup_signal_handlers(void);
void					delete_white_space(t_lexer *lx);
/*-----------------lexer-------------------*/
void					add_node_to_lexer(t_lexer *lx, char *word,
							enum e_token token, enum e_state state);
void					take_token(char *str, int *i, t_lexer *lx);
int						is_alphabet(char c);
t_cmd					*commands(t_lexer *lx);
void					Join_node(char *content, t_node **first, t_node **last,
							enum e_state state, t_lexer *lx);
int						redir_err(t_node *ptr);
void					take_in_dq(t_node **cur, enum e_state state,
							t_lexer *lx);
void					give_state(t_node **head);
int						pipe_err(t_node *elem);
int						is_digits(char c);
void					take_word(char *str, int *i, t_lexer *lx);
void					join_quotes(t_lexer *lx);
int						ft_perr(char *str, char *token);
t_node					*check_quotes(t_node **node, enum e_token quote);
char					*get_token(enum e_token type);
int						if_redirection(enum e_token type);
void					var_from_env(t_env *env, t_lexer *lx);
void					delete_white_space(t_lexer *lx);
int						syntax_error(t_node **cur);
char					*get_env(t_env *env, char *str);
void					join_in_quote_and_word(t_lexer *lx);
t_node					*skip_spaces(t_node *elem, char direction);
int						lexer(char *str, t_lexer *lx, t_env *env);
void					ft_print_lexer(t_node **head);
int						ft_strcmp_EOF(char *s1, char *s2);
void					free_list(t_lexer *lst);
/*-----------ENVIRENEMENT-------------------*/
void					take_env(char *str, int *i, t_lexer *lx);
char					*get_var_name(char *env);
char					*get_var_value(char *env);
void					ft_variables(t_env **env, char **envirement);
void					print_env(t_cmd *cm, t_env *env, char *cmd);

#endif