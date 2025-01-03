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

t_tree_node	*create_redirection(t_token **tokens, t_token *temp)
{
	t_tree_node	*node;

	node = new_tree_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	node->left = parse_redirection(tokens);
	node->right = create_file_node(temp->next);
	free(temp->content);
	free(temp);
	return (node);
}

int	argument_count(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type == WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_tree_node	*new_tree_node(t_type type)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void free_ast(t_tree_node *node)
{
    if (!node)
        return;

    // Free left and right subtrees
    free_ast(node->left);
    free_ast(node->right);

    // Free node values
    if (node->value)
    {
        for (int i = 0; node->value[i]; i++)
            free(node->value[i]);
        free(node->value);
    }

    // Free the node itself
    free(node);
}
