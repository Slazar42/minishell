/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:47:18 by slazar            #+#    #+#             */
/*   Updated: 2023/10/10 21:47:33 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_perr(char *str, char *token)
{
	write(1, str, ft_strlen(str));
	if (token)
		write(1, token, ft_strlen(token));
	write(1, "\n", 1);
	return (1);
}

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
