/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:09:26 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/30 11:39:50 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_characters(char **str, t_token **token)
{
	if (**str == '>')
	{
		if (*(*str + 1) && *(*str + 1) == '>')
		{
			add_tokens(token, new_token(REDOUT_A, ">>"));
			(*str)++;
		}
		else
			add_tokens(token, new_token(REDOUT_T, ">"));
	}
	else if (**str == '<')
	{
		if (*(*str + 1) && *(*str + 1) == '<')
		{
			add_tokens(token, new_token(HEREDOC, "<<"));
			(*str)++;
		}
		else
			add_tokens(token, new_token(REDIN, "<"));
	}
	else if (**str == '|')
		add_tokens(token, new_token(PIPE, "|"));
	(*str)++;
}

void	tokenize_words(char **str, t_token **token, int s_quote, int d_quote)
{
	char	*temp;
	char	*word;
	t_token	*new;

	temp = *str;
	while (**str)
	{
		quote_count(*str, &s_quote, &d_quote);
		if (!(s_quote % 2) && !(d_quote % 2) && ft_strchr(" \t\n><|", **str))
			break ;
		(*str)++;
	}
	if (*str > temp)
	{
		word = ft_strndup(temp, *str - temp);
		if (word)
		{
			new = new_token(WORD, word);
			if (new)
				add_tokens(token, new);
		}
	}
	while (**str && ft_strchr(" \t\n", **str))
		(*str)++;
}

t_token	*tokenizer(char *str)
{
	t_token	*token;

	token = NULL;
	if (*str == '|' || *str == '&')
	{
		ft_error("Syntax error: unexpected pipe or ampersand at the beginning");
		return (NULL);
	}
	while (*str)
	{
		if (no_lexical_errors(str) == false)
		{
			free_tokens(token);
			return (NULL);
		}
		while (*str && ft_strchr(" \t\n", *str))
			str++;
		if (*str == '\0')
			break ;
		if (ft_strchr("><|", *str))
			tokenize_characters(&str, &token);
		else
			tokenize_words(&str, &token, 0, 0);
	}
	return (token);
}