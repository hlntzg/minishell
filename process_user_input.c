/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:12:08 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/30 15:06:49 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_user_input(t_data *data, char *str, int *status)
{
	char	*temp;
	t_token	*token;

	temp = ft_strtrim(str, " \t\n\v\f\r");
	free(str);
	if (!temp)
		return (FAILURE);
	token = tokenizer(data, temp);
	if (!token)
	{
		free(temp);
		return (FAILURE);
	}
	if (data->count_heredoc > 16)//exit bash with code 2
	{
		data->count_heredoc = 0;
		*status = 2;
		//ms_error("heredoc problem\n", NULL, 1, 1);
		ft_putendl_fd("minishell: maximum here-document count exceeded", STDERR_FILENO);
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
