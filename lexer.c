/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:09:30 by slazar            #+#    #+#             */
/*   Updated: 2023/08/27 18:33:45 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *ft_strdup(char *str,int start,int finish)
{
	int i;
	char *dup;
	i = 0;
	while (str && str[start + i] && (start +i)<= finish)
		i++;
	// printf("ww %s\n",)
	dup = malloc(sizeof(char)*(i + 1));
	dup[i] = '\0';
	i = 0;
	while (str && str[start +i] && start +i <= finish)
	{
		dup[i] = str[start+i];
		i++;
	}
	return(dup);
}

int ft_strcmp(int *s1,int *s2)
{
	while (s1 && s2 && *s1 && *s2)
	{
		if(*s1 - *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
int if_token(char c)
{
	if (( c == '\'' || c == '\"' || c == '\\' 
	|| c == '$' || c == '|' || c == '>' || c == '<' || c == ' '))
		return (0);
	return 1;
}
int is_digits(char c)
{
	if (c >= '0' && c <= '9')
		return 0;
	return(1);
}

int ft_strlen(char *str)
{
    int i;
    i=-1;
    while(str && str[++i]);
    return(i);
}
void add_node_to_lexer(t_list *lx,char *word,enum e_token token)
{
	t_elem *new;
	new = malloc(sizeof(t_elem));
	if (!new)
		return;
	new->content = word;
	new->type = token ;
	new->len = ft_strlen(word);
	new->next = NULL;
	new->prev = lx->tail;
	if(!lx->head)
		lx->head = new;
	if(lx->tail)
		lx->tail->next = new;
	lx->tail = new;
	lx->size += 1;
}
void take_env(char *str,int *i,t_list *lx)
{
	int start;
	char *var;
	start = *i;
	(*i)++;
	while(!is_digits(str[*i]) || !is_alphabet(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_strdup(str,start,(*i)-1);
	add_node_to_lexer(lx,var,ENV);
}
void take_token(char *str,int *i,t_list *lx)
{
	char *token;
	if(str[*i] == ENV)
	{
		take_env(str,i,lx);
		return;
	}
	token = ft_strdup(str,*i,*i);
	if (str[*i] == WHITE_SPACE)
		add_node_to_lexer(lx,token,WHITE_SPACE);
	else if (str[*i] == NEW_LINE)
		add_node_to_lexer(lx,token,NEW_LINE);
	else if (str[*i] == QOUTE)
		add_node_to_lexer(lx,token,QOUTE);
	else if (str[*i] == DOUBLE_QUOTE)
		add_node_to_lexer(lx,token,DOUBLE_QUOTE);
	else if (str[*i] == ESCAPE)
		add_node_to_lexer(lx,token,ESCAPE);
	else if (str[*i] == PIPE_LINE)
		add_node_to_lexer(lx,token,PIPE_LINE);
	else if (str[*i] == REDIR_IN && str[(*i) + 1] != REDIR_IN && str[(*i) - 1] != REDIR_IN)
		add_node_to_lexer(lx,token,REDIR_IN);
	else if (str[*i] == REDIR_OUT && str[(*i) + 1] != REDIR_OUT && str[(*i) - 1] != REDIR_OUT)
		add_node_to_lexer(lx,token,REDIR_OUT);
	else if (str[*i] == REDIR_OUT && str[(*i) + 1] == REDIR_OUT)
	{
		add_node_to_lexer(lx,">>",D_REDIR_OUT);
		(*i)++;
	}
	else if (str[*i] == REDIR_IN && str[(*i) + 1] == REDIR_IN)
	{
		add_node_to_lexer(lx,"<<",HERE_DOC);
		(*i)++;
	}
	(*i)++;
}

int is_alphabet(char c)
{
	if ((c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'z'))
		return 0;
	return(1);
}
void take_word(char *str, int *i, t_list *lx)
{
	int start;
	char *word;
	start = *i;
	while ((str[*i] >= 'a' && str[*i] <= 'z' ) || ( str[*i] >= 'A' && str[*i] <= 'Z'))
		(*i)++;
	word = ft_strdup(str,start,*i-1);
	add_node_to_lexer(lx,word,WORD);
}
void lexer(char *str, t_list *lx)
{
	int i = 0;

	while (str && str[i])
	{
		if(is_alphabet(str[i]) == 0)
			take_word(str,&i,lx);
		else if(if_token(str[i]) == 0)
			take_token(str,&i,lx);
		else
			i++;
	}
}
void ft_initialisation(t_list *lx)
{
	lx->head =NULL;
	lx->tail=NULL;
	lx->size = 0;
	// line = NULL;
}
void ft_print_lexer(t_elem **head)
{
    t_elem *cur = *head;
    char general[] = "GENERAL";
    // char in_s_quote[] = "IN_S_QUOTE";
    // char in_d_quote[] = "IN_D_QUOTE";
    char *state;
    
    printf("-----------------------------------------------------------\n");
    printf("|%-17s|%3s|%15s|      token    |\n", "content", "len", "state");
    printf("-----------------------------------------------------------\n");

    while (cur)
    {
        // if (cur->state == IN_DQUOTE)
        //     state = in_d_quote;
        // else if (cur->state == IN_SQUOTE)
        //     state = in_s_quote;
        // else if (cur->state == GENERAL)
            state = general;
        
        printf("|%-17s|%3d|%-15s|", cur->content, cur->len, state);

        if (cur->type == WORD)
            printf("      WORD    |\n");
        else if (cur->type == WHITE_SPACE)
            printf("      WHITE_SPACE    |\n");
        else if (cur->type == NEW_LINE)
            printf("       NEW_LINE     |\n");
        else if (cur->type == QOUTE)
            printf("      QOUTE    |\n");
        else if (cur->type == DOUBLE_QUOTE)
            printf("     DOUBLE_QUOTE     |\n");
        else if (cur->type == ESCAPE)
            printf("      ESCAPE     |\n");
        else if (cur->type == ENV)
            printf("     ENV    |\n");
        else if (cur->type == PIPE_LINE)
            printf("     PIPE_LINE     |\n");
        else if (cur->type == REDIR_IN)
            printf("    REDIR_IN     |\n");
        else if (cur->type == REDIR_OUT)
            printf("     REDIR_OUT    |\n");
        else if (cur->type == D_REDIR_OUT)
            printf("     DREDIR_OUT     |\n");
        else if (cur->type == HERE_DOC)
            printf("    HERE_DOC    |\n");
        
        printf("-----------------------------------------------------------\n");
        cur = cur->next;
    }
}


int main(int ac,char **av,char **envirement)
{
    (void) ac;
    (void) av;
    t_env *env;
    ft_variables(&env,envirement);
	t_list lx;
	char *line;
	while (1)
	{
		ft_initialisation(&lx);
		line = readline("minishell ");
		if (!line)
			printf("Error\n");
		else if (*line == '\0')
			continue;
		else if(!strcmp(line,"env"))
            print_env(env);
		else
		{
			add_history(line);
			lexer(line, &lx);
			ft_print_lexer(&lx.head);
		}
		if(line)
			free(line);
	}
	
}