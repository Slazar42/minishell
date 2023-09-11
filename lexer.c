/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:09:30 by slazar            #+#    #+#             */
/*   Updated: 2023/09/09 13:49:52 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void add_node_to_lexer(t_nodes *lx,char *word,enum e_token token,enum e_state state)
{
	t_elem *new;
	new = malloc(sizeof(t_elem));
	if (!new)
		return;
	new->content = word;
	new->type = token ;
	new->len = ft_strlen(word);
	new->next = NULL;
	new->state = state;
	new->prev = lx->tail;
	if(!lx->head)
		lx->head = new;
	if(lx->tail)
		lx->tail->next = new;
	lx->tail = new;
	lx->size += 1;
}

void take_token(char *str,int *i,t_nodes *lx)
{
	char *token;
	if(str[*i] == ENV)
	{
		take_env(str,i,lx);
		return;
	}
	token = ft_strdup_2(str,*i,*i);
	if (str[*i] == WHITE_SPACE)
		add_node_to_lexer(lx,token,WHITE_SPACE, GENERAL);
	else if (str[*i] == NEW_LINE)
		add_node_to_lexer(lx,token,NEW_LINE, GENERAL);
	else if (str[*i] == QOUTE)
		add_node_to_lexer(lx,token,QOUTE, GENERAL);
	else if (str[*i] == DOUBLE_QUOTE)
		add_node_to_lexer(lx,token,DOUBLE_QUOTE, GENERAL);
	else if (str[*i] == ESCAPE)
		add_node_to_lexer(lx,token,ESCAPE, GENERAL);
	else if (str[*i] == PIPE_LINE)
		add_node_to_lexer(lx,token,PIPE_LINE, GENERAL);
	else if (str[*i] == TAB)
		add_node_to_lexer(lx,token,TAB, GENERAL);
	else if (str[*i] == REDIR_IN && str[(*i) + 1] != REDIR_IN && str[(*i) - 1] != REDIR_IN)
		add_node_to_lexer(lx,token,REDIR_IN, GENERAL);
	else if (str[*i] == REDIR_OUT && str[(*i) + 1] != REDIR_OUT && str[(*i) - 1] != REDIR_OUT)
		add_node_to_lexer(lx,token,REDIR_OUT, GENERAL);
	else if (str[*i] == REDIR_OUT && str[(*i) + 1] == REDIR_OUT)
	{
		add_node_to_lexer(lx,">>",D_REDIR_OUT,GENERAL);
		(*i)++;
	}
	else if (str[*i] == REDIR_IN && str[(*i) + 1] == REDIR_IN)
	{
		add_node_to_lexer(lx,"<<",HERE_DOC,GENERAL);
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
void take_word(char *str, int *i, t_nodes *lx)
{
	int start;
	char *word;
	start = *i;
	while ((str[*i] >= 'a' && str[*i] <= 'z' ) || ( str[*i] >= 'A' && str[*i] <= 'Z'))
		(*i)++;
	word = ft_strdup_2(str,start,*i-1);
	add_node_to_lexer(lx,word,WORD,GENERAL);
}
void	give_state(t_nodes *lx)
{
	t_elem *cur;
	cur = lx->head;
	while (cur)
	{
		if(cur->type == DOUBLE_QUOTE && cur->next)
		{
			cur = cur->next;
			while (cur && cur->type != DOUBLE_QUOTE)
			{
				cur->state = IN_DQUOTE;
				cur = cur->next;
			}
		}
		else if(cur->type == QOUTE && cur->next)
		{
			cur = cur->next;
			while (cur && cur->type != QOUTE)
			{
				cur->state = IN_SQUOTE;
				cur = cur->next;
			}
		}
		cur = cur->next;
	}
}
void	free_list(t_nodes *lst)
{
	t_elem	*tmp;

	tmp = lst->head;
	while (tmp)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
	free(lst);
}
void lexer(char *str, t_nodes *lx)
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
	give_state(lx);
}
void ft_initialisation(t_nodes *lx)
{
	lx->head =NULL;
	lx->tail=NULL;
	lx->size = 0;
}
void ft_print_lexer(t_elem **head)
{
    t_elem *cur = *head;
    char general[] = "GENERAL";
    char in_s_quote[] = "IN_S_QUOTE";
    char in_d_quote[] = "IN_D_QUOTE";
    char *state;

    printf("-----------------------------------------------------------\n");
    printf("|%-17s|%3s|%15s|      token    |\n", "content", "len", "state");
    printf("-----------------------------------------------------------\n");

    while (cur)
    {
        if (cur->state == IN_DQUOTE)
            state = in_d_quote;
        else if (cur->state == IN_SQUOTE)
            state = in_s_quote;
        else if (cur->state == GENERAL)
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
        else if (cur->type == TAB)
            printf("    TAB     |\n");
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
