/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:21:20 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/14 10:06:44 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

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
	node->expand = -1;
	node->fd[0] = -1;
	node->fd[1] = -1;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	has_space(const char *str)
{
	while (*str)
	{
		if (*str == ' ')
			return (1);
		str++;
	}
	return (0);
}

char	**split_expand(char **value, char *content, int *i)
{
	char	**split_words;
	int		j;

	split_words = ft_split(content, ' ');
	j = 0;
	while (split_words[j])
	{
		value[*i] = ft_strdup(split_words[j]);
		(*i)++;
		j++;
	}
	if (split_words)
	{
		j = 0;
		while (split_words[j])
			free(split_words[j++]);
		free(split_words);
	}
	return (value);
}
