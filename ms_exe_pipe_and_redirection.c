/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe_pipe_and_redirection.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:18:35 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/18 09:31:29 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

void	ms_handle_redirection_missing_cmd(t_data *data, int *_pipe_fd)
{
	data->processes -= 1;
	if (data->redirect_input)
	{
		data->redirect_input = 0;
		if (data->fd[0] != -2)
			close(data->fd[0]);
		data->fd[0] = -2;
		if (_pipe_fd[0] != -1)
			close(_pipe_fd[0]);
	}
	if (data->redirect_output)
	{
		data->redirect_output = 0;
		if (data->fd[1] != -2)
			close(data->fd[1]);
		data->fd[1] = -2;
		if (_pipe_fd[1] != -1)
			close(_pipe_fd[1]);
	}
}

int	ms_handle_redirection_execution(t_data *data,
		t_tree_node *ast, int *_pipe_fd)
{
	int	status;

	if (ast->right)
		status = ms_open_file(data, ast->right, ast);
	if (!ast->left || status == 1)
	{
		if (data->processes > 1)
			ms_handle_redirection_missing_cmd(data, _pipe_fd);
	}
	else if (ast->left && ast->left->status == EXECUTE_CMD && g_sig != 2)
		status = ms_exe_command(data, ast->left->value, _pipe_fd);
	else if (ast->left && ast->left->type == PIPE)
		status = ms_handle_pipe_execution(data, ast->left, _pipe_fd);
	else if (ast->left && (ast->left->type == REDIN
			|| ast->left->type == HEREDOC || ast->left->type == REDOUT_T
			|| ast->left->type == REDOUT_A))
		status = ms_handle_redirection_execution(data, ast->left, _pipe_fd);
	return (status);
}

int	ms_handle_pipe_execution(t_data *data, t_tree_node *ast, int *_pipe_fd)
{
	int	status;

	if (ast->status == EXECUTE_CMD)
		status = ms_exe_command(data, ast->value, _pipe_fd);
	if (ast->type == REDIN || ast->type == HEREDOC
		|| ast->type == REDOUT_T || ast->type == REDOUT_A)
		return (ms_handle_redirection_execution(data, ast, _pipe_fd));
	if (ast->left)
		status = ms_handle_pipe_execution(data, ast->left, _pipe_fd);
	if (ast->right)
		status = ms_handle_pipe_execution(data, ast->right, _pipe_fd);
	return (status);
}
