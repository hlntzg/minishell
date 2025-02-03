/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:09:26 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/31 14:36:41 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	tokenize_characters(t_data *data, char **str, t_token **token)
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
			data->count_heredoc += 1;
			(*str)++;
		}
		else
			add_tokens(token, new_token(REDIN, "<"));
	}
	else if (**str == '|')
		add_tokens(token, new_token(PIPE, "|"));
	(*str)++;
}*/

void	tokenize_characters(t_data *data, char **str, t_token **token)
{
	t_token	*new;

	if (**str == '>')
	{
		if (*(*str + 1) && *(*str + 1) == '>')
		{
			new = new_token(REDOUT_A, ">>");
			if (new)
				add_tokens(token, new);
			(*str)++;
		}
		else
		{
			new = new_token(REDOUT_T, ">");
			if (new)
				add_tokens(token, new);
		}
	}
	else if (**str == '<')
	{
		if (*(*str + 1) && *(*str + 1) == '<')
		{
			new = new_token(HEREDOC, "<<");
			if (new)
				add_tokens(token, new);
			data->count_heredoc += 1;
			(*str)++;
		}
		else
		{
			new = new_token(REDIN, "<");
			if (new)
				add_tokens(token, new);
		}
	}
	else if (**str == '|')
	{
		new = new_token(PIPE, "|");
		if (new)
			add_tokens(token, new);
	}
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
			free(word);
		}
	}
	while (**str && ft_strchr(" \t\n", **str))
		(*str)++;
}

t_token	*tokenizer(t_data *data, char *str)
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
			tokenize_characters(data, &str, &token);
		else
			tokenize_words(&str, &token, 0, 0);
	}
	return (token);
}
