#include "./includes/ms.h"

void	ms_manage_builtin_child_fd(t_data *data, int *_pipe_fd, int *_fd, int *_out)
{
	if (data->processes && data->count_child > 0)
		dup2(_pipe_fd[READ], STDIN_FILENO);
	if (data->redirect_output)
	{
		dup2(data->fd[1], _out[1]);
		close(data->fd[1]);
	}
	else if (data->processes > 1)
		dup2(_fd[WRITE], STDOUT_FILENO);
	if (_pipe_fd[0] != -1)
		close(_pipe_fd[0]);
	close(_fd[WRITE]);
	close(_fd[READ]);

/*	// if there is "|", the input for builtin is always from stdin
	if (data->processes && data->processes <= data->count_pipe)
		dup2(_pipe_fd[READ], STDIN_FILENO);
	if (data->redirect_output)
	{
		//dup2(data->fd[1], 1);
//		close(data->fd[1]);
//		dup2(_out[1], STDOUT_FILENO);
		dup2(data->fd[1], _out[1]);
		close(data->fd[1]);
	}
	else if (data->processes > 1) // if not the last pipe
		dup2(_fd[WRITE], STDOUT_FILENO); // output in the pipe
	if (data->processes)
	{
		close(_fd[WRITE]);
		close(_fd[READ]);
	}*/
}

void	ms_manage_builtin_parent_fd(t_data *data, int *_pipe_fd, int *_fd)
{
	if (data->redirect_output)
	{
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

/*	if (data->redirect_output)
	{
		close(data->fd[1]);
		data->redirect_output = 0;
	}
	else if (data->processes > 1) // executed pipes > 1
	{
		//_pipe_fd[READ] = _fd[READ];
		dup2(_pipe_fd[READ], _fd[READ]);
	}
	if (data->processes)
	{
		close(_fd[WRITE]);
		close(_fd[READ]);
	}*/
}

int	ms_builtin_as_child_process(t_data *data, char **_cmd, int *_pipe_fd)
{
	pid_t	pid;
	int		_fd[2];
	int		_out[2];
	int		status;

	_out[1] = STDOUT_FILENO;
//	if (data->redirect_output)
//		_out[1] = data->fd[1];
	if (pipe(_fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
/*	if (data->processes > 1) // if there is pipe without redir or with
	{
		if (pipe(_fd) == -1)
			return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	}*/
	if ((pid = fork()) == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	else if (pid == 0)
	{
		ms_manage_builtin_child_fd(data, _pipe_fd, _fd, _out);
		status = ms_builtin_execution(data, _cmd, _out);
		exit(WEXITSTATUS(status));
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
	//dup2(data->fd[1], STDOUT_FILENO); // if dup2, it gets stuck
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
// no pipe process, but can have redir
	if (data->processes == 0)
		status = ms_builtin_as_simple_cmd(data, _cmd);
// builtin inside a pipe process with or without redir
	else
	{
		status = ms_builtin_as_child_process(data, _cmd, _pipe_fd);
		data->count_child++;
	}
	return (status);
}
