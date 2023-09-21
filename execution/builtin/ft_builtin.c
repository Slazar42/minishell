/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:51:52 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 16:36:08 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"


// int builtin(char **av, t_env **env)
// {
//     if (ft_strcmp(av[0], "cd") == 0)
//     {
//         ft_cd(av, env);
//         return (1);
//     }
//     else if (ft_strcmp(av[0], "unset") == 0)
//     {
//         ft_unset(av, env);
//         return (1);
//     }
//     else if (ft_strcmp(av[0], "pwd") == 0)
//     {
//         ft_pwd();
//         return (1);
//     }
//     else if (ft_strcmp(av[0], "echo") == 0)
//     {
//         ft_echo(av);
//         return (1);
//     }
//     else if (ft_strcmp(av[0], "env") == 0)
//     {
//         ft_env(*env);
//         return (1);
//     }
//     return (0);
// }