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
bool unclosed_quotes(char *str)
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

//error checker function