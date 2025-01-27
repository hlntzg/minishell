/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:12:08 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/24 16:09:24 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_user_input(t_data *data, char *str)
{
	char	*temp;
	t_token	*token;

	temp = ft_strtrim(str, " \t\n\v\f\r");
	free(str);
	if (!temp)
		return (FAILURE);
	token = tokenizer(temp);
	if (!token)
	{
		free(temp);
		return (FAILURE);
	}
	expand_variables(token, data->env, data->exit_code);
	//printf("$ exit code: %d\n", data->exit_code);
	data->tree = parse_tokens(&token);
	if (data->tree == NULL)
	{
		free_tokens(token);
		return (FAILURE);
	}
	return (SUCCESS);
}
