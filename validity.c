/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:38:54 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/03 14:38:55 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// we can use int if bool is not permitted
bool closed_quotes(char *str)
{
	char	type;

	type = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (type == *str)
				type = 0;
			else if (type == 0)
				type = *str;
		}
		*str++;
	}
	if (type == 0)
		return (true);
	else
		return (false);
}

// other kinds of validity checkers: redirections? operators? not sure
bool	valid_redirection(char *str)
{}

bool	valid_pipes(char *str)
{}

//error checker function
bool	lexical_errors(char *str)
{
	if (closed_quotes(str) == false)
	{
		/*ft_putstr_fd: Error message*/
		return (false);
	}
	if (valid_redirection(str) == false)
	{
		/* Error message*/
		return (false);
	}
	if (valid_pipes(str) == false)
	{
		/*Error message*/
		return (false);
	}
	/*logical operators not supported in non-bonus*/
	return (true);
}