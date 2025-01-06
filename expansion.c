/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:21:32 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/17 16:21:34 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_variable_value(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->key, var_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL); // Return NULL if variable not found
}

char *get_variable_name(char *str, int start, int *length)
{
	int i;
	
	i = start;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) // Variable naming rules
		i++;

	*length = i - start;
	return (ft_substr(str, start, *length));
}

char *ft_strjoin_char(char *str, char c)
{
	char new_str[2] = {c, '\0'};
	return (ft_strjoin(str, new_str)); // Use your existing ft_strjoin
}

// Process a single character during token expansion
char *process_character(char *expanded, char c, int *s_quote, int *d_quote)
{
    char *tmp;

    if (c == '\'' && *d_quote == 0) // Handle single quotes
        *s_quote = !(*s_quote);
    else if (c == '\"' && *s_quote == 0) // Handle double quotes
        *d_quote = !(*d_quote);
    tmp = expanded;
    expanded = ft_strjoin_char(expanded, c); // Add the literal character
    free(tmp);
    return (expanded);
}

// Expand a single token by processing its content
char *expand_token_content(char *content, t_env *env, int s_quote, int d_quote, int exit_code)
{
    char	*expanded;
    int		index;
	char	*var_name;
	char	*var_value;
	int		var_len;
	char	*temp;
	char	*exit_code_str;

    expanded = ft_strdup("");
	index = 0;
	while (content[index])
    {
		if (content[index + 1] == '?') // Handle the special case for $?
            {
                exit_code_str = ft_itoa(exit_code); // Convert exit code to string
                temp = expanded;
                expanded = ft_strjoin(expanded, exit_code_str); // Append the exit code
                free(temp);
                free(exit_code_str);
                index++; // Skip past the '?'
            }
        if (content[index] == '$' && !s_quote) // Expand variable
        {
            var_len = 0;
            var_name = get_variable_name(content, index + 1, &var_len);
            var_value = get_variable_value(env, var_name);
            if (var_value)
            {
                temp = expanded;
                expanded = ft_strjoin(expanded, var_value); // Append variable value
                free(temp);
            }
            free(var_name);
            index += var_len; // Skip past the variable name
        }
        else // Handle quotes or literal characters
            expanded = process_character(expanded, content[index], &s_quote, &d_quote);
        index++;
    }
    return (expanded);
}

// Main function to expand all tokens in the list
void expand_variables(t_token *tokens, t_env *env, int exit_code)
{
    t_token *current;
	char	*expanded;

	current = tokens;
    while (current)
    {
        if (current->type == WORD) // Expand only if the token is a word
        {
            expanded = expand_token_content(current->content, env, 0, 0, exit_code);
            free(current->content); // Free the old content
            current->content = expanded; // Replace with expanded content
        }
        current = current->next;
    }
}

