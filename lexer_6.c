/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:08:56 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 23:11:49 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	incrim(t_node **cur)
{
	if (*cur)
		*cur = (*cur)->next;
}

void	give_state(t_lexer *lx)
{
	t_node	*cur;

	cur = lx->head;
	while (cur && cur->next)
	{
		if (cur->type == DOUBLE_QUOTE && cur->next)
		{
			cur = cur->next;
			while (cur && cur->type != DOUBLE_QUOTE)
			{
				cur->state = IN_DQUOTE;
				cur = cur->next;
			}
		}
		else if (cur->type == QOUTE && cur->next)
		{
			cur = cur->next;
			while (cur && cur->type != QOUTE)
			{
				cur->state = IN_SQUOTE;
				cur = cur->next;
			}
		}
		incrim(&cur);
	}
}
