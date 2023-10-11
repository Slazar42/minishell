/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:43:38 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 02:22:09 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	give_state(t_node	**cur)
{
	while ((*cur) && (*cur)->next)
	{
		if ((*cur)->type == DOUBLE_QUOTE && (*cur)->next)
		{
			(*cur) = (*cur)->next;
			while ((*cur) && (*cur)->type != DOUBLE_QUOTE)
			{
				(*cur)->state = IN_DQUOTE;
				(*cur) = (*cur)->next;
			}
		}
		else if ((*cur)->type == QOUTE && (*cur)->next)
		{
			(*cur) = (*cur)->next;
			while ((*cur) && (*cur)->type != QOUTE)
			{
				(*cur)->state = IN_SQUOTE;
				(*cur) = (*cur)->next;
			}
		}
		if ((*cur))
			(*cur) = (*cur)->next;
	}
}
void	free_list(t_lexer *lst)
{
	t_node	*tmp;

	if (!lst)
		return ;
	tmp = lst->head;
	while (tmp)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
}

int	if_redirection(enum e_token type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == D_REDIR_OUT
		|| type == HERE_DOC)
		return (1);
	return (0);
}

t_node	*skip_spaces(t_node *elem, char direction)
{
	while (elem && (elem->type == WHITE_SPACE || elem->type == TAB))
	{
		if (direction == 'l')
			elem = elem->prev;
		else if (direction == 'r')
			elem = elem->next;
	}
	return (elem);
}

int	pipe_err(t_node *elem)
{
	t_node	*next;
	t_node	*prev;

	next = skip_spaces(elem->next, 'r');
	prev = skip_spaces(elem->prev, 'l');
	if (!next || !prev || (next->type != WORD
			&& if_redirection(next->type) == 0))
		return (1);
	return (0);
}
