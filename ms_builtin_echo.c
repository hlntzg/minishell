#include "./includes/ms.h"

/**
 * valid_echo_option - Checks if the given string is a valid echo option.
 * 
 * Valid option: '-' followed by one or more 'n' characters.
 *
 * Return: true if valid option, false otherwise.
 */
static bool	valid_echo_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || !str[1])
		return (false);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/**
 * echo - Builtin echo function 
 *
 * NOTE: do not accept redirections, fd set to 1 for now
 */
int	ms_echo(t_data *data, t_cmd *cmd)
{
	int	option_n;
	int	i;

	option_n = 0;
	i = 1;
	while (cmd->args[i] && valid_echo_option(cmd->args[i]))
	{
		option_n = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[++i])	
			ft_putchar_fd(' ', 1);
	}
	if (!option_n)
		ft_putchar_fd('\n', 1);
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}
