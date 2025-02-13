/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:21:32 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/13 10:02:04 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

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
	if (c == '$' && !s_quote && next_c && next_c != '\''
		&& next_c != '\"' && next_c != ' ')
		return (true);
	else
		return (false);
}

// Main expansion function
char	*expand_token_content(char *content, t_data *data, int *flag)
{
	char	*exp;
	int		i;
	int		s_quote;
	int		d_quote;

	exp = ft_strdup("");
	i = 0;
	s_quote = 0;
	d_quote = 0;
	*flag = 0;
	while (content[i])
	{
		if (content[i] == '$' && content[i + 1] == '?' && !s_quote)
			exp = handle_exit_code(exp, data->exit_code, &i);
		else if (should_expand_variable(content[i], content[i + 1], s_quote))
		{
			exp = handle_variable(exp, data->env, content, &i);
			*flag = 1;
		}
		else
			exp = process_character(exp, content[i++], &s_quote, &d_quote);
	}
	return (exp);
}

void	process_token(t_token **tok, t_token **cur,
		t_token **prev, t_data *data)
{
	int		flag;
	char	*exp;

	if ((*cur)->type == WORD)
	{
		if (!(*prev) || (*prev)->type != HEREDOC)
		{
			exp = expand_token_content((*cur)->content, data, &flag);
			free((*cur)->content);
			(*cur)->content = exp;
			if ((*cur)->content[0] == '\0' && (*cur)->expand != 2)
			{
				free_null_node(tok, cur, prev);
				return ;
			}
			(*cur)->expand = flag;
		}
	}
}

void	expand_variables(t_token **tokens, t_data *data)
{
	t_token	*current;
	t_token	*prev;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		process_token(tokens, &current, &prev, data);
		if (current)
		{
			prev = current;
			current = current->next;
		}
	}
}
