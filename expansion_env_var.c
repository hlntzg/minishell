
#include "minishell.h"

// Handle exit code expansion
char    *handle_exit_code(char *expanded, int exit_code, int *index)
{
    char    *exit_code_str;
    char    *temp;

    exit_code_str = ft_itoa(exit_code);
    temp = expanded;
    expanded = ft_strjoin(expanded, exit_code_str);
    free(temp);
    free(exit_code_str);
    *index += 2;
    return (expanded);
}

// Handle variable expansion
char    *handle_variable(char *expanded, t_env *env, char *content, int *index)
{
    char    *var_name;
    char    *var_value;
    char    *temp;
    int     var_len;

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
bool    should_expand_variable(char c, char next_c, int s_quote)
{
    return (c == '$' && !s_quote && 
            next_c && next_c != '\'' && 
            next_c != '\"');
}

// Main expansion function, now more concise
char    *expand_token_content(char *content, t_env *env, int s_quote, int d_quote, int exit_code)
{
    char    *expanded;
    int     index;

    expanded = ft_strdup("");
    index = 0;
    while (content[index])
    {
        if (content[index] == '$' && content[index + 1] == '?' && !s_quote)
            expanded = handle_exit_code(expanded, exit_code, &index);
        else if (should_expand_variable(content[index], content[index + 1], s_quote))
            expanded = handle_variable(expanded, env, content, &index);
        else
        {
            expanded = process_character(expanded, content[index], &s_quote, &d_quote);
            index++;
        }
    }
    return (expanded);
}