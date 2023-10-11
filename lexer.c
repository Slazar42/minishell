/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:09:30 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 02:23:43 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void inside_if_question_mark(t_node **cur)
{

	(*cur)->content = ft_strjoin(ft_itoa(g_exit_status), (*cur)->content
			+ 2);
	(*cur)->len = ft_strlen((*cur)->content);
	(*cur)->type = ENV;
}
void	var_from_env(t_env *env, t_lexer *lx)
{
	t_node	*cur;

	cur = lx->head;
	while (cur)
	{
		if (cur->type == ENV && (cur->state == GENERAL|| cur->state == IN_DQUOTE) && ft_strlen(cur->content) > 1)
		{
			if (cur->prev && skip_spaces(cur->prev, 'l')->type == HERE_DOC)
				break;
			if (cur->content[1] == '?')
				inside_if_question_mark(&cur);
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

int	lexer(char *str, t_lexer *lx, t_env *env)
{
	int	i;
	t_node	*head;

	i = 0;
	head = lx->head;
	(void)env;
	while (str && str[i])
	{
		if (str[i] && if_token(str[i]) == 1)
			take_word(str, &i, lx);
		else if (if_token(str[i]) == 0)
			take_token(str, &i, lx);
		else
			i++;
	}
	give_state(&head);
	var_from_env(env, lx);
	head = lx->head;
	if (syntax_error(&head))
		return (g_exit_status = 258, 1);
	return (g_exit_status = 0, 0);
}

void	ft_initialisation(t_lexer *lx)
{
	lx->head = NULL;
	lx->tail = NULL;
	lx->size = 0;
}
