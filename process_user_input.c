/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:12:08 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/04 14:13:59 by hutzig           ###   ########.fr       */
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
	free(temp);
	if (data->count_heredoc > 16)//exit bash with code 2
	{
		*status = 2;
		ft_putendl_fd("minishell: maximum here-document count exceeded", STDERR_FILENO);
		free_tokens(token);
		free_and_exit_minishell(data, *status);
	}
	//printf("token before : %s\n", token->content);
	expand_variables(&token, data->env, data->exit_code);
	// if token content == '\0' free/remove that token
	//printf("token after: %s\n", token->content);
	data->tree = parse_tokens(&token);
	if (data->tree == NULL)
	{
		free_tokens(token);
		return (FAILURE);
	}
	return (SUCCESS);
}
