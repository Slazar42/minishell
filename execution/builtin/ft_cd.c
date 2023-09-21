/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:40:58 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 13:30:04 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef enum {
    OUT_NONE,
    WRITEOUT,
    APPENDOUT
} out_redirs;

typedef enum {
    IN_NONE,
    READIN,
    HEREDOC
} in_redirs;

typedef struct c {
    char** argv;
    int in;
    int out;
    int has_pipe;
    out_redirs out_redir_type;
    in_redirs in_redir_type;
    char* in_file;
    char* out_file;
    struct c* next;
    // redirections l8r
} cmd;

int ft_cd(char **arg, int fd)
{
    char *path;

    if(!path[0])
        path = ft_getenv("HOME");
    else if (ft_strcmp(arg[0], "~") == 0)
        path = ft_getenv("OLDPWD");
    else if(ft_strcmp(arg[0], "-") == 0)
    {
        path = ft_getenv("OLDPWD");
        if(!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            return 1;
        }
        ft_putstr_fd(path, fd);
        write(fd, "\n", 1);
    }
    else
        path = ft_strdup(arg[0]);
    if(chdir(path) == -1)
    {
        perror("directory error");
        return 1;
    }
    return 0;
}