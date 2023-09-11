/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:24:41 by slazar            #+#    #+#             */
/*   Updated: 2023/09/11 13:36:03 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int only_sp_tab(char *line)
{
	while (*line)
	{
		if(*line != ' ' || *line != '\t')
			return (1);
		line++;
	}
	return(0);
}
int check_space(char *line)
{
	if(*line == '\0' || only_sp_tab(line))
		return(1);
	return(0);
}
// int syntax_error(char *line)
// {
// 	if(!line)
// 		return(1);
// 	else if ()
// }
int main(int __unused ac,char **av,char **envirement)
{
    (void) ac;
    (void) av;
    t_env *env;
    ft_variables(&env,envirement);
	t_nodes lx;
	char *line;

	while (1)
	{
		// if (execve("ls", av, envirement) == -1)
		// 	puts("error");
		ft_initialisation(&lx);
		line = readline("minishell ");
		if (!line)
			printf("Error\n");
		else if (check_space(line))
			continue;
		else if(!strcmp(line,"env"))
            print_env(env);
		else
			add_history(line);
			lexer(line, &lx);
			ft_print_lexer(&lx.head);
		}
	if(line)
		free(line);
}
