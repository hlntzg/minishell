#include "./includes/ms.h"

int	ms_exe_child_process(t_data *data, char **_cmd)
{
	struct stat path_stat;
	
	if (builtins(_cmd[0]))
		return (ms_exe_builtin(data, _cmd));
	else
	{
		char	*command = _cmd[0];

		if (ft_strcmp(_cmd[0], ".") == 0)
			return (ms_error(_cmd[0], ERR_FILE_ARG_REQUIRED, 127, 127));
        else if (ft_strcmp(_cmd[0], "..") == 0)
            return (ms_error(command, ERR_CMD_NOT_FOUND, 127, 127));

		if (env_get_key(data, "PATH") == 0)
			return (ms_error(command, ERR_NO_FILE_OR_DIR, 127, 127));

		_cmd[0] = get_abs_path(_cmd[0], data->envp_path);
		printf("_cmd[0] of get_abs_path: %s\n", _cmd[0]);
		if (!_cmd[0])
		{
			if (ft_strchr(command, '/'))
				return (ms_error(command, ERR_NO_FILE_OR_DIR, 127, 127));
			return (ms_error(command, ERR_CMD_NOT_FOUND, 127, 127));
		}
		if (stat(_cmd[0], &path_stat) == -1)
			return (ms_error(_cmd[0], strerror(errno), 127, 127));
		if (S_ISDIR(path_stat.st_mode))
			return (ms_error(_cmd[0], ERR_IS_DIR, 126, 126));
		if (access(_cmd[0], X_OK) == -1)
		{
			if (errno == EACCES)
				return (ms_error(_cmd[0], ERR_PERMISSION, 126, 126));
			else
				return (ms_error(_cmd[0], strerror(errno), 126, 126));
		}
		if (execve(_cmd[0], _cmd, data->envp) == -1)
			return (ms_error(_cmd[0], strerror(errno), 1, 1));
	}
	return (SUCCESS);
}

void	ms_manage_child_fd(t_data *data, int *_pipe_fd, int *_fd)
{
	if (data->redirect_input)
	{
		dup2(data->fd[0], 0);
		close(data->fd[0]);
	}
	else if (data->processes && data->processes <= data->count_pipe) // if there is 'executed pipes' && _piped[0] <= _piped[5] (??)
		dup2(_pipe_fd[READ], STDIN_FILENO);
	if (data->redirect_output)
	{
		dup2(data->fd[1], 1);
		close(data->fd[1]);
	}
	else if (data->processes > 1) // if 'executed pipes' > 1 (not first cmd)
		dup2(_fd[WRITE], STDOUT_FILENO);
	close(_fd[WRITE]);
	close(_fd[READ]);
}

void	ms_manage_parent_fd(t_data *data, int *_pipe_fd, int *_fd)
{
	if (data->redirect_input)
	{
		close(data->fd[0]);
		data->redirect_input = 0;
	}
	if (data->redirect_output)
	{
		close(data->fd[1]);
		data->redirect_output = 0;
	}
	close(_fd[WRITE]);
	if (data->processes > 1) // executed pipes > 1
		_pipe_fd[READ] = _fd[READ];
	else
		close(_fd[READ]);
}
int	ms_exe_external_cmd(t_data *data, char **_cmd, int *_pipe_fd)
{
	pid_t	pid;
	int		_fd[2];

	if (pipe(_fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	if ((pid = fork()) == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	else if (pid == 0)//child_process
	{
	//	if (data->processes && data->processes <= data->count_pipe) // if there is 'executed pipes' && _piped[0] <= _piped[5] (??)
	//		dup2(_pipe_fd[READ], STDIN_FILENO);
	//	if (data->processes > 1) // if 'executed pipes' > 1 (not first cmd)
	//		dup2(_fd[WRITE], STDOUT_FILENO);
	//	else
	//		close(_pipe_fd[READ]);
	//	close(_fd[WRITE]);
	//	close(_fd[READ]);
		ms_manage_child_fd(data, _pipe_fd, _fd);
		ms_exe_child_process(data, _cmd); // here execve the command
	}
	ms_manage_parent_fd(data, _pipe_fd, _fd);
	//close(_fd[WRITE]);
	//close(_pipe_fd[READ]);
	//if (data->processes > 1) // executed pipes > 1
	//	_pipe_fd[READ] = _fd[READ];
	//else
	//	close(_fd[READ]);
	return (1);
}

int	ms_execute_newline(t_data *data)
{
	data->total_cmds = 2;
	data->total_process = 0;

	if (ms_pre_exe_newline(data) != SUCCESS)
		return (FAILURE);
//	if (data->total_cmds == 1)
//	{
//		if (builtins(data->tree->value[0]))
//			return (ms_exe_builtin(data, data->tree->value));
//		else
//			return (ms_exe_external_cmd(data, data->tree->value));
//	}
//	else
	return (ms_exe_pipeline(data));
}
