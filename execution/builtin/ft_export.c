/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:50:34 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/22 16:44:20 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void  add_new_var(t_env **env, char **var)
{
    t_env *head = *env;
    t_env *new_var;
    new_var = (t_env *)malloc(sizeof(t_env));
    new_var->name = ft_strdup(var[0]);
    new_var->value = ft_strdup(var[1]);
    new_var->next = NULL;
    while (head->next)
        head = head->next;
    head->next = new_var;
}
int check_if_exist(t_cmd *cmd, char **var)
{
    t_env *env = cmd->env;
    while(env)
    {
        if (ft_strcmp(env->name, var[0]) == 0)
        {
            free(env->value);
            env->value = ft_strdup(var[1]);
            return (1);
        }
        env = env->next;
    }
    return (0);
}
char **check_invalid_var(char *str)
{
    if (str[0] && !ft_isalpha(str[0]) && str[0] != '_')
    {
        printf("bash: export: `%s': not a valid identifier\n", str);
        return (NULL);
    }
    int i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (str[i - 1] == ' ')
    {
        printf("bash: export: `%s': not a valid identifier\n", str);
        return (NULL);
    }
    return (ft_split(str, '='));
}
char update_env(t_env *env, char *str)
{
    while (env)
    {
        if (ft_strcmp(env->name, str) == 0)
        {
            free(env->value);
            env->value = ft_strdup(str);
            return (1);
        }
        env = env->next;
    }
    return (0);
}
int ft_export(t_cmd *cmd)
{
        int i = 1;
        char **var;

        var = NULL;
        while (cmd->cmd[i])
        {
            var = check_invalid_var(cmd->cmd[i]);
            if (var)
            {
                if (!check_if_exist(cmd, var))
                    add_new_var(&cmd->env, var);
            }
            i++;
        }
        return (0);
}

