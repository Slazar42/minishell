/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:41:24 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/18 17:43:12 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"


char **ft_env(t_env *envirement)
{
    char *env = NULL;
    
    while (envirement)
    {
        env = ft_strjoin_free(env, envirement->name);
        env = ft_strjoin_free(env, "=");
        env = ft_strjoin_free(env, envirement->value);
        env = ft_strjoin_free(env, " ");
        envirement = envirement->next;
    }
    return (ft_split(env, ' '));
}



// execve(av[0], av, ft_env(env);