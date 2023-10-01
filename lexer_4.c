/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:40:48 by slazar            #+#    #+#             */
/*   Updated: 2023/10/02 00:40:51 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(enum e_token type)
{
	if (type == HERE_DOC)
		return ("<<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == D_REDIR_OUT)
		return (">>");
	else if (type == REDIR_IN)
		return ("<");
	return (".");
}
int	redir_err(t_node *ptr)
{
	t_node	*nxt;

	nxt = skip_spaces(ptr->next, 'r');
	if (!nxt || (nxt->type != WORD && nxt->type != ENV
			&& nxt->type != DOUBLE_QUOTE && nxt->type != QOUTE))
		return (1);
	return (0);
}
t_node	*check_quotes(t_node **node, enum e_token quote)
{
	while (*node)
	{
		*node = (*node)->next;
		if (!*node || (*node)->type == quote)
			break ;
	}
	if (!*node)
		write(1, "minishell: unclosed quotes detected.\n",
				ft_strlen("minishell: unclosed quotes detected.\n"));
	return (*node);
}

int	syntax_error(t_lexer *lst)
{
	t_node	*cur;

	cur = lst->head;
	while (cur)
	{
		if (cur->type == PIPE_LINE)
		{
			if (pipe_err(cur))
				return (ft_perr("minishell: syntax error near "
								"unexpected token `|'",
								0));
		}
		else if (if_redirection(cur->type))
		{
			if (redir_err(cur))
				return (ft_perr("minishell: syntax error near "
								"unexpected token ",
								get_token(cur->type)));
		}
		else if (cur->type == DOUBLE_QUOTE || cur->type == QOUTE)
		{
			if (!check_quotes(&cur, cur->type))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
void	Join_node(char *content, t_node **first, t_node **last,
		enum e_state state, t_lexer *lx)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->content = ft_substr(content, 0, ft_strlen(content));
	new->next = NULL;
	new->prev = NULL;
	new->len = ft_strlen(new->content);
	if (state == IN_DQUOTE)
		new->type = DOUBLE_QUOTE;
	else
		new->type = QOUTE;
	new->state = state;
	if (*first)
		(*first)->next = new;
	new->prev = (*first);
	new->next = (*last);
	if (*last)
		(*last)->prev = new;
	if (!(*first))
		lx->head = new;
}