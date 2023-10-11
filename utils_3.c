/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:55:21 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 01:55:26 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_node **cur, t_cmd *cmd)
{
	if ((*cur)->type == REDIR_IN)
	{
		if (cmd->in_file)
			free(cmd->in_file);
		cmd->in_file = ft_strdup((*cur)->next->content);
		cmd->in_redir_type = READIN;
	}
	else if ((*cur)->type == REDIR_OUT)
	{
		if (cmd->out_file)
			free(cmd->out_file);
		cmd->out_file = ft_strdup((*cur)->next->content);
		cmd->out_redir_type = WRITEOUT;
	}
	else if ((*cur)->type == D_REDIR_OUT)
	{
		if (cmd->out_file)
			free(cmd->out_file);
		cmd->out_file = ft_strdup((*cur)->next->content);
		cmd->out_redir_type = APPENDOUT;
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
		tmp_fd = open(cur->next->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		close(tmp_fd);
	}
}

void	here_doc(t_node **cur, t_cmd **cmd)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (ft_strcmp(line, (*cur)->next->content) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	close(fd);
	(*cmd)->in_file = ft_strdup("/tmp/heredoc");
	(*cmd)->in_redir_type = HEREDOC;
	(*cur) = (*cur)->next->next;
}

void	inside_if(t_cmd **cmd, int *i, int *j)
{
	(*cmd)->cmd = malloc(sizeof(char *) * (*j + 1));
	(*cmd)->cmd[*j] = NULL;
	(*cmd)->next = malloc(sizeof(t_cmd));
	ft_memset((*cmd)->next, 0, sizeof(t_cmd));
	(*cmd) = (*cmd)->next;
	(*i)++;
	(*cmd)->fd_out = 1;
	*j = 0;
}

void	boucle_norm(t_node **cur, t_cmd **cmd, int *i, int *j)
{
	while (*cur)
	{
		if ((*cur)->type == HERE_DOC)
		{
			here_doc(cur, cmd);
			continue ;
		}
		if ((*cur)->type == REDIR_IN || (*cur)->type == REDIR_OUT
			|| (*cur)->type == D_REDIR_OUT)
		{
			check_next_next(*cur);
			redirect(cur, *cmd);
			continue ;
		}
		if ((*cur)->type == PIPE_LINE)
			inside_if(cmd, i, j);
		else
			(*j)++;
		(*cur) = (*cur)->next;
	}
}
