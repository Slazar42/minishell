/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:43:17 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 12:59:32 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int exit_status(int status) {
    return WEXITSTATUS(status);
}
// ls -> /bin/ls
// afjkadsf -> NULL (command not found)
char* find_abs_path(char* cmd)
{
    // check if cmd starts with ./ (ya3ni lcommand kayna f current directory dial minishell)
    // linked list dial envp, ya3ni converti envp -> linked list
    char* raw_path = getenv("PATH");
    char** path_arr = ft_split(raw_path, ':');
    int i = 0;
    if (cmd[0] == '/' && ft_strlen(cmd) > 1)
    {
        if (access(cmd, F_OK) == 0)
            return cmd;
        return NULL;
    }
    if(cmd[0] == '.' && cmd[1] == '/')
    {
        if (access(cmd, F_OK) == 0)
            return cmd;
        return NULL;
    }
    while (path_arr[i])
    {
        char* fwd_slash = ft_strjoin(path_arr[i], "/");
        char* abs_path = ft_strjoin(fwd_slash, cmd);
        if (access(abs_path, F_OK) == 0) {
            free(fwd_slash);
            free(path_arr);
            printf("found abs path: %s\n", abs_path);
            return abs_path;
        }
        free(fwd_slash);
        free(abs_path);
        i++;
    }
    printf("command not found\n");
    return NULL;
}

void check_redirections(cmd* cmd) {
    int pipefd[2];
    // >
    if (cmd->out_redir_type == WRITEOUT) 
    {
        cmd->out = open(cmd->out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        printf("out redir fd: %i\n", cmd->out);
        if(cmd->out == -1)
            printf("error opening file\n");
    }
    // >>
    if (cmd->out_redir_type == APPENDOUT) {
        cmd->out = open(cmd->out_file, O_WRONLY | O_APPEND, 0644);
        if(cmd->out == -1)
            printf("error opening file\n");
    }
    // <
    if (cmd->in_redir_type == READIN) 
    {
        cmd->in = open(cmd->in_file, O_RDONLY);
        if(cmd->in == -1)
            printf("error opening file\n");
    }
    // <<
    if (cmd->in_redir_type == HEREDOC) 
    {
        pipe(pipefd);
        write(pipefd[1], cmd->in_file, ft_strlen(cmd->in_file));
        close(pipefd[1]);
        cmd->in = pipefd[0];
    }
}


int execution_proto(cmd* cmd, char** env) 
{
    int exit_status = 0;
    int pipe_fd[2];
   while (cmd)
   {
        // check ila cmd kitbda b ./
        // ila kant lcmd dial lit3tat lk absolute, /bin/ls
        char* cmd_abs_path = find_abs_path(cmd->argv[0]);
        if (cmd->has_pipe) 
        {
            pipe(pipe_fd);
            cmd->out = pipe_fd[1];
            cmd->next->in = pipe_fd[0];
        }
        if (!cmd_abs_path) 
        {
            printf("minishell: %s: command not found\n", cmd->argv[0]); // print f stderro later
            exit_status = 127;
            close(cmd->out);
            cmd = cmd->next;
            continue;
        }
        check_redirections(cmd);
        cmd->argv[0] = cmd_abs_path;
        int child_pid = fork();
        if (child_pid == 0) 
        {
            if (cmd->out != 1)
            {
                dup2(cmd->out, 1);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            if (cmd->in != 0)
            {
                dup2(cmd->in, 0);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            } 
            execve(cmd_abs_path, cmd->argv, env);
            printf("an error occured when executing %s\n", cmd->argv[0]);
        }
        if (cmd->out != 1)
            close(cmd->out);
        if (cmd->in != 0)
            close(cmd->in);
        cmd = cmd->next;
   }
   while (wait(&exit_status) > 0);
   return WEXITSTATUS(exit_status);
}

cmd* create_node() 
{
    cmd* ret = malloc(sizeof(cmd));
    ft_memset(ret, 0, sizeof(cmd));
    ret->out = 1;
    return ret;
}
//cat < input.txt

void test_pipes()
{
    char* cmd1_argv[] = {"echo", "-n", NULL};
    char* cmd2_argv[] = {"head", "n", NULL};
    char* cmd3_argv[] = {"wc", "-c", NULL};

    cmd* cmd_node = create_node();
    cmd_node->argv = cmd1_argv;
    cmd_node->has_pipe = 1;
    cmd_node->next = create_node();
    
    cmd_node->next->argv = cmd2_argv;
    cmd_node->next->has_pipe = 1;
    cmd_node->next->next = create_node();
    
    cmd_node->next->next->argv = cmd3_argv;

    int exit_status = execution_proto(cmd_node, NULL);
}

// working
void redirections_test() {
    char* cmd1_redir_argv[] = {"ls", "-la", "dfkahfkahsdk", NULL};

    // cat -e < Makefile > Makefile2
    // cat -e
    cmd* cmd_node = create_node();
    cmd_node->argv = cmd1_redir_argv;
    // < Makefile
    cmd_node->in_redir_type = HEREDOC;
    cmd_node->in_file = "Hello\nworld\nfrom\nheredoc\n";
    // > Makefile
    cmd_node->out_redir_type = WRITEOUT;
    cmd_node->out_file = "heredoc_output.txt";
    int exit_status = execution_proto(cmd_node, NULL);
}


int main() {
    char* cmd1_argv[] = {"./test", NULL};
    char* cmd2_argv[] = {"cat", "-e", NULL};

    cmd* cmd_node = create_node();
    cmd_node->argv = cmd1_argv;
    cmd_node->has_pipe = 1;
    cmd_node->next = create_node();
    
    cmd_node->next->argv = cmd2_argv;
    // cmd_node->next->has_pipe = 1;
    

    int exit_status = execution_proto(cmd_node, NULL);
    return 0;
}

