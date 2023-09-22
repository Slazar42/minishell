/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:09:50 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/22 17:50:57 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int is_buildin(t_cmd *cmd)
{
    if(ft_strcmp(cmd->cmd[0], "echo") || ft_strcmp(cmd->cmd[0], "pwd") || ft_strcmp(cmd->cmd[0], "cd") \
    || ft_strcmp(cmd->cmd[0], "export") || ft_strcmp(cmd->cmd[0], "unset")\
     || ft_strcmp(cmd->cmd[0], "env") || ft_strcmp(cmd->cmd[0], "exit"))
        return (1);
    return (0);
}
int execution_builtin(t_cmd *cmd, int i)
{
    int check = 0;
    
    if(!ft_strcmp(cmd[i].cmd[0], "echo"))
        check = ft_echo(cmd, cmd[i].fd_out);
    else if(!ft_strcmp(cmd[i].cmd[0], "pwd"))
        check = ft_pwd(cmd[i].fd_out);
    else if(!ft_strcmp(cmd[i].cmd[0], "cd"))
        check = ft_cd(cmd, cmd[i].fd_out);
    else if(!ft_strcmp(cmd[i].cmd[0], "export"))
        check = ft_export(cmd);
    else if (!ft_strcmp(cmd[i].cmd[0], "unset"))
        check = ft_unset(cmd);
    return (check);
}
