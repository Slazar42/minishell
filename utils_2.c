/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:54:06 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 02:35:23 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_sp_tab(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (*line)
		return (1);
	return (0);
}

int	check_space(char *line)
{
	if (*line == '\0' || only_sp_tab(line) == 0)
		return (0);
	return (1);
}

void	join_in_quote_and_word(t_lexer *lx)
{
	t_node	*tmp;
	t_node	*cur;

	cur = lx->head;
	while (cur)
	{
		if (cur->next && ((cur->type == QOUTE || cur->type == DOUBLE_QUOTE
					|| cur->type == WORD) && (cur->next->type == QOUTE
					|| cur->next->type == DOUBLE_QUOTE
					|| cur->next->type == WORD)))
		{
			tmp = cur->next;
			cur->content = ft_strjoin(cur->content, tmp->content);
			cur->len = ft_strlen(cur->content);
			cur->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = cur;
			free(tmp->content);
			free(tmp);
			lx->size -= 1;
			cur = lx->head;
		}
		cur = cur->next;
	}
}

int	ft_count_cmd(t_lexer *lx)
{
	t_node	*tmp;
	int		count;

	count = 0;
	tmp = lx->head;
	while (tmp)
	{
		if (tmp->type == PIPE_LINE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	init_cmd_struct(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->fd_in = 0;
	(*cmd)->fd_out = 1;
	(*cmd)->in_file = NULL;
	(*cmd)->out_file = NULL;
}
