/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 02:05:47 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 02:40:37 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmd(t_lexer *lx, t_cmd *cmd)
{
	t_node	*cur;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cur = lx->head;
	cmd->fd_out = 1;
	boucle_norm(&cur, &cmd, &i, &j);
	cmd->cmd = malloc(sizeof(char *) * (j + 1));
	cmd->cmd[j] = NULL;
	cmd->next = NULL;
}

void	inside_while(t_node **cur, t_cmd **cmd, int *i, int *j)
{
	if ((*cur)->type == PIPE_LINE)
	{
		(*cmd)->cmd[*j] = NULL;
		(*i)++;
		*j = 0;
		(*cmd) = (*cmd)->next;
	}
	else if ((*cur)->type == REDIR_IN || (*cur)->type == REDIR_OUT
		|| (*cur)->type == D_REDIR_OUT || (*cur)->type == HERE_DOC
		|| ((*cur)->type == WORD && (*cur)->prev
			&& ((*cur)->prev->type == REDIR_IN
				|| (*cur)->prev->type == REDIR_OUT
				|| (*cur)->prev->type == D_REDIR_OUT
				|| (*cur)->prev->type == HERE_DOC)))
	{
		(*cur) = (*cur)->next->next;
		return ;
	}
	else
	{
		(*cmd)->cmd[*j] = ft_strdup((*cur)->content);
		(*j)++;
	}
	(*cur) = (*cur)->next;
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
		inside_while(&cur, &cmd, &i, &j);
	cmd->cmd[j] = NULL;
	return (head);
}

void	sig_handler(int i)
{
	if (i == SIGINT)
	{
		printf("\n");
		rl_initialize();
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	signal(SIGINT, sig_handler);
	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
