/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:43:49 by slazar            #+#    #+#             */
/*   Updated: 2023/10/10 21:50:16 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node_to_lexer(t_lexer *lx, char *word, enum e_token token,
		enum e_state state)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	new->content = word;
	new->type = token;
	new->len = ft_strlen(word);
	new->next = NULL;
	new->prev = NULL;
	new->state = state;
	if (lx->tail)
	{
		lx->tail->next = new;
		new->prev = lx->tail;
	}
	lx->tail = new;
	if (!lx->head)
		lx->head = new;
	lx->size += 1;
}

void	take_token(char *str, int *i, t_lexer *lx)
{
	char	*token;

	if (str[*i] == ENV)
	{
		take_env(str, i, lx);
		return ;
	}
	token = ft_strdup_2(str, *i, *i);
	if (str[*i] == WHITE_SPACE)
		add_node_to_lexer(lx, token, WHITE_SPACE, GENERAL);
	else if (str[*i] == NEW_LINE)
		add_node_to_lexer(lx, token, NEW_LINE, GENERAL);
	else if (str[*i] == QOUTE)
		add_node_to_lexer(lx, token, QOUTE, GENERAL);
	else if (str[*i] == DOUBLE_QUOTE)
		add_node_to_lexer(lx, token, DOUBLE_QUOTE, GENERAL);
	else if (str[*i] == ESCAPE)
		add_node_to_lexer(lx, token, ESCAPE, GENERAL);
	else if (str[*i] == PIPE_LINE)
		add_node_to_lexer(lx, token, PIPE_LINE, GENERAL);
	else if (str[*i] == TAB)
		add_node_to_lexer(lx, token, TAB, GENERAL);
	else if (str[*i] == REDIR_IN && str[(*i) + 1] != REDIR_IN && str[(*i)
		- 1] != REDIR_IN)
		add_node_to_lexer(lx, token, REDIR_IN, GENERAL);
	else if (str[*i] == REDIR_OUT && str[(*i) + 1] != REDIR_OUT && str[(*i)
		- 1] != REDIR_OUT)
		add_node_to_lexer(lx, token, REDIR_OUT, GENERAL);
	else if (str[*i] == REDIR_OUT && str[(*i) + 1] == REDIR_OUT)
	{
		add_node_to_lexer(lx, ft_strdup(">>"), D_REDIR_OUT, GENERAL);
		free(token);
		(*i)++;
	}
	else if (str[*i] == REDIR_IN && str[(*i) + 1] == REDIR_IN)
	{
		add_node_to_lexer(lx, ft_strdup("<<"), HERE_DOC, GENERAL);
		free(token);
		(*i)++;
	}
	(*i)++;
}

int	is_alphabet(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'z'))
		return (0);
	return (1);
}
void	take_word(char *str, int *i, t_lexer *lx)
{
	int		start;
	char	*word;

	start = *i;
	while (str[*i] && if_token(str[*i]) == 1)
		(*i)++;
	word = ft_strdup_2(str, start, *i - 1);
	add_node_to_lexer(lx, word, WORD, GENERAL);
}