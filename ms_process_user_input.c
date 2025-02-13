/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process_user_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:12:08 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/13 08:57:31 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "./includes/ms.h"

void	count_heredocs(t_data *data, t_token *token, int *status)
{
	if (data->count_heredoc > 16)
	{
		*status = 2;
		ft_putendl_fd("minishell: maximum here-document count exceeded",
			STDERR_FILENO);
		free_tokens(token);
		free_and_exit_minishell(data, *status);
	}
}

int	process_user_input(t_data *data, char *str, int *status)
{
	char	*temp;
	t_token	*token;

	data->exit_code = *status;
	temp = ft_strtrim(str, " \t\n\v\f\r");
	free(str);
	if (!temp)
		return (FAILURE);
	token = tokenizer(data, temp);
	if (!token)
	{
		*status = 2;
		free(temp);
		return (FAILURE);
	}
	free(temp);
	count_heredocs(data, token, status);
	expand_variables(&token, data);
	data->tree = parse_tokens(&token);
	if (data->tree == NULL)
	{
		free_tokens(token);
		return (FAILURE);
	}
	return (SUCCESS);
}
