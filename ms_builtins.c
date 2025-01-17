#include "./includes/ms.h"

int	builtins(char *cmd)
{
	return (ft_strequ(cmd, "echo") || ft_strequ(cmd, "cd")
		|| ft_strequ(cmd, "pwd") || ft_strequ(cmd, "export")
		|| ft_strequ(cmd, "unset") || ft_strequ(cmd, "env")
		|| ft_strequ(cmd, "exit"));
}

int	ms_builtin_execution(t_data *data, char **_cmd, int *_out)
{
	if (!_cmd || !_cmd[0])
		return (FAILURE);
	if (ft_strequ(_cmd[0], "cd"))
		return (ms_cd(data, _cmd));
	else if (ft_strequ(_cmd[0], "echo")) //accept out
		return (ms_echo(data, _cmd, _out));
	else if (ft_strequ(_cmd[0], "env")) //accept out
		return (ms_env(data, _cmd, _out));
	else if (ft_strequ(_cmd[0], "exit"))
		return (ms_exit(data, _cmd));
	else if (ft_strequ(_cmd[0], "export")) //accept out without more args
		return (ms_export(data, _cmd, _out));
	else if (ft_strequ(_cmd[0], "pwd")) //accept out
		return (ms_pwd(data, _cmd, _out));
	else if (ft_strequ(_cmd[0], "unset"))
		return (ms_unset(data, _cmd));
	else
		return (SUCCESS);
}
