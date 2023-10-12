/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:24:41 by slazar            #+#    #+#             */
/*   Updated: 2023/10/11 23:06:52 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_env(char *str, int *i, t_lexer *lx)
{
	int		start;
	char	*var;

	start = *i;
	(*i)++;
	while (!is_digits(str[*i]) || !is_alphabet(str[*i]) || str[*i] == '_'
		|| str[*i] == '?')
		(*i)++;
	var = ft_strdup_2(str, start, (*i) - 1);
	add_node_to_lexer(lx, var, ENV, GENERAL);
}

char	*get_line(t_lexer *lx)
{
	char	*line;

	ft_initialisation(lx);
	line = readline("minishell $-> ");
	if (!line)
		exit (1);
	add_history(line);
	return (line);
}

int	free_if_line(char *line)
{
	if (line)
		free(line);
	return (1);
}

void	loop(t_lexer *lx, t_env *env)
{
	char	*line;
	char	**str;
	t_cmd	*cmd;

	cmd = NULL;
	str = NULL;
	while (1)
	{
		line = get_line(lx);
		if (check_space(line) == 0 && free_if_line(line))
			continue ;
		if (lexer(line, lx, env) && destroy_t_node(lx) && free_if_line(line))
			continue ;
		cmd = lexer_to_cmd(lx);
		if (access_check(cmd))
		{
			destroy_cmd(cmd);
			continue ;
		}
		executtion(cmd, str, env);
		destroy_t_node(lx);
		if (line)
			free(line);
	}
}

int	main(int __unused ac, char __unused **av, char **envirement)
{
	t_env	*env;
	t_lexer	lx;

	ft_variables(&env, envirement);
	setup_signal_handlers();
	loop(&lx, env);
	return (0);
}
