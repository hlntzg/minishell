#include "./includes/ms.h"

int	builtins(char *cmd)
{
	return (ft_strequ(cmd, "echo") || ft_strequ(cmd, "cd")
		|| ft_strequ(cmd, "pwd") || ft_strequ(cmd, "export")
		|| ft_strequ(cmd, "unset") || ft_strequ(cmd, "env")
		|| ft_strequ(cmd, "exit"));
}

int	ms_exe_builtin(t_data *data, char **args)
{
	if (ft_strequ(args[0], "cd"))
		return (ms_cd(data, args));
	else if (ft_strequ(args[0], "echo"))
		return (ms_echo(data, args));
	else if (ft_strequ(args[0], "env"))
		return (ms_env(data, args));
	else if (ft_strequ(args[0], "exit"))
		return (ms_exit(data, args));
	else if (ft_strequ(args[0], "export"))
		return (ms_export(data, args));
	else if (ft_strequ(args[0], "pwd"))
		return (ms_pwd(data, args));
	else if (ft_strequ(args[0], "unset"))
		return (ms_unset(data, args));
	else
		return (SUCCESS);
}

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

void	child_process(t_data *data, char **_cmd)
{
//	if (data->total_process == 0)
//		first_process(data, _cmd);
//	else if (data->total_process == data->total_cmds - 1)
//		last_process(data, _cmd);
//	else
//		middle_process(data, cmd);
	//if (data->total_cmds != 1)
	//	close_pipes_fd();
	ms_exe_child_process(data, _cmd);
	//return (SUCCESS);
}

int	ms_exe_simple_cmd(t_data *data, char **_cmd)
{
	int		status;

	data->pid[0] = fork();
	{
		if (data->pid[0] == -1)
			return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
		if (data->pid[0] == 0)
			child_process(data, _cmd);
	}
	waitpid(data->pid[0], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}

int	ms_execute_newline(t_data *data)
{
	data->total_cmds = 1;
	data->total_process = 0;

	if (ms_pre_exe_newline(data) != SUCCESS)
		return (FAILURE);
	if (data->total_cmds == 1)
	{
		if (builtins(data->tree->value[0]))
			return (ms_exe_builtin(data, data->tree->value));
		else
			return (ms_exe_simple_cmd(data, data->tree->value));
	}
	else
		printf("there is pipe\n");
	return (0);
}
