/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:12:08 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/06 13:10:15 by hutzig           ###   ########.fr       */
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
		data->exit_code = 2;
		free(temp);
		return (FAILURE);
	}
	free(temp);
	if (data->count_heredoc > 16)//exit bash with code 2
	{
	//	data->count_heredoc = 0;
		*status = 2;
		ft_putendl_fd("minishell: maximum here-document count exceeded", STDERR_FILENO);
		free_tokens(token);
		free_and_exit_minishell(data, *status);
	}
	expand_variables(token, data->env, data->exit_code);
	//printf("$ exit code: %d\n", data->exit_code);
//	printf("process_user_input: token BEFORE %s\n", token->content);
	data->tree = parse_tokens(&token);
//	if (token)
//		printf("process_user_input: token AFTER\n");//%s\n", token->content);
	if (data->tree == NULL)
	{
		free_tokens(token);
		return (FAILURE);
	}
	return (SUCCESS);
}
