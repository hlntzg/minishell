/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:35:24 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/13 10:38:50 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

int	expand_count(char *content)
{
	char	**split_tokens;
	int		total;
	int		j;

	split_tokens = ft_split(content, ' ');
	if (!split_tokens)
		return (0);
	total = 0;
	while (split_tokens[total])
		total++;
	if (split_tokens)
	{
		j = 0;
		while (split_tokens[j])
			free(split_tokens[j++]);
		free(split_tokens);
	}
	return (total);
}

int	count_expanded_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->expand && has_space(tokens->content))
			count += expand_count(tokens->content);
		else
			count++;
		tokens = tokens->next;
	}
	return (count);
}

char	*process_character(char *expanded, char c, int *s_quote, int *d_quote)
{
	char	*tmp;

	if (c == '\'' && *d_quote == 0)
	{
		*s_quote = !(*s_quote);
		return (expanded);
	}
	else if (c == '\"' && *s_quote == 0)
	{
		*d_quote = !(*d_quote);
		return (expanded);
	}
	tmp = expanded;
	expanded = ft_strjoin_char(expanded, c);
	free(tmp);
	return (expanded);
}
