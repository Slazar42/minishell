/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:43:17 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/19 00:48:41 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct c {
    char** argv;
    int in;
    int out;
    int has_pipe;
    struct c* next;
    // redirections l8r
} cmd;


// ls -> /bin/ls
// afjkadsf -> NULL (command not found)
char* find_abs_path(char* cmd) {
    // linked list dial envp, ya3ni converti envp -> linked list
    char* raw_path = getenv("PATH");
    char** path_arr = ft_split(raw_path, ':');
    int i = 0;
    while (path_arr[i]) {
        char* fwd_slash = ft_strjoin(path_arr[i], "/");
        char* abs_path = ft_strjoin(fwd_slash, cmd);
        if (access(abs_path, F_OK) == 0) {
            free(fwd_slash);
            free(path_arr);
            // command found
            return abs_path;
        }
        free(fwd_slash);
        free(abs_path);
        i++;
    }
    // command not found
    return NULL;
}


int execution_proto(cmd* cmd, char** env) {
    int exit_status = 0;
    int pipe_fd[2];
   while (cmd) {
        char* cmd_abs_path = find_abs_path(cmd->argv[0]);
        if (!cmd_abs_path) {
            printf("minishell: %s: command not found\n", cmd->argv[0]); // print f stderro later
            cmd = cmd->next;
            continue;
        }
        if (cmd->has_pipe) {
            pipe(pipe_fd);
            cmd->out = pipe_fd[1];
            cmd->next->in = pipe_fd[0];
        }
        cmd->argv[0] = cmd_abs_path;
        int child_pid = fork();
        if (child_pid == 0) {
            if (cmd->out != 1) {
                dup2(cmd->out, 1);
                close(cmd->out);
            }
            if (cmd->in != 0) {
                dup2(cmd->in, 0);
                close(cmd->in);
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
   while (wait(NULL) > 0);
   return exit_status;
}

cmd* create_node() {
    cmd* ret = malloc(sizeof(cmd));
    ft_memset(ret, 0, sizeof(cmd));
    ret->out = 1;
    return ret;
}

int main() {
    char* cmd1_argv[] = {"cat", "/dev/urandom", NULL};
    char* cmd2_argv[] = {"head", "-10", NULL};
    // char* cmd3_argv[] = {"grep", "execution.c", NULL};
    // ls -la |
    cmd* cmd_node = create_node();
    cmd_node->argv = cmd1_argv;
    cmd_node->has_pipe = 1;
    cmd_node->next = create_node();
    
    // cat -e
    cmd_node->next->argv = cmd2_argv;
    // cmd_node->next->has_pipe = 1;
    // cmd_node->next->next = create_node();
    
    // grep execution.c
    // cmd_node->next->next->argv = cmd3_argv;
    
    execution_proto(cmd_node, NULL);
}
 
// int ft_execution(t_cmd *cmd, t_env *env)
// {
//     char **path = ft_split(getenv("PATH"),':');
//     char *cmd_name = cmd->cmd;
//     char *pwd_path = ft_strjoin("/",cmd_name);
//     int i = 0;
//     char* abs_path = NULL;
//     while (path[i] != NULL)
//     {
//         char* fwd_path = ft_strjoin(path[i], "/");
//         abs_path = ft_strjoin(fwd_path, cmd_name);
//         if (access(abs_path, F_OK) == 0) 
//         {
//             free(fwd_path);
//             break;
//         }
//         free(abs_path);
//         free(fwd_path);
//         i++;
//     }
//     i = 0;
//     free(path);
//     printf("executing: %s\n", abs_path);
//     change_home(env);
//     char* argv[] = {abs_path, NULL};
//     int child_pid = fork();
//     if (!child_pid) {
//         execve(abs_path, argv, ft_env(env));
//         ft_putstr_fd("error: execve failed\n", 2);
//         exit(1);
//     }
//     waitpid(child_pid, NULL, 0);
//     return(0);
// }
