/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:15:30 by slazar            #+#    #+#             */
/*   Updated: 2023/08/23 20:32:57 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>


typedef struct envirement
{
    char *name;
    char *value;
    struct envirement *next ;
}t_env;

// typedef struct pars
// {
//     int fd_input; //fd diel input for each cmmd
//     int fd_output; //fd diel aoutput for each cmmd
//     t_env envirement; // struct dial l envierement
//     char **cmmd; //cmmd bles arguments dialha
    
// }
// builtins
// expansion;
// signals
// ecxeve bles ereures dialha