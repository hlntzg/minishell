/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:11:44 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/14 10:23:25 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node	*node;
	int			num;
	int			i;
	t_token		*temp;

	node = new_tree_node(WORD);
	num = count_expanded_args(*tokens);
	node->value = malloc(sizeof(char *) * (num + 1));
	if (!node->value)
		return (NULL);
	i = 0;
	while (*tokens && i < num)
	{
		if ((*tokens)->expand && has_space((*tokens)->content))
			node->value = split_expand(node->value, (*tokens)->content, &i);
		else
			node->value[i++] = ft_strdup((*tokens)->content);
		temp = *tokens;
		*tokens = (*tokens)->next;
		free(temp->content);
		free(temp);
	}
	node->value[i] = NULL;
	return (node);
}

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
	node->expand = token->expand;
	node->fd[0] = -1;
	node->fd[1] = -1;
	node->left = NULL;
	node->right = NULL;
	free(token);
	return (node);
}

t_tree_node	*parse_redirection(t_token **tokens)
{
	t_token		*temp;
	t_token		*nxt;
	t_tree_node	*node;

	if (!*tokens)
		return (NULL);
	temp = *tokens;
	if ((*tokens)->type >= REDIN && (*tokens)->type <= HEREDOC
		&& (*tokens)->next)
		return (create_redirection(tokens, temp));
	while (*tokens && (*tokens)->next)
	{
		nxt = (*tokens)->next;
		if ((*tokens)->next->type >= REDIN
			&& (*tokens)->next->type <= HEREDOC && nxt->next)
		{
			node = new_tree_node((*tokens)->next->type);
			(*tokens)->next = nxt->next->next;
			node->left = parse_redirection(&temp);
			node->right = create_file_node((nxt->next));
			return (free(nxt->content), free(nxt), node);
		}
		*tokens = nxt;
	}
	return (parse_command(&temp));
}

t_tree_node	*parse_pipes(t_token **tokens)
{
	t_token		*temp;
	t_token		*nxt;
	t_tree_node	*node;

	temp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		nxt = (*tokens)->next;
		if ((*tokens)->next->type == PIPE)
		{
			node = new_tree_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			node->left = parse_redirection(&temp);
			node->right = parse_pipes(&(nxt->next));
			return (free(nxt->content), free(nxt), node);
		}
		*tokens = nxt;
	}
	return (parse_redirection(&temp));
}

t_tree_node	*parse_tokens(t_token **tokens)
{
	t_tree_node	*tree;	

	if (!tokens || !*tokens)
		return (NULL);
	tree = parse_pipes(tokens);
	return (tree);
}
