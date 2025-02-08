/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:11:44 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/03 13:07:01 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand_count(char *content)
{
    char	**split_tokens;
    int     total;
	int		j;

    split_tokens = ft_split(content, ' ');
    if (!split_tokens)
		return (0);
	total = 0;
	while (split_tokens[total])
		total++;
	if (split_tokens)
    {
	    j = 0;
        while (split_tokens[j])
            free(split_tokens[j++]);
        free(split_tokens);
    }
    return (total);
}

char    **split_expansion(char **value, char *content, int *i)
{
    char **split_words;
    int j;

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

t_tree_node *parse_command(t_token **tokens)
{
	t_tree_node	*node;
	int			num;
	int			i;
    t_token		*temp;
    
	node = new_tree_node(WORD);
    if ((*tokens)->expand && has_space((*tokens)->content))
        num = expand_count((*tokens)->content);
    else
		num = argument_count(*tokens);
	node->value = malloc(sizeof(char *) * (num + 1));
	if (!node->value)
		return (NULL);
	i = 0;
	while (*tokens && i < num)
	{
        if ((*tokens)->expand && has_space((*tokens)->content))
            node->value = split_expansion(node->value, (*tokens)->content, &i);
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

t_tree_node	*parse_redirection(t_token **tokens)
{
	t_token		*temp;
	t_token		*nxt;
	t_tree_node	*node;

	if (!*tokens)
		return (NULL);
	temp = *tokens;
	if ((*tokens)->type >= REDIN && (*tokens)->type <= HEREDOC)
		return (create_redirection(tokens, temp));
	while (*tokens && (*tokens)->next)
	{
		nxt = (*tokens)->next;
		if ((*tokens)->next->type >= REDIN && (*tokens)->next->type <= HEREDOC)
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
