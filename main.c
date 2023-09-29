/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:24:41 by slazar            #+#    #+#             */
/*   Updated: 2023/09/29 05:52:26 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int only_sp_tab(char *line)
{
	while (*line && ( *line == ' ' || *line == '\t'))
		line++;
	return(*line ? 1 : 0);
}
int check_space(char *line)
{
	if(*line == '\0' || only_sp_tab(line) == 0)
		return(0);
	return(1);
}
void join_in_quote_and_word(t_lexer *lx)
{
	t_node *tmp;
	t_node *cur;
	
	cur = lx->head;
	while(cur)
	{
		if(cur->next && ((cur->type == QOUTE || cur->type == DOUBLE_QUOTE || cur->type == WORD ) && \
			(cur->next->type == QOUTE || cur->next->type == DOUBLE_QUOTE || cur->next->type == WORD)))
		{
			tmp = cur->next;
			cur->content = ft_strjoin(cur->content,tmp->content);
			cur->len = ft_strlen(cur->content);
			cur->next = tmp->next;
			if(tmp->next)
				tmp->next->prev = cur;
			free(tmp->content);
			free(tmp);
			lx->size -= 1;
			cur = lx->head;
		}
		cur = cur->next;
	}
}
int ft_count_cmd(t_lexer *lx)
{
	t_node *tmp;
	int count;
	
	count = 0;
	tmp = lx->head;
	while(tmp)
	{
		if(tmp->type == PIPE_LINE)
			count++;
		tmp = tmp->next;
	}
	return(count);
}
void init_cmd_struct(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->fd_in = 0;
	(*cmd)->fd_out = 1;
	// (*cmd)->redir.in_file = NULL;
	// (*cmd)->redir.out_file = NULL;
}
void redirect(t_node **cur, t_cmd *cmd)
{
	if((*cur)->type == REDIR_IN)
	{
		if (!cmd->in_file)
			free(cmd->in_file);
		cmd->in_file = ft_strdup((*cur)->next->content);
		cmd->in_redir_type = READIN;
	}
	else if((*cur)->type == REDIR_OUT)
	{
		if (!cmd->out_file)
			free(cmd->out_file);
		cmd->out_file = ft_strdup((*cur)->next->content);
		cmd->out_redir_type = WRITEOUT;
	}
	else if((*cur)->type == D_REDIR_OUT)
	{		
		if (!cmd->out_file)
			free(cmd->out_file);
		cmd->out_file = ft_strdup((*cur)->next->content);
		cmd->out_redir_type = APPENDOUT;
	}
	else if((*cur)->type == HERE_DOC)
	{
		if (!cmd->in_file)
			free(cmd->in_file);
		cmd->in_file = ft_strdup((*cur)->next->content);
		cmd->in_redir_type = HEREDOC;
	}
	(*cur) = (*cur)->next->next;
}

void check_next_next(t_node *cur)
{
	int tmp_fd;
	if (cur->next->next && (cur->next->next->type == REDIR_IN || 
		cur->next->next->type == REDIR_OUT || cur->next->next->type == D_REDIR_OUT))
	{
		tmp_fd = open(cur->next->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(tmp_fd);
	}
}
void	create_cmd(t_lexer *lx, t_cmd *cmd)
{
	t_node *cur;
	int i;
	int j;
	
	i = 0;
	j = 0;
	cur = lx->head;
	cmd->fd_out = 1;
	while(cur)
	{
		if (cur->type == REDIR_IN || cur->type == REDIR_OUT || cur->type == D_REDIR_OUT || cur->type == HERE_DOC)
		{
			check_next_next(cur);
			redirect(&cur, cmd);
			continue;
		}
		if(cur->type == PIPE_LINE)
		{
			cmd->cmd = malloc(sizeof(char *) * (j + 1));
			cmd->cmd[j] = NULL;
			cmd->next = malloc(sizeof(t_cmd));
			ft_memset(cmd->next, 0, sizeof(t_cmd));
			cmd = cmd->next;
			i++;
			cmd->fd_out = 1;
			j = 0;
		}
		else
			j++;
		cur = cur->next;
	}
	cmd->cmd = malloc(sizeof(char *) * (j + 1));
	cmd->cmd[j] = NULL;
	cmd->next = NULL;
}

t_cmd *commands(t_lexer *lx)
{
	t_node *cur;
	t_cmd* cmd;
	t_cmd* head;
	int i;
	int j;

	i = 0;
	j = 0;
	cmd = malloc(sizeof(t_cmd) * (ft_count_cmd(lx) + 1));
	ft_memset(cmd, 0, sizeof(t_cmd));
	head = cmd;
	create_cmd(lx,cmd);
	cur = lx->head;
	while(cur)
	{
		if(cur->type == PIPE_LINE)
		{
			cmd->cmd[j] = NULL;
			i++;
			j = 0;
			cmd = cmd->next;
		}
		else if (cur->type == REDIR_IN || cur->type == REDIR_OUT || cur->type == D_REDIR_OUT || cur->type == HERE_DOC || (cur->type == WORD && cur->prev && (cur->prev->type == REDIR_IN || cur->prev->type == REDIR_OUT || cur->prev->type == D_REDIR_OUT || cur->prev->type == HERE_DOC)))
		{
			cur = cur->next->next;
			continue;
		}
		else
		{
			cmd->cmd[j] = ft_strdup(cur->content);
			j++;
		}
		cur = cur->next;
	}
	cmd->cmd[j] = NULL;
	// max_i = i;
	
	// i = 0;
	// while (i < max_i)
	// {
	// 	cmd[i].next = &cmd[i + 1];
	// 	i++;
	// }
	// cmd[i].next = NULL;
	return(head);
}

void print_argv(char** argv) {
	int i = 0;
	while (argv[i]) {
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(", ");
		i++;
	}
	printf("\n");
}

char* print_redir_token(out_redirs out, in_redirs in) {
	if (out == WRITEOUT)
		return (">");
	if (out == APPENDOUT)
		return (">>");
	if (in == READIN)
		return ("<");
	if (in == HEREDOC)
		return ("<<");
	return NULL;
}

void print_list(t_cmd* cmd) {
	while (cmd) {
		printf("argv: ");
		print_argv(cmd->cmd);
		printf("fd_in: %i\n", cmd->fd_in);
		printf("fd_out: %i\n", cmd->fd_out);
		printf("input redirections: %s\n", print_redir_token(0, cmd->in_redir_type));
		printf("output redirections: %s\n", print_redir_token(cmd->out_redir_type, 0));
		// if (cmd->in_file)
		printf("input file: %s\n", cmd->in_file);
		// if (cmd->out_file)
		printf("output file: %s\n", cmd->out_file);
		if (cmd->next)
			printf("=======================\n");
		cmd = cmd->next;
	}
}

int main(int __unused ac,char __unused **av,char **envirement)
{
	char *line;
    t_env *env;
	t_lexer lx;
	t_cmd *cmd;

	cmd = NULL;
    ft_variables(&env,envirement);

	while (1)
	{
		ft_initialisation(&lx);
		line = readline("\x1B[34mminishell \x1B[35m$->\x1b[0m");
		if (!line)
			return (1);
		else if (check_space(line) == 0)
			continue;
		else
		{
			add_history(line);
			if(lexer(line, &lx, env))
				continue;
			else
			{
				// ft_print_lexer(&lx.head);
				join_quotes(&lx);
				join_in_quote_and_word(&lx);
				delete_white_space(&lx);
				cmd = commands(&lx);
				cmd->env = env;
				if(is_buildin(cmd))
				{
					execution_builtin(cmd,0);
				}
				else
					execution_proto(cmd, envirement);
				// print_list(cmd);
			}
		}
	}
	if(line)
		free(line);
}
