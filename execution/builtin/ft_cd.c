/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:40:58 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/18 18:01:37 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// void change_dir()
// {
//     char *pwd;
//     char *oldpwd;
//     char *home;
//     char *tmp;

//     pwd = getcwd(NULL, 0);
//     oldpwd = ft_strdup(getenv("OLDPWD"));
//     home = ft_strdup(getenv("HOME"));

//     if (ft_strcmp(av, "-") == 0) {
//         av = oldpwd;
//     } else if (ft_strcmp(av, "~") == 0) {
//         av = home;
//     }

//     if (chdir(av) == -1) {
//         printf("minishell: cd: %s: No such file or directory\n", av);
//         free(pwd);
//         free(oldpwd);
//         free(home);
//         return 1;
//     }

//     tmp = ft_strjoin("OLDPWD=", pwd);
//     environment->value = ft_strdup(tmp);
//     free(tmp);
    
//     tmp = ft_strjoin("PWD=", av);
//     environment->next->value = ft_strdup(tmp);
//     free(tmp);

//     free(pwd);
//     free(oldpwd);
//     free(home);
// }
