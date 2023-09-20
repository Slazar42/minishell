/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:40:58 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/20 21:50:22 by yberrim          ###   ########.fr       */
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

