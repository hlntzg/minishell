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
 */
int	ms_echo(t_data *data, char **_cmd, int *_out)
{
	int		i;
	int		option_n;
	char	*home;

	i = 1;
	option_n = 0;
	while (_cmd[i] && valid_echo_option(_cmd[i]))
	{
		option_n = 1;
		i++;
	}
	while (_cmd[i])
	{
		if (ft_strequ(_cmd[i], "~"))
		{
			home = env_get_value(data, "HOME");
			ft_putstr_fd(home, _out[1]);
			free(home);
		}
		else
			ft_putstr_fd(_cmd[i], _out[1]);
		if (_cmd[++i])	
			ft_putchar_fd(' ', _out[1]);
	}
	if (!option_n)
		ft_putchar_fd('\n', _out[1]);
	data->exit_code = 0;
	return (SUCCESS);
}
