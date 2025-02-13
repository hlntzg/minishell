/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_validity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:38:54 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/13 10:36:49 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

bool	closed_quotes(char *str)
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
		str++;
	}
	if (type == 0)
		return (true);
	else
		return (false);
}

bool	valid_redirection(char *str)
{
	char	temp;
	int		s_quote;
	int		d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*str)
	{
		quote_count(str, &s_quote, &d_quote);
		if (!(s_quote % 2) && !(d_quote % 2) && is_redirection(str))
		{
			temp = *str;
			str++;
			if (temp == *str)
				str++;
			while (*str && (*str == ' ' || *str == '\t'))
				str++;
			if (*str == '\0' || *str == '>' || *str == '<' || *str == '|')
				return (false);
		}
		str++;
	}
	return (true);
}

bool	valid_pipes(char *str, int command)
{
	int	s_quote;
	int	d_quote;

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
		else if (*str != ' ' && *str != '\t')
			command = 0;
		str++;
	}
	if (command)
		return (false);
	return (true);
}

bool	no_logical_operators(char *str)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*str)
	{
		quote_count(str, &s_quote, &d_quote);
		if (!(s_quote % 2) && !(d_quote % 2) && ((*str == '|'
					&& *(str + 1) == '|')
				|| (*str == '&' && (*str + 1) == '&')))
		{
			return (false);
		}
		str++;
	}
	return (true);
}

bool	no_lexical_errors(char *str)
{
	if (closed_quotes(str) == false)
	{
		ms_error(ERR_SYNTAX, ERR_QUOTES, FAILURE, FAILURE);
		return (false);
	}
	if (valid_redirection(str) == false)
	{
		ms_error(ERR_SYNTAX, ERR_REDIR, FAILURE, FAILURE);
		return (false);
	}
	if (valid_pipes(str, 0) == false)
	{
		ms_error(ERR_SYNTAX, ERR_OPERATOR, FAILURE, FAILURE);
		return (false);
	}
	if (no_logical_operators(str) == false)
	{
		ms_error(ERR_SYNTAX, ERR_LOGICAL_OPERATORS, FAILURE, FAILURE);
		return (false);
	}
	return (true);
}
