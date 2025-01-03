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
    int i = start;

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

char *expand_variables(char *var, t_env *env)
{
    int index = 0;
    int single_quote = 0;
    int double_quote = 0;
    char *expanded = ft_strdup("");

    while (var[index])
    {
        if (var[index] == '\'' && double_quote % 2 == 0) // Handle single quotes
        {
            single_quote = !single_quote; // Toggle single-quote state
            char *tmp = expanded;
            expanded = ft_strjoin_char(expanded, var[index]); // Add the literal quote
            free(tmp);
        }
        else if (var[index] == '\"' && single_quote == 0) // Handle double quotes
        {
            double_quote = !double_quote; // Toggle double-quote state
            char *tmp = expanded;
            expanded = ft_strjoin_char(expanded, var[index]); // Add the literal quote
            free(tmp);
        }
        else if (!single_quote && var[index] == '$') // Expand variable if not in single quotes
        {
            int var_len = 0;
            char *var_name = get_variable_name(var, index + 1, &var_len); // Extract variable name
            char *var_value = get_variable_value(env, var_name); // Get its value from the environment

            if (var_value)
            {
                char *tmp = expanded;
                expanded = ft_strjoin(expanded, var_value); // Append variable value
                free(tmp);
            }

            free(var_name);
            index += var_len; // Skip past the variable name
        }
        else
        {
            char *tmp = expanded;
            expanded = ft_strjoin_char(expanded, var[index]); // Add the literal character
            free(tmp);
        }
        index++;
    }

    return (expanded);
}
