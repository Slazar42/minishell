/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:09:26 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/20 21:49:48 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void ft_unset(char **av, t_env **env)
{
    int i;
    t_env *tmp;
    t_env *tmp2;

    i = 1;
    while (av[i])
    {
        tmp = *env;
        if (ft_strcmp(tmp->name, av[i]) == 0)
        {
            *env = tmp->next;
            free(tmp->name);
            free(tmp->value);
            free(tmp);
        }
        else
        {
            while (tmp->next)
            {
                if (ft_strcmp(tmp->next->name, av[i]) == 0)
                {
                    tmp2 = tmp->next;
                    tmp->next = tmp->next->next;
                    free(tmp2->name);
                    free(tmp2->value);
                    free(tmp2);
                }
                tmp = tmp->next;
            }
        }
        i++;
    }
}
