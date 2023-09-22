/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:09:26 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/22 17:53:39 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void ft_clear_env(t_env **env)
{
    t_env *tmp;
    tmp = *env;
    *env = (*env)->next;
    free(tmp->name);
    free(tmp->value);
    free(tmp);
}
int ft_unset(t_cmd *cmd)
{
    char **var = cmd->cmd;
    t_env *env = cmd->env;
    while(env)
    {
        if (ft_strcmp(env->name, var[0]) == 0)
        {
            free(env->value);
            ft_clear_env(&env);
            return (1);
        }
        env = env->next;
    }
    return (0);
}
