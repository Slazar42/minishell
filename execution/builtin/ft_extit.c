/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:00:58 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/20 21:43:55 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

//◦ exit with no options

void ft_exit(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
        i++;
    if (i == 1)
        exit(0);
    else if (i == 2)
    {
        if (ft_isdigit(argv[1][0]))
            exit(ft_atoi(argv[1]));
        else
        {
            printf("minishell: exit: %s: numeric argument required\n", argv[1]);
            exit(255);
        }
    }
    else
    {
        printf("minishell: exit: too many arguments\n");
        return (1);
    }
    return (0);
}