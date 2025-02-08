/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:50:18 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/09 12:50:20 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_error(char *str)
{
    printf("%s\n", str);
    return (0);
}

void free_token(t_token **tokens)
{
    t_token *temp;
	
	temp = *tokens;
    *tokens = (*tokens)->next;
    free(temp->content);
    free(temp);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
void	free_ast(t_tree_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->value)
	{
		while (node->value[i])
		{
			free(node->value[i]);
			i++;
		}
		free(node->value);
	}
	free(node);
}*/
