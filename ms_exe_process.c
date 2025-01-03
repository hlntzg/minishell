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
/*
int	ms_exe_child_process(t_data *data, t_cmd *cmd)
{
	char	*absolute_path;

	if (builtins(data->cmd->command))
		return (ms_exe_builtin(data, cmd));
	else
	{
		absolute_path = get_abs_path(cmd->command, data->envp_path);
		if (execve(absolute_path, cmd->args, data->envp) == -1)
			return (ms_error(ERR_PROCESS_EXECVE, NULL, 1, ERR_CMD_EXECVE);
	}
	return (SUCCESS);
}

void	child_process(t_data *data, t_cmd *cmd)
{
	if (data->total_process == 0)
		first_process(data, cmd);
	else if (data->total_process == data->total_cmds - 1)
		last_process(data, cmd);
	else
		middle_process(data, cmd);
	//if (data->total_cmds != 1)
	//	close_pipes_fd();
	ms_exe_child_process(data, cmd);
	return (SUCCESS);
}

int	ms_exe_simple_cmd(t_data *data, t_cmd *cmd)
{
	int		status;

	data->pid = fork();
	{
		if (data->pid == -1)
			return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
		if (data->pid == 0)
			child_process(data, cmd);
	}
	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}
*/
int	ms_execute_newline(t_data *data)
{
	char	**args;

	args = ft_split(data->input_user, ' ');
	data->total_cmds = 1;

	//if (ms_pre_exe_newline(data) != SUCCESS)
	//	return (FAILURE);
	if (data->total_cmds == 1)
	{
		if (builtins(args[0]))
			return (ms_exe_builtin(data, args));
		else
	//		return (ms_exe_simple_cmd(data, data->cmd));
			printf("there is a non builtin command\n");
	}
	else
		printf("there is pipe\n");

	return (0);
}
