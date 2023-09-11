/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:15:30 by slazar            #+#    #+#             */
/*   Updated: 2023/09/09 13:43:32 by slazar           ###   ########.fr       */
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
	WORD = -1,
	WHITE_SPACE = ' ',
	TAB = '\t',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	D_REDIR_OUT,
};

typedef struct s_elem
{
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	struct s_elem	*next;
	struct s_elem	*prev;
}	t_elem;

typedef struct s_nodes
{
	t_elem	*head;
	t_elem	*tail;
	int		  size;
}	t_nodes;


typedef struct envirement
{
    char *name;
    char *value;
    struct envirement *next ;
}t_env;


/*-----------------utils-------------------*/
char *ft_strdup_2(char *str,int start,int finish);
int ft_strcmp(int *s1,int *s2);
int if_token(char c);
void ft_initialisation(t_nodes *lx);
/*-----------------lexer-------------------*/
void add_node_to_lexer(t_nodes *lx,char *word,enum e_token token,enum e_state state);
void take_token(char *str,int *i,t_nodes *lx);
int is_alphabet(char c);
int is_digits(char c);
void take_word(char *str, int *i, t_nodes *lx);
void lexer(char *str, t_nodes *lx);
void ft_print_lexer(t_elem **head);
void	free_list(t_nodes *lst);
/*-----------ENVIRENEMENT-------------------*/
void take_env(char *str,int *i,t_nodes *lx);
char *get_var_name(char *env);
char *get_var_value(char *env);
void ft_variables(t_env **env,char **envirement);
void print_env(t_env *env);

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