/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:50:34 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 14:40:40 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int print_expot_lis(char **env, int fd)
{
    int i;
    
    i = 0;
    while (env[i])
    {
        if(ft_strcmp(ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]), "_"))
        {
            i++;
            continue;
        }
        ft_putstr_fd("declare -x ", fd);
        if(ft_strchr(env[i], '='))
        {
            ft_putstr_fd(ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]), fd);
            write(fd, "\"", 2);
            ft_putstr_fd(ft_strchr(env[i], '=') + 1, fd);
            write(fd, "\"\n", 2);
        }
        else
        {
            ft_putstr_fd(env[i], fd);
            write(fd, "\n", 1);
        }
        i++;
    }
    return 0;
}

char *ft_copy(char *s1)
{
    char *s2;
    size_t i;

    i = ft_strlen((char *)s1);
    s2 = malloc(sizeof(char) * (i + 1));
    if (!s2)
        return (0);
    ft_strlcpy(s2, s1, i + 1);
    return (s2);
}

int **ft_env_enw(char **env, char **av)
{
    char **tmp;
    
    int i = 0;
    tmp = malloc(sizeof(char *) * (ft_strstrlen(env) + 2));
    while (env[i])
    {
        tmp[i] = ft_copy(env[i]);
        i++;
    }
    tmp[i] = ft_copy(av[1]);
    tmp[i + 1] = NULL;
    free(env);
    return (tmp);
}
char **exporting_arg(char **env, char *arg)
{
    int i ;
    
    i = 0;
    while (env[i])
    {
        if(ft_strcmp(ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]), arg) == 0)
        {
            if(ft_strchr(env[i], '='))
            {
                free(env[i]);
                env[i] = ft_copy(arg);
            }
        
        }    return (env);
        i++;
    }
    return ft_env_enw(env, &arg);
}

int ft_export(char **av,int fd)
{
    char **env;
    int i = 0;

    env = ft_env(NULL);
    if(!av[1])
        return print_expot_lis(env, fd);
    while (av[i])
    {
        if(ft_strchr(av[i], '='))
            env = exporting_arg(env, av[i]);
        else
        {
            ft_putstr_fd(av[i], 2);
            ft_putstr_fd("export: not valid in this context: ", 2);
        }
        i++;
    }
    ft_env(env);
    return 0;
}

