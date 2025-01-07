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


