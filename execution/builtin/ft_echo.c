/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:52:08 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 13:19:54 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}
int ft_echo(char **av, int fd_out)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (av[1] && ft_strcmp(av[1], "-n") == 0)
    {
        n = 1;
        i++;
    }
    while (av[i])
    {
        ft_putstr_fd(av[i], fd_out);
        if (av[i + 1])
            ft_putstr_fd(" ", fd_out);
        i++;
    }
    if (n == 0)
        ft_putstr_fd("\n", fd_out);
    return (0);
}