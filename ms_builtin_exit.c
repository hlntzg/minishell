#include "./includes/ms.h"

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
 * for exit command. If there is an invalid argument, exit code is set to 2,
 * which is a standard exit code for invalid arguments in many commands, 
 * including exit. If there is more than one argument, exit code is set to 1, and
 * error message is display.
 */
int	ms_exit(t_data *data, char **_cmd)
{
	int	exit_code;

	exit_code = 0;
	if (_cmd[1] && invalid_exit_arg(_cmd[1]))
	{
		// It exits minishell, but it's better to return and clean up in main before.
		if (!data->processes)
			ft_putendl_fd("exit", STDOUT_FILENO);
		return (ms_error(ERR_EXIT_BAD_ARG, NULL, 2, 2)); //data->exit_code = 2;
	}
	else if (count_cmd_args(_cmd) > 2)
	{
		if (!data->processes)
			ft_putendl_fd("exit", STDOUT_FILENO);
		return (ms_error(ERR_EXIT_ARGS, NULL, 1, 1)); //data->exit_code = 1;
	}
	else
	{
		// It exits minishell, but it's better to return and clean up in main before.
		if (!data->processes)
			ft_putendl_fd("exit", STDOUT_FILENO);
		if (_cmd[1])
			exit_code = ft_atoi(_cmd[1]) % 256;
			//exit (ft_atoi(_cmd[1]) % 256); //	data->exit_code = ft_atoi(_cmd[1]) % 256;
		else
			exit_code = data->exit_code;///exit (data->exit_code);
		//return (SUCCESS);
	}
	if (!data->processes)
		free_and_exit_minishell(data, exit_code); //exit (exit_code); // free_and_exit_minishell(data, exit_code);
	return (exit_code);
}
