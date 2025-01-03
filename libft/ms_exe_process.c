#include "./includes/ms.h"

int	builtins(char *cmd)
{
	return (ft_strequ(cmd, "echo") || ft_strequ(cmd, "cd")
		|| ft_strequ(cmd, "pwd") || ft_strequ(cmd, "export")
		|| ft_strequ(cmd, "unset") || ft_strequ(cmd, "env")
		|| ft_strequ(cmd, "exit"));
}

int	ms_exe_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strequ(cmd->command, "cd"))
		return (ms_cd(data, cmd));
	else if (ft_strequ(cmd->command, "echo"))
		return (ms_echo(data, cmd));
	else if (ft_strequ(cmd->command, "env"))
		return (ms_env(data, cmd));
	else if (ft_strequ(cmd->command, "exit"))
		return (ms_exit(data, cmd));
	else if (ft_strequ(cmd->command, "export"))
		return (ms_export(data, cmd));
	else if (ft_strequ(cmd->command, "pwd"))
		return (ms_pwd(data, cmd));
	else if (ft_strequ(cmd->command, "unset"))
		return (ms_unset(data, cmd));
	else
		return (SUCCESS);
}

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
	/*else if (data->total_process == data->total_cmds - 1)
		last_process(data, cmd);
	else
		middle_process(data, cmd);*/
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

int	ms_execute_newline(t_data *data)
{
	//call lexing, parsing, etc
	data->cmd = malloc(sizeof(t_cmd));
//	data->cmd->args = NULL;
//	data->cmd->command = NULL;
	data->cmd->args = ft_split(data->input_user, ' ');
	data->cmd->command = data->cmd->args[0];
	data->total_cmds = 1;

	if (ms_pre_exe_newline(data) != SUCCESS)
		return (FAILURE);
	if (data->total_cmds == 1)
	{
		if (builtins(data->cmd->command))
			return (ms_exe_builtin(data, data->cmd));
		else
			return (ms_exe_simple_cmd(data, data->cmd));
	}
	else
		printf("there is pipe\n");
}
