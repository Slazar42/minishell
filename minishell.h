/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:15:30 by slazar            #+#    #+#             */
/*   Updated: 2023/09/21 14:37:51 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include"minishell.h"
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

enum e_state
{
	IN_DQUOTE,
	IN_SQUOTE,
	ESCAPED,
	GENERAL,
};

enum e_token
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

typedef struct s_command
{
	char *cmd;
    //struct node *node;
    struct s_command *next ;
	int fd_in;
	int fd_out;
}t_cmd;


typedef struct t_node
{
	char			*content;
	enum e_token	type;
	enum e_state	state;
	int				len;
	struct t_node	*prev;
	struct t_node	*next;
}	t_node;

typedef struct s_lexer
{
	t_node	*head;
	t_node	*tail;
	t_cmd	*cmd;
	int		  size;
}	t_lexer;


typedef struct envirement
{
    char *name;
    char *value;
    struct envirement *next ;
}t_env;

/*execution parttt*/
// typedef struct s_cmd {
//     char** argv;
//     int in;
//     int out;
//     int has_pipe;
//     int has_redir;
//     struct c* next;
//     // redirections l8r
// } t_cmd;


int ft_pwd(int fd_out);
char	*ft_strjoin_free(char const *s1, char const *s2);
int ft_strcmp(char *s1, char *s2);
void ft_unset(char **av, t_env **env);

int builtin(char **av, t_env **env);
int ft_echo(char **av, int fd_out);
char **ft_env(t_env *envirement);
/*-----------------quotes-------------------*/
void join_quotes(t_lexer *lx);
/*-----------------utils-------------------*/
char *ft_strdup_2(char *str,int start,int finish);
int ft_strcmp(char *s1,char *s2);
int if_token(char c);
void ft_initialisation(t_lexer *lx);
/*-----------------lexer-------------------*/
void add_node_to_lexer(t_lexer *lx,char *word,enum e_token token,enum e_state state);
void take_token(char *str,int *i,t_lexer *lx);
int is_alphabet(char c);
int is_digits(char c);
void take_word(char *str, int *i, t_lexer *lx);
int lexer(char *str, t_lexer *lx);
void ft_print_lexer(t_node **head);
void	free_list(t_lexer *lst);
/*-----------ENVIRENEMENT-------------------*/
void take_env(char *str,int *i,t_lexer *lx);
char *get_var_name(char *env);
char *get_var_value(char *env);
void ft_variables(t_env **env,char **envirement);
void print_env(t_env *env);
// void change_dir();
char **ft_env(t_env *envirement);
// typedef struct pars
// {
//     int fd_input; //fd diel input for each cmmd
//     int fd_output; //fd diel aoutput for each cmmd
//     t_env envirement; // struct dial l envierement
//     char **cmmd; //cmmd bles arguments dialha
    
// }
// builtins
// expansion;
// signals
// ecxeve bles ereures dialha
#endif