/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:39:19 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/30 12:39:23 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int	ms_echo(t_data *data, char **node) //t_node or char **
{
	int	option_n;
	int	i;

	option_n = 0;
	i = 1;
	while (node[i] && valid_echo_option(node[i]))
	{
		option_n = 1;
		i++;
	}
	while (node[i])
	{
		if (ft_strequ(node[i], "~"))
			printf("$HOME\n");
		else
			ft_putstr_fd(node[i], 1);
		if (node[++i])	
			ft_putchar_fd(' ', 1);
	}
	if (!option_n)
		ft_putchar_fd('\n', 1);
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}