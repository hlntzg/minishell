/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:12:08 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/03 16:10:14 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_user_input(t_data *data, char *str)
{
	char	*temp;
	t_token	*token;
//	t_tree_node	*tree;

	temp = ft_strtrim(str, " \t\n\v\f\r");
	if (temp == NULL)
	{
		// handle error
		return (FAILURE);
	}
	token = tokenizer(temp);
	if (token == NULL)
	{
		//handle error
		return (FAILURE);
	}
	expand_variables(token, data->env, data->exit_code);
	data->tree = parse_tokens(&token);
	if (data->tree == NULL)
	{
		//handle error
		return (FAILURE);
	}
	return (SUCCESS);
}
