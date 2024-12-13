/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:21:20 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/12 16:21:22 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_ast(t_tree_node *node)
{
	if (!node)
		return;
	free(node->value);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

t_tree_node	*new_tree_node(t_token *token)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// create commands -> count the commands and add the arguments to the 
// array struct **value variable, maybe i can do this on the weekend.