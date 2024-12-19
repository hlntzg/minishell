#include "./includes/ms.h"

int	arguments_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/** 
 * invalid_exit_arg - Checks if the given string is a valid exit argument.
 *
 * valid: 123 -266 +22 999999
 * invalid: abc 1h3ll@ 172981720972901902102912801
 *
 * Return: true if the string is invalid; false if valid.
 */
static bool	invalid_exit_arg(char *str)
{
	int	i;
	
	if (!str || ft_atol(str) <= LONG_MIN || ft_atol(str) >= LONG_MAX)
		return (true);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (true);
		i++;
	}
	return (false);
}

/**
 * exit - Builtin exit function
 *
 * Successfully exit minishell if there is only one valid (or none) argument
 * for exit command. If there is an invalid argument, exit code is set to 2, which
 * is a standard exit code for invalid arguments in many commands, including exit.
 * If there is more than one argument, exit code is set to 1, and error message is
 * display.
 */
int	ms_exit(t_data *data, t_cmd *cmd)
{
	(void) data;
	if (cmd->args[1] && invalid_exit_arg(cmd->args[1]))
	{
		// (NOT SURE IF EXIT FOR SURE) exit with exit_code = 2;
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (ft_putendl_fd(ERR_EXIT_BAD_ARG, STDERR_FILENO), 2); // error exit_code=2
	}
	else if (arguments_count(cmd->args) > 2)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (ft_putendl_fd(ERR_EXIT_ARGS, STDERR_FILENO), 1); // error exit_code=1
	}
	else
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		if (cmd->args[1])
			exit (ft_atoi(cmd->args[1]) % 256);
		else
		// gets the last exit code from previous process, not always 0
			exit (0);
	}
}
