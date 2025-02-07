/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:21:20 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/31 14:01:06 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node	*create_file_node(t_token *token)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->value = malloc(sizeof(char *) * 2);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	node->value[0] = token->content;
	node->value[1] = NULL;
	node->status = -1;
	node->left = NULL;
	node->right = NULL;
	free(token);
	return (node);
}

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
	node->status = -1;
	node->fd[0] = -1;
	node->fd[1] = -1;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int has_space(const char *str)
{
    while (*str)
    {
        if (*str == ' ')
            return (1);
        str++;
    }
    return (0);
}
