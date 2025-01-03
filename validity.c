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
        //printf("Current string in closed quotes: '%s'\n", str);
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
	char    temp;
    int     s_quote;
    int     d_quote;

    s_quote = 0;
    d_quote = 0;
    while (*str)
    {
        //printf("Current string in valid redirection: '%s'\n", str);
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
	int s_quote;
    int d_quote;
    
    //printf("str: %s\n", str);
    s_quote = 0;
    d_quote = 0;
    //if (str[0] == '|' || str[0] == '&')
        //return (false);
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

bool    no_logical_operators(char *str)
{
    int s_quote;
    int d_quote;

    s_quote = 0;
    d_quote = 0;
    while (*str)
    {
        quote_count(str, &s_quote, &d_quote);
        if (!(s_quote % 2) && !(d_quote % 2) && ((*str == '|' 
            && *(str + 1) == '|') || (*str == '&' && (*str + 1) == '&')))
            {
                return (false);
            }
            str++;
    }
    return (true);
}

//error checker function
bool	no_lexical_errors(char *str)
{
    //printf("Checking string for lexical errors: '%s'\n", str);
	if (closed_quotes(str) == false)
	{
		ft_putstr_fd("Syntax error: unclosed quotes\n", STDERR_FILENO);
		return (false);
	}
	if (valid_redirection(str) == false)
	{
		ft_putstr_fd("Syntax error: invalid redirection\n", STDERR_FILENO);
		return (false);
	}
	if (valid_pipes(str, 0) == false)
	{
		ft_putstr_fd("Syntax error: misplaced operator\n", STDERR_FILENO);
		return (false);
	}
    if (no_logical_operators(str) == false)
    {
        ft_putstr_fd("Error: logical operators '&&' and '||' \
            are not supported\n", STDERR_FILENO);
        return (false);
    }
	return (true);
}
