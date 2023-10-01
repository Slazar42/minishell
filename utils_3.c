/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:43:57 by slazar            #+#    #+#             */
/*   Updated: 2023/10/02 00:43:59 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_node **cur, t_cmd *cmd)
{
	if ((*cur)->type == REDIR_IN)
	{
		if (!cmd->in_file)
			free(cmd->in_file);
		cmd->in_file = ft_strdup((*cur)->next->content);
		cmd->in_redir_type = READIN;
	}
	else if ((*cur)->type == REDIR_OUT)
	{
		if (!cmd->out_file)
			free(cmd->out_file);
		cmd->out_file = ft_strdup((*cur)->next->content);
		cmd->out_redir_type = WRITEOUT;
	}
	else if ((*cur)->type == D_REDIR_OUT)
	{
		if (!cmd->out_file)
			free(cmd->out_file);
		cmd->out_file = ft_strdup((*cur)->next->content);
		cmd->out_redir_type = APPENDOUT;
	}
	else if ((*cur)->type == HERE_DOC)
	{
		if (!cmd->in_file)
			free(cmd->in_file);
		cmd->in_file = ft_strdup((*cur)->next->content);
		cmd->in_redir_type = HEREDOC;
	}
	(*cur) = (*cur)->next->next;
}

void	check_next_next(t_node *cur)
{
	int	tmp_fd;

	if (cur->next->next && (cur->next->next->type == REDIR_IN
			|| cur->next->next->type == REDIR_OUT
			|| cur->next->next->type == D_REDIR_OUT))
	{
		tmp_fd = open(cur->next->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(tmp_fd);
	}
}
void	create_cmd(t_lexer *lx, t_cmd *cmd)
{
	t_node	*cur;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cur = lx->head;
	cmd->fd_out = 1;
	while (cur)
	{
		if (cur->type == REDIR_IN || cur->type == REDIR_OUT
			|| cur->type == D_REDIR_OUT || cur->type == HERE_DOC)
		{
			check_next_next(cur);
			redirect(&cur, cmd);
			continue ;
		}
		if (cur->type == PIPE_LINE)
		{
			cmd->cmd = malloc(sizeof(char *) * (j + 1));
			cmd->cmd[j] = NULL;
			cmd->next = malloc(sizeof(t_cmd));
			ft_memset(cmd->next, 0, sizeof(t_cmd));
			cmd = cmd->next;
			i++;
			cmd->fd_out = 1;
			j = 0;
		}
		else
			j++;
		cur = cur->next;
	}
	cmd->cmd = malloc(sizeof(char *) * (j + 1));
	cmd->cmd[j] = NULL;
	cmd->next = NULL;
}

t_cmd	*commands(t_lexer *lx)
{
	t_node	*cur;
	t_cmd	*cmd;
	t_cmd	*head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = malloc(sizeof(t_cmd) * (ft_count_cmd(lx) + 1));
	ft_memset(cmd, 0, sizeof(t_cmd));
	head = cmd;
	create_cmd(lx, cmd);
	cur = lx->head;
	while (cur)
	{
		if (cur->type == PIPE_LINE)
		{
			cmd->cmd[j] = NULL;
			i++;
			j = 0;
			cmd = cmd->next;
		}
		else if (cur->type == REDIR_IN || cur->type == REDIR_OUT
				|| cur->type == D_REDIR_OUT || cur->type == HERE_DOC
				|| (cur->type == WORD && cur->prev
					&& (cur->prev->type == REDIR_IN
						|| cur->prev->type == REDIR_OUT
						|| cur->prev->type == D_REDIR_OUT
						|| cur->prev->type == HERE_DOC)))
		{
			cur = cur->next->next;
			continue ;
		}
		else
		{
			cmd->cmd[j] = ft_strdup(cur->content);
			j++;
		}
		cur = cur->next;
	}
	cmd->cmd[j] = NULL;
	return (head);
}

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(", ");
		i++;
	}
	printf("\n");
}