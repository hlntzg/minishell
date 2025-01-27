/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:21:32 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/27 10:41:20 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Process a single character during token expansion
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

// Handle variable expansion
char	*handle_variable(char *expanded, t_env *env, char *content, int *index)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		var_len;

	var_len = 0;
	var_name = get_variable_name(content, *index + 1, &var_len);
	var_value = get_variable_value(env, var_name);
	if (var_value)
	{
		temp = expanded;
		expanded = ft_strjoin(expanded, var_value);
		free(temp);
	}
	free(var_name);
	*index += var_len + 1;
	return (expanded);
}

// Check if variable expansion is needed
bool	should_expand_variable(char c, char next_c, int s_quote)
{
	if (c == '$' && !s_quote && next_c && next_c != '\'' && next_c != '\"')
		return (true);
	else
		return (false);
}

// Main expansion function
char	*expand_token_content(char *content, t_env *env, int exit_code)
{
	char	*expanded;
	int		i;
	int		s_quote;
	int		d_quote;

	expanded = ft_strdup("");
	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (content[i])
	{
		if (content[i] == '$' && content[i + 1] == '?' && !s_quote)
			expanded = handle_exit_code(expanded, exit_code, &i);
		else if (should_expand_variable(content[i], content[i + 1], s_quote))
			expanded = handle_variable(expanded, env, content, &i);
		else
		{
			expanded = process_character(expanded, content[i],
					&s_quote, &d_quote);
			i++;
		}
	}
	return (expanded);
}

// Main function to expand all tokens in the list
void	expand_variables(t_token *tokens, t_env *env, int exit_code)
{
	t_token	*current;
	t_token	*prev;
	char	*expanded;

	current = tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == WORD)
		{
			if (!prev || prev->type != HEREDOC)
			{
				expanded = expand_token_content(current->content,
						env, exit_code);
				free(current->content);
				current->content = expanded;
			}
		}
		prev = current;
		current = current->next;
	}
}
