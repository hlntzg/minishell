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
int	ms_echo(t_data *data, t_tree_node *node) //t_node or char **
{
	int	option_n;
	int	i;

	(void)data;
	option_n = 0;
	i = 1;
	while (node->value[i] && valid_echo_option(node->value[i]))
	{
		option_n = 1;
		i++;
	}
	while (node->value[i])
	{
		if (ft_strequ(node->value[i], "~"))
			printf("$HOME\n");
		else
			ft_putstr_fd(node->value[i], 1);
		if (node->value[++i])	
			ft_putchar_fd(' ', 1);
	}
	if (!option_n)
		ft_putchar_fd('\n', 1);
	//if (data->total_cmds == 1)
	//	return (SUCCESS);
	return (SUCCESS);
}