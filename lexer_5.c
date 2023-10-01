/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:41:37 by slazar            #+#    #+#             */
/*   Updated: 2023/10/02 00:41:40 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_in_dq(t_node **cur, enum e_state state, t_lexer *lx)
{
	char	*new_cont;
	t_node	*tmp;
	t_node	*ptr;

	tmp = (*cur);
	new_cont = ft_calloc(1, 1);
	(*cur) = (*cur)->next;
	while ((*cur) && (*cur)->state == state)
	{
		new_cont = ft_strjoin(new_cont, (*cur)->content);
		(*cur) = (*cur)->next;
	}
	Join_node(new_cont, &tmp->prev, cur, state, lx);
	while (tmp && tmp->state == state)
	{
		free(tmp->content);
		ptr = tmp->next;
		free(tmp);
		tmp = ptr;
		lx->size -= 1;
	}
}
void	join_quotes(t_lexer *lx)
{
	t_node	*cur;

	cur = lx->head;
	while (cur)
	{
		if (cur->type == DOUBLE_QUOTE)
			take_in_dq(&cur, IN_DQUOTE, lx);
		else if (cur->type == QOUTE)
			take_in_dq(&cur, IN_SQUOTE, lx);
		else
			cur = cur->next;
	}
}
void	delete_white_space(t_lexer *lx)
{
	t_node	*cur;
	t_node	*tmp;

	cur = lx->head;
	while (cur)
	{
		if (cur->type == WHITE_SPACE || cur->type == TAB || (cur->type == QOUTE
				&& !cur->len) || (cur->type == DOUBLE_QUOTE && !cur->len))
		{
			tmp = cur->next;
			if (cur->prev)
				cur->prev->next = cur->next;
			if (cur->next)
				cur->next->prev = cur->prev;
			if (cur == lx->head)
				lx->head = cur->next;
			if (cur == lx->tail)
				lx->tail = cur->prev;
			free(cur->content);
			free(cur);
			lx->size -= 1;
			cur = tmp;
		}
		else
			cur = cur->next;
	}
}

char	*get_env(t_env *env, char *str)
{
	t_env	*cur;
	char	*s;

	s = ft_strdup(str + 1);
	cur = env;
	while (cur)
	{
		if (!ft_strncmp(cur->name, (str + 1), ft_strlen(s)))
			return (cur->value);
		cur = cur->next;
	}
	free(s);
	return (NULL);
}

void	var_from_env(t_env *env, t_lexer *lx)
{
	t_node	*cur;

	cur = lx->head;
	while (cur)
	{
		if (cur->type == ENV && (cur->state == GENERAL
				|| cur->state == IN_DQUOTE) && ft_strlen(cur->content) > 1)
		{
			if (cur->content[1] == '?')
			{
				cur->content = ft_strjoin(ft_itoa(g_exit_status), cur->content
						+ 2);
				cur->len = ft_strlen(cur->content);
				cur->type = ENV;
			}
			else
			{
				cur->content = ft_strdup(get_env(env, cur->content));
				cur->len = ft_strlen(cur->content);
				cur->type = ENV;
			}
		}
		cur = cur->next;
	}
}