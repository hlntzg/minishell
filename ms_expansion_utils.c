/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:22:19 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/13 10:02:13 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

char	*get_variable_value(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->key, var_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_variable_name(char *str, int start, int *length)
{
	int	i;

	i = start;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*length = i - start;
	return (ft_substr(str, start, *length));
}

char	*ft_strjoin_char(char *str, char c)
{
	char	new_str[2];

	new_str[0] = c;
	new_str[1] = '\0';
	return (ft_strjoin(str, new_str));
}

// Handle exit code expansion
char	*handle_exit_code(char *expanded, int exit_code, int *index)
{
	char	*exit_code_str;
	char	*temp;

	exit_code_str = ft_itoa(exit_code);
	temp = expanded;
	expanded = ft_strjoin(expanded, exit_code_str);
	free(temp);
	free(exit_code_str);
	*index += 2;
	return (expanded);
}

void	free_null_node(t_token **tok, t_token **cur, t_token **prev)
{
	t_token	*tmp;

	tmp = *cur;
	if (*prev)
		(*prev)->next = (*cur)->next;
	else
		*tok = (*cur)->next;
	*cur = (*cur)->next;
	free(tmp->content);
	free(tmp);
	return ;
}
