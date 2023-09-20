/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:50:34 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/20 23:00:51 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void ft_export(char* val, t_env* env) 
{
    char* env_spl = ft_split(val, "=");
    char* key = env_spl[0];
    char* val = env_spl[1];

    if(env == NULL)
    {
        env = malloc(sizeof(t_env));
        env->name = key;
        env->value = val;
        env->next = NULL;
        return;
    }
    while (env) 
    {
        if (env->next == NULL)
            break;
        env = env->next;
    }
    t_env* new_env = malloc(sizeof(t_env));
    new_env->name = key;
    new_env->value = val;
    new_env->next = NULL;
    env->next = new_env;
}
