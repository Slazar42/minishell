/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:24:41 by slazar            #+#    #+#             */
/*   Updated: 2023/09/19 21:11:31 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// hy younes

int only_sp_tab(char *line)
{
	while (*line && ( *line == ' ' || *line == '\t'))
		line++;
	return(*line ? 1 : 0);
}
int check_space(char *line)
{
	if(*line == '\0' || only_sp_tab(line) == 0)
		return(0);
	return(1);
}
void join_in_quote_and_word(t_lexer *lx)
{
	t_node *tmp;
	t_node *cur;
	
	cur = lx->head;
	while(cur)
	{
		if(cur->next && ((cur->type == QOUTE || cur->type == DOUBLE_QUOTE || cur->type == WORD ) && \
			(cur->next->type == QOUTE || cur->next->type == DOUBLE_QUOTE || cur->next->type == WORD)))
		{
			tmp = cur->next;
			cur->content = ft_strjoin(cur->content,tmp->content);
			cur->len = ft_strlen(cur->content);
			cur->next = tmp->next;
			if(tmp->next)
				tmp->next->prev = cur;
			free(tmp->content);
			free(tmp);
			lx->size -= 1;
			cur = lx->head;
		}
		cur = cur->next;
	}
}
int main(int __unused ac,char **av,char **envirement)
{
    (void) ac;
    (void) av;
    t_env *env;
    ft_variables(&env,envirement);
	t_lexer lx;
	char *line;

	while (1)
	{
		ft_initialisation(&lx);
		line = readline("minishell ");
		if (!line)
			printf("Error\n");
		else if (check_space(line) == 0)
			continue;
		else if(!ft_strcmp(line,"env"))
            print_env(env);
		else
		{
			add_history(line);
			if(lexer(line, &lx, env))
				continue;
			else
			{
				ft_print_lexer(&lx.head);
				join_quotes(&lx);
				join_in_quote_and_word(&lx);
				delete_white_space(&lx);
				ft_print_lexer(&lx.head);
			}
			// free_list(&lx);
		}
	}
	if(line)
		free(line);
}
