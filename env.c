/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:11:51 by slazar            #+#    #+#             */
/*   Updated: 2023/09/18 13:23:02 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *get_var_name(char *env)
{
    int i;
    char *name;

    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    name = malloc(sizeof(char)*i + 1);
    i = 0;
    while (env[i] && env[i] != '=')
    {
        name[i] = env[i];
        i++;
    }
    name[i]=0;
    return(name);
}
char *get_var_value(char *env)
{
    int i;
    int j = 0;
    char *value;
    
    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    value = malloc(ft_strlen(env) - i + 1);
    i++;
    while (env[i])
    {
        value[j] = env[i];
        j++;
        i++;
    }
    value[j]=0;
    return(value);
}
void ft_variables(t_env **env,char **envirement)
{
    int i;
    t_env *new;
    t_env *head;
    i = 0;
    
    while (envirement[i])
    {
        new = malloc(sizeof(t_env));
        new->value = get_var_value(envirement[i]);
        new->name = get_var_name(envirement[i]);
        new->next = NULL;
        if(!*env)
        {
            *env = new;
            head = new;
        }
        else
        {
            (*env)->next = new;
            *env = (*env)->next;
        }
        i++;
    }
    *env = head;
}
void print_env(t_env *env)
{
    while (env)
    {   
        printf("%s=%s\n",env->name,env->value);
        env = env->next;
    }
}

void take_env(char *str,int *i,t_lexer *lx)
{
	int start;
	char *var;
	start = *i;
	(*i)++;
	while(!is_digits(str[*i]) || !is_alphabet(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_strdup_2(str,start,(*i)-1);
	add_node_to_lexer(lx,var,ENV,GENERAL);
}