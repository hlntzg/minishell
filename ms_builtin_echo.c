/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:17:00 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/10 18:54:30 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	handle_echo_tilde(t_data *data, int *_out)
{
	char	*home;
	char	*user;
	char	*prefix;
	char	*home_path;

	home = env_get_value(data, "HOME");
	if (ft_strequ(home, ""))
	{
		free(home);
		user = env_get_value(data, "USER");
		prefix = "/home/";
		home_path = ft_strjoin(prefix, user);
		free(user);
		if (home_path && access(home_path, F_OK) == 0)
		{
			ft_putstr_fd(home_path, _out[1]);
			free(home_path);
		}
	}
	else
	{
		ft_putstr_fd(home, _out[1]);
		free(home);
	}
}

/**
 * echo - Builtin echo function 
 *
 */
int	ms_echo(t_data *data, char **_cmd, int *_out)
{
	int		i;
	int		option_n;

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
			handle_echo_tilde(data, _out);
		else
			ft_putstr_fd(_cmd[i], _out[1]);
		if (_cmd[++i])
			ft_putchar_fd(' ', _out[1]);
	}
	if (!option_n)
		ft_putchar_fd('\n', _out[1]);
	return (0);
}
