/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:11:51 by slazar            #+#    #+#             */
/*   Updated: 2023/08/27 14:19:40 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *get_var_name(char *env)
{
    int i;
    char *name;

    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    name = malloc(sizeof(char)*i + 1);
    i = 0;
    while (env[i] && env[i] != '=')
    {
        name[i] = env[i];
        i++;
    }
    name[i]=0;
    return(name);
}
char *get_var_value(char *env)
{
    int i;
    int j = 0;
    char *value;
    
    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    value = malloc(ft_strlen(env + i));
    i++;
    while (env[i])
    {
        value[j] = env[i];
        j++;
        i++;
    }
    value[j]=0;
    return(value);
}
void ft_variables(t_env **env,char **envirement)
{
    int i;
    t_env *node;
    t_env *ptr;
    i = 0;
    
    while (envirement[i])
    {
        node = malloc(sizeof(t_env));
        node->value = get_var_value(envirement[i]);
        node->name = get_var_name(envirement[i]);
        if(!*env)
        {
            *env = node;
            ptr = node;
        }
        else
        {
            (*env)->next = node;
            *env = (*env)->next;
        }
        i++;
    }
    *env = ptr;
}
void print_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n",env->name,env->value);
        env = env->next;
    }
    
}



