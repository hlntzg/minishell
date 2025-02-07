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

static int has_space(const char *str)
{
    while (*str)
    {
        if (*str == ' ')
            return (1);
        str++;
    }
    return (0);
}

static void free_token(t_token **tokens)
{
    t_token *temp;
	
	temp = *tokens;
    *tokens = (*tokens)->next;
    free(temp->content);
    free(temp);
}

/*static char **reallocate_value(char **value, int actual_args, int max_args)
{
    char	**new_value;
	int		i;
	
	new_value = malloc(sizeof(char *) * (max_args + 1));
	if (!new_value)
		return (NULL);
	i = 0;
    while (i < actual_args && value[i])
	{
		new_value[i] = value[i];
		i++;
	}
	while (i <= max_args)
		new_value[i++] = NULL;
	free(value);
    return (new_value);
}*/

static void process_expanded_token(char **value, int *actual_args, int *max_args, char *content)
{
    char	**split_tokens;
	//char	**new_value;
	int		i;
	int		j;
	int		total;
	
	(void)max_args;
	split_tokens = ft_split(content, ' ');
	if (!split_tokens)
		return ;
	total = 0;
	while (split_tokens[total])
		total++;
	i = 0;
    while (split_tokens && split_tokens[i])
    {
        /*if (*actual_args >= total)
        {
            new_value = reallocate_value(value, *actual_args, total);
            if (!new_value)
            {
                // Handle memory allocation failure
                break;
            }
            value = new_value;
			*max_args *= 2;
        }*/
        value[*actual_args] = ft_strdup(split_tokens[i]);
        (*actual_args)++;
        i++;
    }
    if (split_tokens)
    {
		j = 0;
        while (split_tokens[j])
            free(split_tokens[j++]);
        free(split_tokens);
    }
}

t_tree_node *parse_command(t_token **tokens)
{
    t_tree_node	*node;
    int			max_args;
    int			actual_args;

    node = new_tree_node(WORD);
	max_args = argument_count(*tokens) * 2;
	actual_args = 0;
	node->value = malloc(sizeof(char *) * (max_args + 1));
    if (!node->value)
	{
		free(node);
		return (NULL);
	}
    while (*tokens && actual_args < max_args)
    {
        if ((*tokens)->expand && has_space((*tokens)->content))
            process_expanded_token(node->value, &actual_args, &max_args, (*tokens)->content);
        else
        {
            node->value[actual_args] = ft_strdup((*tokens)->content);
            actual_args++;
        }
        free_token(tokens);
    }
    node->value[actual_args] = NULL;
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
			//printf("after parse command: [0] %s [1] %s\n,", node->left->value[0], node->left->value[1]);
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
	//printf("after parse command: [0] %s [1] %s [2] %s\n,", tree->value[0], tree->value[1], tree->value[2]);
	return (tree);
}
