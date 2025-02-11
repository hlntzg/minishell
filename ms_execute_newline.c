/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_newline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:40:01 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/11 18:39:05 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

void	ms_exe_set_ast_status(t_tree_node *ast_head)
{
	if (ast_head->type != WORD)
	{
		ast_head->status = READY;
		if (ast_head->type == PIPE)
		{
			if (ast_head->right)
				ast_head->right->status = EXECUTE_CMD;
			if (ast_head->left)
				ast_head->left->status = EXECUTE_CMD;
		}
		if (ast_head->type == REDIN && ast_head->right)
			ast_head->right->status = READ_FROM;
		if (ast_head->type == HEREDOC && ast_head->right)
			ast_head->right->status = READ_HEREDOC;
		if (ast_head->type == REDOUT_T && ast_head->right)
			ast_head->right->status = WRITE_TO_T;
		if (ast_head->type == REDOUT_A && ast_head->right)
			ast_head->right->status = WRITE_TO_A;
	}
	if (ast_head->status == -1)
		ast_head->status = EXECUTE_CMD;
	if (ast_head->left)
		ms_exe_set_ast_status(ast_head->left);
	if (ast_head->right)
		ms_exe_set_ast_status(ast_head->right);
}

int	ms_exe_command(t_data *data, char **_cmd, int *_pipe_fd)
{
	int	status;

	if (builtins(_cmd[0]))
		status = ms_exe_builtin_cmd(data, _cmd, _pipe_fd);
	else
	{
		status = ms_exe_external_cmd(data, _cmd, _pipe_fd);
		data->count_child++;
	}
	if (data->processes > 1)
		data->processes -= 1;
	return (status);
}

static int	wait_pid(t_data *data, pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	signal(SIGINT, handle_sigint_exe);
	while (i < data->count_child)
	{
		waitpid(pid[i++], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
	}
	restore_main_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}

int	ms_exe_ast(t_data *data, t_tree_node *ast)
{
	int	pipe_fd[2];
	int	status;

	status = 0;
	pipe_fd[READ] = -1;
	pipe_fd[WRITE] = -1;
	if (ast->status == EXECUTE_CMD)
		status = ms_exe_command(data, ast->value, pipe_fd);
	if (ast->status == READY)
	{
		if (ast->type == PIPE)
			status = ms_handle_pipe_execution(data, ast, pipe_fd);
		if (ast->type == REDIN || ast->type == HEREDOC
			|| ast->type == REDOUT_T || ast->type == REDOUT_A)
			status = ms_handle_redirection_execution(data, ast, pipe_fd);
	}
	if (data->count_child)
		status = wait_pid(data, data->pid);
	if (pipe_fd[READ] != -1)
		close(pipe_fd[READ]);
	if (pipe_fd[WRITE] != -1)
		close(pipe_fd[WRITE]);
	close_heredoc_fds(data->tree);
	return (status);
}

int	ms_execute_newline(t_data *data, int *status)
{
	if (ms_pre_exe_newline(data) != SUCCESS)
		return (FAILURE);
	ms_exe_set_ast_status(data->tree);
	ms_exe_set_heredoc(data, data->tree);
	if (g_sig != SIGINT)
		*status = ms_exe_ast(data, data->tree);
	if (g_sig == SIGINT)
		*status = 130;
	if (g_sig == SIGQUIT)
		*status = 131;
	g_sig = 0;
	update_minishell(data, *status);
	return (SUCCESS);
}
