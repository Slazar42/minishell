/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:09:30 by slazar            #+#    #+#             */
/*   Updated: 2023/10/12 00:12:05 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env *env, char *str)
{
	t_env	*cur;
	char	*s;

	s = ft_strdup(str + 1);
	free(str);
	cur = env;
	while (cur)
	{
		if (!ft_strcmp_eof(cur->name, (str + 1)))
		{
			free(s);
			return (cur->value);
		}
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
				|| cur->state == IN_DQUOTE) && ft_strlen(cur->content) > 1 
			&& (cur->prev && skip_spaces(cur->prev, 'l')->type != HERE_DOC))
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

int	lexer(char *str, t_lexer *lx, t_env *env)
{
	int	i;

	i = 0;
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
	give_state(lx);
	var_from_env(env, lx);
	if (syntax_error(lx))
		return (g_exit_status = 258, 1);
	return (g_exit_status = 0, 0);
}

void	ft_initialisation(t_lexer *lx)
{
	lx->head = NULL;
	lx->tail = NULL;
	lx->size = 0;
}

// void	ft_print_lexer(t_node **head)
// {
// 	t_node	*cur;
// 	char	*state;

// 	cur = *head;
// 	char general[] = "GENERAL";
// 	char in_s_quote[] = "IN_S_QUOTE";
// 	char in_d_quote[] = "IN_D_QUOTE";
// 	printf("-----------------------------------------------------------\n");
// 	printf("|%-17s|%3s|%15s|      token    |\n", "content", "len", "state");
// 	printf("-----------------------------------------------------------\n");
// 	while (cur)
// 	{
// 		if (cur->state == IN_DQUOTE)
// 			state = in_d_quote;
// 		else if (cur->state == IN_SQUOTE)
// 			state = in_s_quote;
// 		else if (cur->state == GENERAL)
// 			state = general;
// 		printf("|%-17s|%4d|%-15s|", cur->content, cur->len, state);
// 		if (cur->type == WORD)
// 			printf("      WORD    |\n");
// 		else if (cur->type == WHITE_SPACE)
// 			printf("      WHITE_SPACE    |\n");
// 		else if (cur->type == NEW_LINE)
// 			printf("       NEW_LINE     |\n");
// 		else if (cur->type == QOUTE)
// 			printf("      QOUTE    |\n");
// 		else if (cur->type == DOUBLE_QUOTE)
// 			printf("     DOUBLE_QUOTE     |\n");
// 		else if (cur->type == ESCAPE)
// 			printf("      ESCAPE     |\n");
// 		else if (cur->type == ENV)
// 			printf("     ENV    |\n");
// 		else if (cur->type == PIPE_LINE)
// 			printf("     PIPE_LINE     |\n");
// 		else if (cur->type == REDIR_IN)
// 			printf("    REDIR_IN     |\n");
// 		else if (cur->type == TAB)
// 			printf("    TAB     |\n");
// 		else if (cur->type == REDIR_OUT)
// 			printf("     REDIR_OUT    |\n");
// 		else if (cur->type == D_REDIR_OUT)
// 			printf("     DREDIR_OUT     |\n");
// 		else if (cur->type == HERE_DOC)
// 			printf("    HERE_DOC    |\n");
// 		printf("-----------------------------------------------------------\n");
// 		cur = cur->next;
// 	}
// }
