/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:48:07 by slazar            #+#    #+#             */
/*   Updated: 2023/10/10 21:54:01 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	Join_node(char *content, t_node **first, t_node **last,
		enum e_state state, t_lexer *lx)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->content = content;
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
	while (tmp && tmp != (*cur))
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

int ft_strcmp_EOF(char *s1,char *s2)
{
	int i;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if(!s1[i] && !s2[i])
		return (0);
	return (1);
}

char	*get_env(t_env *env, char *str)
{
	t_env	*cur;
	char	*s;

	s = ft_strdup(str + 1);
	free(str);
	cur = env;
	while (cur)
	{
		if (!ft_strcmp_EOF(cur->name, (str + 1)))
		{
			free(s);	
			return (cur->value);
		}
		cur = cur->next;
	}
	free(s);
	return (NULL);
}
