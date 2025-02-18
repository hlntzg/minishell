/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe_builtin_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:30:08 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/11 10:21:58 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

void	ms_manage_builtin_child_fd(t_data *data, int *_pipe_fd,
			int *_fd, int *_out)
{
	if (data->redirect_input)
	{
		if (data->fd[0] == -1)
			close_free_and_exit_child(data, _pipe_fd, _fd);
		close(data->fd[0]);
	}
	if (data->processes && data->count_child > 0)
		dup2(_pipe_fd[READ], STDIN_FILENO);
	if (data->redirect_output)
	{
		if (data->fd[1] == -1)
			close_free_and_exit_child(data, _pipe_fd, _fd);
		dup2(data->fd[1], _out[1]);
		close(data->fd[1]);
	}
	else if (data->processes > 1)
		dup2(_fd[WRITE], STDOUT_FILENO);
	if (_pipe_fd[0] != -1)
		close(_pipe_fd[0]);
}

void	ms_manage_builtin_parent_fd(t_data *data, int *_pipe_fd, int *_fd)
{
	if (data->redirect_input)
	{
		if (data->fd[0] != -1)
			close(data->fd[0]);
		data->redirect_input = 0;
	}
	if (data->redirect_output)
	{
		if (data->fd[1] != -1)
			close(data->fd[1]);
		data->redirect_output = 0;
	}
	if (_pipe_fd[0] != -1)
		close(_pipe_fd[0]);
	if (data->processes > 1)
		_pipe_fd[READ] = _fd[READ];
	else
		close(_fd[READ]);
	close(_fd[WRITE]);
}

int	ms_builtin_as_child_process(t_data *data, char **_cmd, int *_pipe_fd)
{
	int		_fd[2];
	int		_out[2];
	int		status;

	status = 0;
	child_signal();
	_out[1] = STDOUT_FILENO;
	if (pipe(_fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	data->pid[data->count_child] = fork();
	if (data->pid[data->count_child] == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	else if (data->pid[data->count_child] == 0)
	{
		child_signal();
		ms_manage_builtin_child_fd(data, _pipe_fd, _fd, _out);
		close_heredoc_fds(data->tree);
		status = ms_builtin_execution(data, _cmd, _out);
		close_fds(_fd[READ], _fd[WRITE]);
		ms_free_and_exit_child(data, status);
	}
	ms_manage_builtin_parent_fd(data, _pipe_fd, _fd);
	return (1);
}

int	ms_builtin_as_simple_cmd(t_data *data, char **_cmd)
{
	int	status;
	int	_out[2];

	_out[1] = STDOUT_FILENO;
	if (data->redirect_output)
		_out[1] = data->fd[1];
	status = ms_builtin_execution(data, _cmd, _out);
	if (data->redirect_output)
	{
		close(data->fd[1]);
		data->redirect_output = 0;
	}
	return (status);
}

int	ms_exe_builtin_cmd(t_data *data, char **_cmd, int *_pipe_fd)
{
	int	status;

	status = 0;
	if (data->processes == 0)
		status = ms_builtin_as_simple_cmd(data, _cmd);
	else
	{
		status = ms_builtin_as_child_process(data, _cmd, _pipe_fd);
		data->count_child++;
	}
	return (status);
}
