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
	if (*str == '|' || *str == '&')
        return (false);
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (type == *str)
				type = 0;
			else if (type == 0)
				type = *str;
		}
		str++;
	}
	if (type == 0)
		return (true);
	else
		return (false);
}

// other kinds of validity checkers: redirections? operators? not sure
bool	valid_redirection(char *str)
{
	char    *temp;
    int     s_quote;
    int     d_quote;

    s_quote = 0;
    d_quote = 0;
    temp = NULL;
    while (*str)
    {
        quote_count(str, &s_quote, &d_quote);
        if (!(s_quote % 2) && !(d_quote % 2) && is_redirection(str))
        {
            *temp = *str;
            str++;
            if (*temp == *str)
                str++;
            while (*str && (*str == ' ' || *str == '\t'))
                str++;
            if (*str == '\0' || *str == '>' || *str == '<' || *str == '|')
                return (false); //syntax error message
        }
    }
    return (true);
}

bool	valid_pipes(char *str, int command)
{
	int s_quote;
    int d_quote;

    s_quote = 0;
    d_quote = 0;
    while (*str)
    {
        quote_count(str, &s_quote, &d_quote);
        if (*str == '|' && !(s_quote % 2) && !(d_quote % 2))
        {
            if (command)
                return (false);
            command = 1;
        }
        else if (*str != ' ' || *str != '\t')
            command = 0;
        str++;
    }
    return (true);
}

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
	if (valid_pipes(str, 0) == false)
	{
		/*Error message*/
		return (false);
	}
	/*logical operators not supported in non-bonus*/
	return (true);
}