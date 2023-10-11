/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:24:41 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 02:06:37 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
	if (array)
    	free(array);
}

void    destroy_cmd(t_cmd *cmd)
{
    t_cmd    *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        ft_free_array(cmd->cmd);
		if (cmd->in_file)
			free(cmd->in_file);
		if (cmd->out_file)
			free(cmd->out_file);
        free(cmd);
        cmd = tmp;
    }
}

void destroy_t_node(t_lexer *lx)
{
    t_node *tmp;
    t_node *cur;

    cur = lx->head;
    while (cur)
    {
        tmp = cur->next;
		if(cur->content)
        	free(cur->content);
        free(cur);
        cur = tmp;
    }
    lx->head = NULL;
    lx->tail = NULL;
}
int access_check(t_cmd *cmd)
{
	t_cmd *cur;

	cur = cmd;
	while (cur)
	{
		if (cur->in_redir_type == APPENDOUT || cur->in_redir_type == WRITEOUT)
		{
			if (access(cur->in_file, F_OK) == -1)
			{
				printf("minishell: %s: No such file or directory\n", cur->in_file);
				return (1);
			}
		}
		else if (cur->in_redir_type == READIN)
		{
			if (access(cur->in_file, F_OK) == -1)
			{
				printf("minishell: %s: No such file or directory\n", cur->in_file);
				return (1);
			}
		}
		cur = cur->next;
	}
	return (0);
}
int	main(int __unused ac, char __unused **av, char **envirement)
{
	char	*line;
	t_env	*env;
	t_lexer	lx;
	t_cmd	*cmd;

	cmd = NULL;
	ft_variables(&env, envirement);
	setup_signal_handlers();
	while (1)
	{
		
		ft_initialisation(&lx);
		line = readline("minishell $-> ");
		if (!line)
			return (1);
		else if (check_space(line) == 0)
			continue ;
		else
		{
			add_history(line);
			if (lexer(line, &lx, env))
				continue ;
			else
			{
				join_quotes(&lx);
				join_in_quote_and_word(&lx);
				delete_white_space(&lx);
				cmd = commands(&lx);
				if(access_check(cmd))
				{
					destroy_cmd(cmd);
					continue ;
				}
				cmd->env = env;
				char **str = lincke_list_toaraay(env);
				execution_proto(cmd, str);
				free_double(str);
				destroy_cmd(cmd);
			}
		}
		destroy_t_node(&lx);
		if (line)
			free(line);
	}
}
