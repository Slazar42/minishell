/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:33:51 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 13:24:07 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int ft_pwd(int fd_out)
{
    char *current_dir;
    
    current_dir = getcwd(NULL, 0);
    if(!current_dir){
        ft_putstr_fd(2,"Current directory error\n");
        return 1;
    }
    ft_putstr_fd(current_dir, fd_out);
    write(fd_out, "\n", 1);
    return 0;
}
