/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:02:53 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/30 13:02:55 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Set up pipes for child process
void setup_pipes_for_child(int **pipes, int pipe_count, int cmd_index)
{
    if (cmd_index > 0)
        dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
    if (cmd_index < pipe_count)
        dup2(pipes[cmd_index][1], STDOUT_FILENO);
    for (int i = 0; i < pipe_count; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

// Execute single command with proper pipe setup
void execute_command_node(t_tree_node *cmd, int **pipes, int pipe_count, int cmd_index, pid_t *pids)
{
    char **args;

    pids[cmd_index] = fork();
    if (pids[cmd_index] == -1)
        return handle_error("Fork failed");
        
    if (pids[cmd_index] == 0)
    {
        setup_pipes_for_child(pipes, pipe_count, cmd_index);
        handle_redirections(cmd);
        args = build_command_args(cmd);
        execvp(args[0], args);
        exit(EXIT_FAILURE);
    }
}

// Main recursive function to execute commands
void execute_commands(t_tree_node *node, int **pipes, int pipe_count, pid_t *pids)
{
    static int cmd_index;
    
    cmd_index = 0;
    if (!node)
        return;
    if (node->type == PIPE)
    {
        execute_command_node(node->left, pipes, pipe_count, cmd_index, pids);
        cmd_index++;
        execute_commands(node->right, pipes, pipe_count, pids);
    }
    else
        execute_command_node(node, pipes, pipe_count, cmd_index, pids);
}

// Create array of pipes
int **create_pipes(int pipe_count)
{
    int **pipes;
    int i;

    pipes = malloc(sizeof(int *) * pipe_count);
    if (!pipes)
        return (NULL);
    i = 0;
    while (i < pipe_count)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i])
        {
            free_pipe_array(pipes, i);
            return (NULL);
        }
        if (pipe(pipes[i]) == -1)
        {
            free_pipe_array(pipes, i);
            return (NULL);
        }
        i++;
    }
    return (pipes);
}

// Helper function to count pipes in AST
int count_pipes(t_tree_node *node)
{
    int count;

    count = 0;
    while (node && node->type == PIPE)
    {
        count++;
        node = node->right;
    }
    return (count);
}

void execute_pipeline(t_tree_node *ast_head)
{
    int pipe_count;
    int cmd_count;
    int **pipes;
    pid_t *pids;
    
    pipe_count = count_pipes(ast_head);
    cmd_count = pipe_count + 1;
    pipes = NULL;
    pids = NULL;
    pipes = create_pipes(pipe_count);
    if (!pipes)
        return handle_error("Failed to create pipes"); // don't have
    pids = malloc(sizeof(pid_t) * cmd_count);
    if (!pids)
    {
        cleanup_pipes(pipes, pipe_count);
        return (handle_error("Failed to allocate PIDs array"));
    }
    execute_commands(ast_head, pipes, pipe_count, pids);
    cleanup_pipes(pipes, pipe_count); //don't have
    wait_for_children(pids, cmd_count); // don't have
    free(pids);
    free_pipe_array(pipes, pipe_count);
}
