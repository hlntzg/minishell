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
		printf("execute %s\n", cmd->command);
	else if (ft_strequ(cmd->command, "echo"))
		ms_echo(data, cmd);
	else if (ft_strequ(cmd->command, "env"))
		ms_env(data, cmd);
	else if (ft_strequ(cmd->command, "exit"))
		ms_exit(data, cmd);
	else if (ft_strequ(cmd->command, "export"))
		printf("execute %s\n", cmd->command);
	else if (ft_strequ(cmd->command, "pwd"))
		printf("execute %s\n", cmd->command);
	else if (ft_strequ(cmd->command, "unset"))
		printf("execute %s\n", cmd->command);
}

void	ms_execute_newline(t_data *data)
{
	//call lexing, parsing, etc
	data->cmd = malloc(sizeof(t_cmd));
	data->cmd->args = NULL;
	data->cmd->command = NULL;
	data->cmd->args = ft_split(data->input_user, ' ');
	data->cmd->command = data->cmd->args[0];
	data->total_cmds = 1;


	if (data->total_cmds == 1 && builtins(data->cmd->command))
		ms_exe_builtin(data, data->cmd);
	else
	{
		printf("cmd isnt builtin or there is pipe\n");
	}
}
