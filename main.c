/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:24:41 by slazar            #+#    #+#             */
/*   Updated: 2023/10/02 00:43:44 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_redir_token(out_redirs out, in_redirs in)
{
	if (out == WRITEOUT)
		return (">");
	if (out == APPENDOUT)
		return (">>");
	if (in == READIN)
		return ("<");
	if (in == HEREDOC)
		return ("<<");
	return (NULL);
}

void	print_list(t_cmd *cmd)
{
	while (cmd)
	{
		printf("argv: ");
		print_argv(cmd->cmd);
		printf("fd_in: %i\n", cmd->fd_in);
		printf("fd_out: %i\n", cmd->fd_out);
		printf("input redirections: %s\n", print_redir_token(0,
					cmd->in_redir_type));
		printf("output redirections: %s\n",
				print_redir_token(cmd->out_redir_type, 0));
		// if (cmd->in_file)
		printf("input file: %s\n", cmd->in_file);
		// if (cmd->out_file)
		printf("output file: %s\n", cmd->out_file);
		if (cmd->next)
			printf("=======================\n");
		cmd = cmd->next;
	}
}

void	sig_handler(int i)
{
	if (i == SIGINT)
	{
		printf("\n");
		rl_initialize();
		rl_on_new_line();
		// rl_replace_line("", 0);
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
				cmd->env = env;
				//print_list(cmd);
				execution_proto(cmd, envirement);
			}
		}
	}
	if (line)
		free(line);
}
