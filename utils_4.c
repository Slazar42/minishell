/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:58:58 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 23:15:56 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	treat_commands(t_node *cur, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cur)
	{
		if (cur->type == PIPE_LINE && ++i)
		{
			cmd->cmd[j] = NULL;
			j = 0;
			cmd = cmd->next;
		}
		else if (cur->type == REDIR_IN || cur->type == REDIR_OUT
			|| cur->type == D_REDIR_OUT || cur->type == HERE_DOC
			|| (cur->type == WORD && cur->prev
				&& (cur->prev->type == REDIR_IN || cur->prev->type == REDIR_OUT
					|| cur->prev->type == D_REDIR_OUT
					|| cur->prev->type == HERE_DOC)))
			cur = cur->next;
		else
			cmd->cmd[j++] = ft_strdup(cur->content);
		cur = cur->next;
	}
}

t_cmd	*commands(t_lexer *lx)
{
	t_node	*cur;
	t_cmd	*cmd;
	t_cmd	*head;

	cmd = ft_calloc(sizeof(t_cmd), (ft_count_cmd(lx) + 1));
	head = cmd;
	cur = create_cmd(lx, cmd);
	treat_commands(cur, cmd);
	return (head);
}

// void	print_argv(char **argv)
// {
// 	int	i;

// 	i = 0;
// 	while (argv[i])
// 	{
// 		printf("%s", argv[i]);
// 		if (argv[i + 1])
// 			printf(", ");
// 		i++;
// 	}
// 	printf("\n");
// }

// char	*print_redir_token(out_redirs out, in_redirs in)
// {
// 	if (out == WRITEOUT)
// 		return (">");
// 	if (out == APPENDOUT)
// 		return (">>");
// 	if (in == READIN)
// 		return ("<");
// 	if (in == HEREDOC)
// 		return ("<<");
// 	return (NULL);
// }

// void	print_list(t_cmd *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("argv: ");
// 		print_argv(cmd->cmd);
// 		printf("fd_in: %i\n", cmd->fd_in);
// 		printf("fd_out: %i\n", cmd->fd_out);
// 		printf("input redirections: %s\n", print_redir_token(0,
// 				cmd->in_redir_type));
// 		printf("output redirections: %s\n",
// 			print_redir_token(cmd->out_redir_type, 0));
// 		// if (cmd->in_file)
// 		printf("input file: %s\n", cmd->in_file);
// 		// if (cmd->out_file)
// 		printf("output file: %s\n", cmd->out_file);
// 		if (cmd->next)
// 			printf("=======================\n");
// 		cmd = cmd->next;
// 	}
// }

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

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
}
