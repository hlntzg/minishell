#include "./includes/ms.h"

int	builtins(char *cmd)
{
	return (ft_strequ(cmd, "echo") || ft_strequ(cmd, "cd")
		|| ft_strequ(cmd, "pwd") || ft_strequ(cmd, "export")
		|| ft_strequ(cmd, "unset") || ft_strequ(cmd, "env")
		|| ft_strequ(cmd, "exit"));
}

void	ms_exe_builtin(t_data *data, t_cmd *cmd)
{
	(void)data;
	if (ft_strequ(cmd->command, "cd"))
		ms_cd(data, cmd);
	else if (ft_strequ(cmd->command, "echo"))
		ms_echo(data, cmd);
	else if (ft_strequ(cmd->command, "env"))
		ms_env(data, cmd);
	else if (ft_strequ(cmd->command, "exit"))
		ms_exit(data, cmd);
	else if (ft_strequ(cmd->command, "export"))
		ms_export(data, cmd);
	else if (ft_strequ(cmd->command, "pwd"))
		ms_pwd(data, cmd);
	else if (ft_strequ(cmd->command, "unset"))
		ms_unset(data, cmd);
}

int	ms_exe_child_process(t_data *data, t_cmd *cmd)
{
	char	*absolute_path;

	if (builtins(data->cmd->command))
		ms_exe_builtin(data, cmd);
	else
	{
		absolute_path = get_abs_path(cmd->command, data->envp_path);
		if (execve(absolute_path, cmd->args, data->envp) == -1)
			return (ERR_CMD_EXECVE);
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
//	(void)data;
//	printf("cmd %s isnt builtin but there is no pipe\n", cmd->command);
	int		status;

	data->pid = fork();
	{
		if (data->pid == -1)
			return (ft_putendl_fd(ERR_PROCESS_FORK, STDERR_FILENO), FAILURE);
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
	data->cmd->args = NULL;
	data->cmd->command = NULL;
	data->cmd->args = ft_split(data->input_user, ' ');
	data->cmd->command = data->cmd->args[0];
	data->total_cmds = 1;
	data->envp = env_get_array_str(data);
	data->envp_path = exe_get_path(data->envp);

	if (data->total_cmds == 1 && builtins(data->cmd->command))
	{
		ms_exe_builtin(data, data->cmd);
		return (0); // need to update builtins
	}
	else if (data->total_cmds == 1)
		return (ms_exe_simple_cmd(data, data->cmd));
	else
		printf("there is pipe\n");
}
