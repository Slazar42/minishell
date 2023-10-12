/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:15:30 by slazar            #+#    #+#             */
/*   Updated: 2023/10/12 00:12:19 by slazar           ###   ########.fr       */
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

int	g_exit_status;

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
typedef enum e_s
{
	OUT_NONE,
	WRITEOUT,
	APPENDOUT
}	t_outredirs;

typedef enum e_p
{
	IN_NONE,
	READIN,
	HEREDOC
}	t_inredirs;

typedef struct s_redir
{
	char	*in_file;
	char	*out_file;
	char	*app_file;
}						t_redir;

/*-----------yy---------*/
typedef struct envirement
{
	char				*name;
	char				*value;
	struct envirement	*next;
	struct envirement	*prev;
}						t_env;

typedef struct s_cmd 
{
	char			**cmd;
	char			*cmd_path;
	int				argc;
	int				fd_in;
	int				fd_out;
	int				has_pipe;
	char			*raw_path;
	char			**path_arr;
	int				i;
	char			*fwd_slash;
	char			*abs_path;
	int				child_pid;
	t_outredirs		out_redir_type;
	t_inredirs		in_redir_type;
	char			*in_file;
	char			*out_file;
	int				herdoc_fd; 
	t_env			*env;
	struct s_cmd	*next;
}t_cmd;

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
int						exec(t_cmd *cmd, char **env, int **pipe_fd);
void					ft_close(t_cmd *cmd, int **pipe_fd);
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
void					ft_free_array(char **array);
void					take_env(char *str, int *i, t_lexer *lx);
int						if_token(char c);
void					executtion(t_cmd *cmd, char **str, t_env *env);
t_cmd					*lexer_to_cmd(t_lexer *lx);
void					destroy_cmd(t_cmd *cmd);
t_node					*create_cmd(t_lexer *lx, t_cmd *cmd);
int						destroy_t_node(t_lexer *lx);
void					boucle_norm(t_node **cur, t_cmd **cmd, int *i, int *j);
int						access_check(t_cmd *cmd);
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
t_node					*join_node(t_node **first, t_node **last,
							enum e_state state, t_lexer *lx);
void					incrim(t_node **cur);
int						redir_err(t_node *ptr);
void					give_state(t_lexer *lx);
void					take_in_dq(t_node **cur, enum e_state state,
							t_lexer *lx);
void					give_state(t_lexer *lx);
int						pipe_err(t_node *elem);
void					execute_command_v2(t_cmd *cmd, char **env);
void					execute_command_v1(t_cmd *cmd, char **env);
int						is_digits(char c);
int						built_in(t_cmd *cmd);
void					take_word(char *str, int *i, t_lexer *lx);
void					join_quotes(t_lexer *lx);
int						ft_perr(char *str, char *token);
t_node					*check_quotes(t_node **node, enum e_token quote);
char					*get_token(enum e_token type);
int						if_redirection(enum e_token type);
void					var_from_env(t_env *env, t_lexer *lx);
void					delete_white_space(t_lexer *lx);
int						syntax_error(t_lexer *lx);
char					*get_env(t_env *env, char *str);
void					join_in_quote_and_word(t_lexer *lx);
t_node					*skip_spaces(t_node *elem, char direction);
int						lexer(char *str, t_lexer *lx, t_env *env);
void					ft_print_lexer(t_node **head);
int						ft_strcmp_eof(char *s1, char *s2);
void					free_list(t_lexer *lst);
/*-----------ENVIRENEMENT-------------------*/
void					take_env(char *str, int *i, t_lexer *lx);
char					*get_var_name(char *env);
char					*get_var_value(char *env);
void					ft_variables(t_env **env, char **envirement);
void					print_env(t_cmd *cm, t_env *env, char *cmd);

#endif