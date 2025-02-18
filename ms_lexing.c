/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:09:26 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/13 10:19:45 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

void	tokenize_characters(t_data *data, char **str, t_token **token)
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
}

char	*extract_word(char **str, int *s_quote, int *d_quote)
{
	char	*start;

	start = *str;
	while (**str)
	{
		quote_count(*str, s_quote, d_quote);
		if (!(*s_quote % 2) && !(*d_quote % 2) && ft_strchr(" \t\n><|", **str))
			break ;
		(*str)++;
	}
	if (*str == start)
	{
		if ((*start == '"' || *start == '\'') && *(start + 1) == *start)
			return (ft_strdup(""));
		return (NULL);
	}
	return (ft_strndup(start, *str - start));
}

void	tokenize_words(char **str, t_token **token, int s_quote, int d_quote)
{
	char	*word;
	t_token	*new;

	word = extract_word(str, &s_quote, &d_quote);
	if (word)
	{
		new = new_token(WORD, word);
		if (new)
			add_tokens(token, new);
		free(word);
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
		ms_error(ERR_SYNTAX, ERR_PIPE_OR_AMPERSAND, FAILURE, FAILURE);
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
