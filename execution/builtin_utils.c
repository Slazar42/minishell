/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:09:50 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 13:31:59 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int is_buildin(char *cmd)
{
    if(ft_strcmp(cmd, "echo") || ft_strcmp(cmd, "pwd") || ft_strcmp(cmd, "cd") \
    || ft_strcmp(cmd, "export") || ft_strcmp(cmd, "unset")\
     || ft_strcmp(cmd, "env") || ft_strcmp(cmd, "exit"))
        return (1);
    return (0);
}
typedef struct s_command
{
    char **cmd;
    char **arg;
    int fd_in;
    int fd_out ;
}t_command;

int execution_builtin(t_command **cmd, int i)
{
    int check = 0;
    if(ft_strcmp(cmd[i]->arg, "echo"))
        check = ft_echo(cmd[i]->arg, cmd[i]->fd_out);
    else if(ft_strcmp(cmd[i]->arg, "pwd"))
        check = ft_pwd(cmd[i]->fd_out);
    else if(ft_strcmp(cmd[i]->arg, "cd"))
        check = ft_cd(cmd[i]->arg, cmd[i]->fd_out);
    else if(ft_strcmp(cmd[i]->arg, "export"));
        check = ft_export(cmd[i]->arg, cmd[i]->fd_out);
    else if(ft_strcmp(cmd[i]->arg, "unset"))
        check = ft_unset(cmd[i]->arg, cmd[i]->fd_out);
    else if(ft_strcmp(cmd[i]->arg, "env"))
        check = ft_env(cmd[i]->arg, cmd[i]->fd_out);
    else if(ft_strcmp(cmd[i]->arg, "exit"))
        check = ft_exit(cmd[i]->arg, cmd[i]->fd_out);
}
