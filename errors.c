/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:50:18 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/10 13:36:53 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

void	free_token(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	*tokens = (*tokens)->next;
	free(temp->content);
	free(temp);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
