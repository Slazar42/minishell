/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:59:48 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 23:15:34 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

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

int	destroy_t_node(t_lexer *lx)
{
	t_node	*tmp;
	t_node	*cur;

	cur = lx->head;
	while (cur)
	{
		tmp = cur->next;
		if (cur->content)
			free(cur->content);
		free(cur);
		cur = tmp;
	}
	lx->head = NULL;
	lx->tail = NULL;
	return (1);
}

int	access_check(t_cmd *cmd)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur)
	{
		if ((cur->in_redir_type == APPENDOUT || cur->in_redir_type == WRITEOUT)
			&& access(cur->in_file, F_OK) == -1)
			return (printf("minishell: %s: No such file or directory\n",
					cur->in_file));
		else if (cur->in_redir_type == READIN
			&& access(cur->in_file, F_OK) == -1)
			return (printf("minishell: %s: No such file or directory\n",
					cur->in_file));
		cur = cur->next;
	}
	return (0);
}

t_cmd	*lexer_to_cmd(t_lexer *lx)
{
	join_quotes(lx);
	join_in_quote_and_word(lx);
	delete_white_space(lx);
	return (commands(lx));
}

void	executtion(t_cmd *cmd, char **str, t_env *env)
{
	cmd->env = env;
	str = lincke_list_toaraay(env);
	execution_proto(cmd, str);
	free_double(str);
	destroy_cmd(cmd);
}
